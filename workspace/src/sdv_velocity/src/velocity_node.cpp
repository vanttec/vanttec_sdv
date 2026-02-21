#include <memory>
#include <cmath>
#include <algorithm>
#include <deque>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_with_covariance_stamped.hpp"
#include "geometry_msgs/msg/twist_with_covariance_stamped.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "std_msgs/msg/float32.hpp"

#include "tf2/LinearMath/Quaternion.h"
#include "tf2/LinearMath/Matrix3x3.h"

using std::placeholders::_1;
using namespace std::chrono_literals;

class VelocityEstimator : public rclcpp::Node
{
public:
  VelocityEstimator()
  : Node("velocity_estimator")
  {

    // Parameters
    this->declare_parameter<std::string>("pose_topic", "/pcl_pose");
    this->declare_parameter<std::string>("imu_vel_topic", "/vectornav/velocity_body");
    this->declare_parameter<std::string>("output_topic", "/control/velocity_body");

    // Safety Parameters
    this->declare_parameter<double>("imu_timeout", 0.5);   // Max time without IMU before switching to PCL
    this->declare_parameter<double>("pose_timeout", 0.5);  // Max time without PCL before emergency zero
    this->declare_parameter<double>("output_rate", 50.0);  // Hz (How often to talk to controller)

    this->declare_parameter<double>("alpha", 0.7);
    this->declare_parameter<double>("beta", 0.05);

    std::string pose_topic = this->get_parameter("pose_topic").as_string();
    std::string imu_vel_topic = this->get_parameter("imu_vel_topic").as_string();
    std::string output_topic = this->get_parameter("output_topic").as_string();

    imu_timeout_ = this->get_parameter("imu_timeout").as_double();
    pose_timeout_ = this->get_parameter("pose_timeout").as_double();
    double rate = this->get_parameter("output_rate").as_double();

    alpha_ = this->get_parameter("alpha").as_double();
    beta_ = this->get_parameter("beta").as_double();
    filter_dt_ = 1.0 / rate;

    rclcpp::QoS qos(rclcpp::KeepLast(10));
    qos.reliability(RMW_QOS_POLICY_RELIABILITY_RELIABLE);

    // Subcribers
    sub_pose_ = this->create_subscription<geometry_msgs::msg::PoseWithCovarianceStamped>(
      pose_topic, rclcpp::QoS(10).reliable(), 
      std::bind(&VelocityEstimator::pose_callback, this, _1));
    sub_imu_ = this->create_subscription<geometry_msgs::msg::TwistWithCovarianceStamped>(
      imu_vel_topic, rclcpp::QoS(10).reliable(), 
      std::bind(&VelocityEstimator::imu_callback, this, _1));

    // Publishers
    pub_odom_ = this->create_publisher<nav_msgs::msg::Odometry>(output_topic, qos);

    // Timer
    timer_ = this->create_wall_timer(
      std::chrono::duration<double>(1.0 / rate), 
      std::bind(&VelocityEstimator::timer_callback, this));

    RCLCPP_INFO(this->get_logger(), "Velocity Estimator started. Publishing at %.1f Hz", rate);
  }


private:
  std::deque<double> buffer_vx_;
  std::deque<double> buffer_vy_;
  const size_t median_window_ = 5; //Size of window, odd
  
  // IMU State
  rclcpp::Time last_imu_time_{0, 0, RCL_ROS_TIME};
  rclcpp::Time last_pose_msg_time_{0, 0, RCL_ROS_TIME}; 
  rclcpp::Time prev_pcl_stamp_{0, 0, RCL_ROS_TIME};

  // Store values
  double imu_vx_ = 0.0;
  double imu_vy_ = 0.0;
  bool imu_valid_ = false;

  // PCL Calculations
  double prev_pcl_x_ = 0.0, prev_pcl_y_ = 0.0;
  double pcl_vx_body_ = 0.0, pcl_vy_body_ = 0.0;
  bool first_pose_ = true;

  geometry_msgs::msg::Pose current_pose_;

  // Output Filter
  double est_vx_ = 0.0, est_vy_ = 0.0;
  double est_ax_ = 0.0, est_ay_ = 0.0;

  // Params
  double imu_timeout_, pose_timeout_;
  double alpha_, beta_, filter_dt_;

  rclcpp::Subscription<geometry_msgs::msg::PoseWithCovarianceStamped>::SharedPtr sub_pose_;
  rclcpp::Subscription<geometry_msgs::msg::TwistWithCovarianceStamped>::SharedPtr sub_imu_;
  rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr pub_odom_;
  rclcpp::TimerBase::SharedPtr timer_;

