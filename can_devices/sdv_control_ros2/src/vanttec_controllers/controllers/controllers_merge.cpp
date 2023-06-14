#include <memory>
#include <functional>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "sdv_msg/msg/eta_pose.hpp"
#include "sdv_msg/msg/system_dynamics.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "sdv_control_ros2/controllers_merge.hpp"

namespace car_controller

{
    CarController::CarController(rclcpp::Node::SharedPtr node, float delta_max, float k, float k_soft, const float sample_time, const float k_p, const float k_i, const float k_d, const float u_max, const DOFControllerType_E& type):
    node_(node), stanleycontroller::StanleyController(delta_max, k, k_soft), pid::PID(sample_time, k_p, k_i, k_d, u_max, type)
    {
        stanley_heading = node->create_subscription<sdv_msg::msg::EtaPose>(
                "/car_simulation/dynamic_model/eta_pose", 10, std::bind(&StanleyController::setHeading, this, std::placeholders::_1));
        car_dynamics = node->create_subscription<sdv_msg::msg::SystemDynamics>(
            "/car_simulation/dynamic_model/non_linear_functions", 1, std::bind(&PID::updateFunctions, this, std::placeholders::_1));
        car_vel1 = node->create_subscription<geometry_msgs::msg::Twist>(
            "/car_simulation/dynamic_model/vel", 1, std::bind(&StanleyController::calculateSteering, this, std::placeholders::_1));
        car_vel2 = node->create_subscription<geometry_msgs::msg::Twist>(
            "/car_simulation/dynamic_model/vel", 1, std::bind(&PID::calculateManipulation, this, std::placeholders::_1));
    }
    CarController::~CarController(){}
}
