#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "nav_msgs/msg/path.hpp"
#include "sdv_msg/msg/system_dynamics.hpp"
#include "sdv_msg/msg/thrust_control.hpp"
#include "sdv_msg/msg/system_dynamics.hpp"
#include "sdv_msg/msg/eta_pose.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"

#include <sdv_control_ros2/controllers_merge.hpp>
#include <sdv_control_ros2/common.hpp>
#include <sdv_control_ros2/stanley_controller.hpp>
#include <sdv_control_ros2/pid.hpp>

using namespace std::chrono_literals;
using std::placeholders::_1;

class CarControlNode : public rclcpp::Node
{
    public:
        CarControlNode() : Node("car_control_node")
        {
            car_steering = this->create_publisher<std_msgs::msg::Float32>("/car_control/car_control_node/steering",1);
            car_force = this->create_publisher<sdv_msg::msg::ThrustControl>("/car_control/car_control_node/force",1);
            follow_path = this->create_publisher<nav_msgs::msg::Path>("/car_path_to_follow",1);
            timer_ = this->create_wall_timer(
                100ms, std::bind(&CarControlNode::timer_callback, this));
            
        }
        void configure(){
            carcontroller = std::make_unique<car_controller::CarController>(shared_from_this(), delta_max, k, k_soft,
            sample_time, kp, ki, kd, u_max, controller_type);
        }
    private:
        void timer_callback()
        {
            carcontroller->calculateCrosstrackError(x0,y0,x1,y1);
            std_msgs::msg::Float32 deltainfo;
            deltainfo.data = carcontroller->delta_;
            car_steering->publish(deltainfo);
            carcontroller->updateSetpoint(4,0);
            sdv_msg::msg::ThrustControl u;
            u.tau_x = carcontroller->u_;
            car_force->publish(u);

            geometry_msgs::msg::PoseStamped pose;
            nav_msgs::msg::Path path;

            pose.header.stamp       = rclcpp::Clock().now();
            pose.header.frame_id    = "world";
            pose.pose.position.x    = x0;
            pose.pose.position.y    = y0;

            path.header.stamp     = rclcpp::Clock().now();
            path.header.frame_id  = "world";
            path.poses.push_back(pose);

            pose.header.stamp       = rclcpp::Clock().now();
            pose.header.frame_id    = "world";
            pose.pose.position.x    = x1;
            pose.pose.position.y    = y1;

            path.header.stamp     = rclcpp::Clock().now();
            path.header.frame_id  = "world";
            path.poses.push_back(pose);

            follow_path->publish(path);
        }

        int frequency = 100;

        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr car_steering;
        rclcpp::Publisher<sdv_msg::msg::ThrustControl>::SharedPtr car_force;
        rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr follow_path;

        float sample_time = 1.0/frequency;
        float delta_max = 1;
        float k = 0.3;
        float k_soft = 1;
        float kp = 1;
        float ki = 0;
        float kd = 1;
        float u_max = 340;
        float x0 = 0;
        float y0 = -10;
        float x1 = 0;
        float y1 = 10;
        DOFControllerType_E controller_type = LINEAR_DOF;

    protected:
        std::unique_ptr<car_controller::CarController> carcontroller;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto merging_node = std::make_shared<CarControlNode>();
    merging_node->configure();
    rclcpp::spin(merging_node->get_node_base_interface());
    rclcpp::shutdown();
    return 0;
}