  // Delete the pikes
  double get_median(std::deque<double> &buffer, double new_val) {
      buffer.push_back(new_val);
      if (buffer.size() > median_window_) buffer.pop_front();

      if (buffer.empty()) return 0.0;

      std::vector<double> v(buffer.begin(), buffer.end());
      std::sort(v.begin(), v.end());

      return v[v.size() / 2];
  }

  void imu_callback(const geometry_msgs::msg::TwistWithCovarianceStamped::SharedPtr msg)
  {
    // Store high-quality velocity from GNSS/IMU 
    last_imu_time_ = this->get_clock()->now();
    imu_vx_ = msg->twist.twist.linear.x;
    imu_vy_ = msg->twist.twist.linear.y;
    imu_valid_ = true;
  }

  void pose_callback(const geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr msg)
  {
    rclcpp::Time current_time = this->get_clock()->now();
    current_pose_ = msg->pose.pose;

    rclcpp::Time msg_stamp(msg->header.stamp);
    double x = msg->pose.pose.position.x;
    double y = msg->pose.pose.position.y;

    if (first_pose_) {
      prev_pcl_stamp_ = msg_stamp;
      prev_pcl_x_ = x;
      prev_pcl_y_ = y;
      first_pose_ = false;
      return;
    }

    double dt = (msg_stamp - prev_pcl_stamp_).seconds();
    if (dt < 0.04) return; 

    // Calculate Global Velocity
    double raw_vx_global = (x - prev_pcl_x_) / dt;
    double raw_vy_global = (y - prev_pcl_y_) / dt;

    prev_pcl_stamp_ = msg_stamp;
    prev_pcl_x_ = x;
    prev_pcl_y_ = y;

    // Rotate to Body Frame
    tf2::Quaternion q(
      msg->pose.pose.orientation.x, msg->pose.pose.orientation.y,
      msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
    tf2::Matrix3x3 m(q);
    double r, p, yaw;
    m.getRPY(r, p, yaw);

    double cos_y = std::cos(yaw);
    double sin_y = std::sin(yaw);

    pcl_vx_body_ = raw_vx_global * cos_y + raw_vy_global * sin_y;
    pcl_vy_body_ = -raw_vx_global * sin_y + raw_vy_global * cos_y;
  }

  void timer_callback() {
rclcpp::Time now = this->get_clock()->now();

    bool imu_alive = (now - last_imu_time_).seconds() < imu_timeout_;
    bool pose_alive = (now - last_pose_msg_time_).seconds() < pose_timeout_;

    double noisy_input_vx = 0.0;
    double noisy_input_vy = 0.0;

    // Dicide source
    if (imu_alive && imu_valid_) {
      noisy_input_vx = imu_vx_;
      noisy_input_vy = imu_vy_;
    } 
    else if (pose_alive) {
      noisy_input_vx = pcl_vx_body_;
      noisy_input_vy = pcl_vy_body_;
    } 
    else {
      buffer_vx_.clear();
      buffer_vy_.clear();
      noisy_input_vx = 0.0;
      noisy_input_vy = 0.0;
      est_ax_ = 0.0; est_ay_ = 0.0;
    }

    // Apply media filter
    double target_vx = get_median(buffer_vx_, noisy_input_vx);
    double target_vy = get_median(buffer_vy_, noisy_input_vy);

    // Filtro Alpha-Beta (Suavizado y Predicción)
    double pred_vx = est_vx_ + (est_ax_ * filter_dt_);
    double pred_vy = est_vy_ + (est_ay_ * filter_dt_);

    double res_vx = target_vx - pred_vx;
    double res_vy = target_vy - pred_vy;

    est_vx_ = pred_vx + (alpha_ * res_vx);
    est_vy_ = pred_vy + (alpha_ * res_vy);

    est_ax_ = est_ax_ + (beta_ / filter_dt_) * res_vx;
    est_ay_ = est_ay_ + (beta_ / filter_dt_) * res_vy;

    // Publish
    auto odom = nav_msgs::msg::Odometry();
    odom.header.stamp = now;
    odom.header.frame_id = "odom";
    odom.child_frame_id = "base_link";

    odom.pose.pose = current_pose_;
    odom.twist.twist.linear.x = est_vx_;
    odom.twist.twist.linear.y = est_vy_;
    odom.twist.twist.linear.z = std::hypot(est_vx_, est_vy_);  

    double cov = (imu_alive || pose_alive) ? 0.05 : 999.0;
    for(int i=0; i<36; i+=7) odom.twist.covariance[i] = cov;

    pub_odom_->publish(odom);
  }
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<VelocityEstimator>());
  rclcpp::shutdown();
  return 0;
}