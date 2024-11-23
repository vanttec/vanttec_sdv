#include <tf2/LinearMath/Quaternion.h>

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <eigen3/Eigen/Dense>
#include "rclcpp/rclcpp.hpp"

#include "geometry_msgs/msg/pose2_d.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "std_msgs/msg/u_int8.hpp"
#include "nav_msgs/msg/path.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "sdv_msgs/msg/nonlinear_functions.hpp"

#include "dynamic_models/ground_vehicles/car_like/vehicles/vtec_sdc1.cpp"

using namespace std::chrono_literals;

class SDVDynamicSimNode : public rclcpp::Node {
 public:
  SDVDynamicSimNode() : Node("sdv_dynamic_sim_node") {
    using namespace std::placeholders;

    this->declare_parameter("sample_time", 0.01);
    this->declare_parameter("D_MAX", 255);
    sample_time_ = this->get_parameter("sample_time").as_double();
    D_MAX_ = this->get_parameter("D_MAX").as_int();

    model = VTecSDC1DynamicModel{sample_time_, D_MAX_};
    model.setInitPose(Eigen::Vector3f{0,0,0});

    odom_pub_ =
        this->create_publisher<nav_msgs::msg::Odometry>("/vectornav/velocity_body", 10);

    pose_path_pub_ = this->create_publisher<nav_msgs::msg::Path>(
        "/sdv/pose_path", 10);
    
    f_g_pub_ = this->create_publisher<sdv_msgs::msg::NonlinearFunctions>(
        "/sdv/control/nonlinear_functions", 10);

    throttle_sub_ = this->create_subscription<std_msgs::msg::Float64>(
        "/sdv/velocity/throttle", 10,
        [this](const std_msgs::msg::Float64 &msg) {
            model.setThrottle(msg.data);
         });

    tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);
    pose_stamped_tmp_.header.frame_id = "world";
    pose_path.header.frame_id = "world";
    pose_path.header.stamp = SDVDynamicSimNode::now();

    // sample_time_ = 0.01;
    updateTimer = this->create_wall_timer(
        // 1000ms*sample_time_, std::bind(&SDVDynamicSimNode::update, this));
        10ms, std::bind(&SDVDynamicSimNode::update, this));
  }

 protected:
  void update() {
    model.calculateModelParams();
    model.calculateStates();

    /**
     * Output stage
     */
    double x{0}, y{0}, etheta{0};
    x = model.eta_pose_(0);  // position in x
    y = model.eta_pose_(1);  // position in y
    etheta = model.eta_pose_(2);

    tf2::Quaternion q;
    q.setRPY(0, 0, etheta);

    geometry_msgs::msg::Pose2D pose;
    nav_msgs::msg::Odometry odom;

    etheta = std::fmod(etheta + M_PI, 2*M_PI) - M_PI; // [-pi, pi]

    pose.x = x;
    pose.y = y;
    pose.theta = etheta;

    odom.pose.pose.position.x = x;
    odom.pose.pose.position.y = y;
    odom.pose.pose.position.z = 0;
    odom.pose.pose.orientation.x = q[0];
    odom.pose.pose.orientation.y = q[1];
    odom.pose.pose.orientation.z = q[2];
    odom.pose.pose.orientation.w = q[3];

    double u{0}, v{0}, r{0};

    geometry_msgs::msg::Vector3 velMsg;

    u = model.velocities_(0);  // surge velocity
    v = model.velocities_(1);  // sway velocity
    r = model.velocities_(2);  // yaw rate
    velMsg.x = u;
    velMsg.y = v;
    velMsg.z = r;
    odom.twist.twist.linear.x = u;
    odom.twist.twist.linear.y = v;
    odom.twist.twist.linear.z = 0;

    odom.twist.twist.angular.x = 0;
    odom.twist.twist.angular.y = 0;
    odom.twist.twist.angular.z = r;

    pose_stamped_tmp_.pose.position.x = pose.x;
    pose_stamped_tmp_.pose.position.y = pose.y;
    pose_path.poses.push_back(pose_stamped_tmp_);

    odom_pub_->publish(odom);
    pose_path_pub_->publish(pose_path);

    f_g_msg.f_x = model.get_f_();
    f_g_msg.g_x = model.get_g_();
    f_g_pub_->publish(f_g_msg);

    tf_broadcast(pose);
  }

 private:
  rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr localVelPub;
  rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr pose_path_pub_;
  rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odom_pub_;
  rclcpp::Publisher<sdv_msgs::msg::NonlinearFunctions>::SharedPtr f_g_pub_;
  rclcpp::TimerBase::SharedPtr updateTimer;

  geometry_msgs::msg::PoseStamped pose_stamped_tmp_;
  nav_msgs::msg::Path pose_path;
  sdv_msgs::msg::NonlinearFunctions f_g_msg;

  rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr throttle_sub_,
      rightThrusterSub;
  double Tport{0}, Tstbd{0};
  float sample_time_;
  int D_MAX_;

  VTecSDC1DynamicModel model{0.01,255};

  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;

  void tf_broadcast(const geometry_msgs::msg::Pose2D &msg) {
    geometry_msgs::msg::TransformStamped t;

    // Read message content and assign it to
    // corresponding tf variables
    t.header.stamp = this->get_clock()->now();
    t.header.frame_id = "world";
    t.child_frame_id = "sdv";

    // Turtle only exists in 2D, thus we get x and y translation
    // coordinates from the message and set the z coordinate to 0
    t.transform.translation.x = msg.x;
    t.transform.translation.y = msg.y;
    t.transform.translation.z = 0.0;

    // For the same reason, turtle can only rotate around one axis
    // and this why we set rotation in x and y to 0 and obtain
    // rotation in z axis from the message
    tf2::Quaternion q;
    q.setRPY(0, 0, msg.theta);
    t.transform.rotation.x = q.x();
    t.transform.rotation.y = q.y();
    t.transform.rotation.z = q.z();
    t.transform.rotation.w = q.w();

    // Send the transformation
    tf_broadcaster_->sendTransform(t);
  }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SDVDynamicSimNode>());
  rclcpp::shutdown();
  return 0;
}