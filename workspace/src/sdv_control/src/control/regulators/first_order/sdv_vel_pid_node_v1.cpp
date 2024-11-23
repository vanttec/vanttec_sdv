#include <algorithm>
#include <cmath>
#include <cstdio>

#include "geometry_msgs/msg/pose2_d.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include "std_msgs/msg/float64.hpp"
#include "std_msgs/msg/u_int16.hpp"

#include <stdio.h>
#include "rclcpp/rclcpp.hpp"

#include "utils/utils.hpp"

#include "geometry_msgs/msg/accel.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "geometry_msgs/msg/twist_with_covariance_stamped.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "std_msgs/msg/multi_array_dimension.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/u_int8.hpp"
#include "std_msgs/msg/string.hpp"

#include "sdv_msgs/msg/nonlinear_functions.hpp"
#include "vectornav_msgs/msg/common_group.hpp"
#include "vectornav_msgs/msg/ins_group.hpp"

#include "controllers/feedback_linearization/model_based_controllers/SDCs/regulators/vtec_sdc1_pid.cpp"

using namespace std::chrono_literals;

class VelPidNode : public rclcpp::Node {
    public:
        VelPidNode() : Node("vel_pid_node") {
            using namespace std::placeholders;
            params = initialize_params();
            controller_ = VTEC_SDC1_1DOF_PID(params);
            
            velocity_setpoint_sub_ = this->create_subscription<std_msgs::msg::Float64>(
                "/sdv/velocity/setpoint", 10,
                [this](const std_msgs::msg::Float64 &msg) { vel_d_ = msg.data; });

            velocity_sub_ = this->create_subscription<nav_msgs::msg::Odometry>(
                "/vectornav/velocity_body", 10,
                [this](const nav_msgs::msg::Odometry &msg) { 
                    vel_ = msg.twist.twist.linear.x;
                });

            f_g_sub_ = this->create_subscription<sdv_msgs::msg::NonlinearFunctions>(
                "/sdv/control/nonlinear_functions", 10,
                [this](const sdv_msgs::msg::NonlinearFunctions &msg) {
                    f_x_ = msg.f_x;
                    g_x_ = msg.g_x;
                });

            throttle_pub_ = this->create_publisher<std_msgs::msg::Float64>(
                "/sdv/velocity/throttle", 10);


            updateTimer =
                this->create_wall_timer(10ms, std::bind(&VelPidNode::update, this));
        }

    private:
        PIDParameters params;
        // PID controller{PID::defaultParams()};

        rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr velocity_setpoint_sub_;
        rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr velocity_sub_;
        rclcpp::Subscription<sdv_msgs::msg::NonlinearFunctions>::SharedPtr f_g_sub_;
        
        rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr throttle_pub_;

        rclcpp::TimerBase::SharedPtr updateTimer;

        double vel_{0}, vel_d_{0}, u_{0};
        double f_x_{0}, g_x_{0};

        std_msgs::msg::Float64 throttle_msg;

        DOFControllerType_E controller_type_{LINEAR_DOF};
        VTEC_SDC1_1DOF_PID controller_{params};

        PIDParameters initialize_params() {
            this->declare_parameter("Kp", 1.0);
            this->declare_parameter("Ki", 0.01);
            this->declare_parameter("Kd", 0.2);
            this->declare_parameter("U_MAX", 1.0);
            this->declare_parameter("U_MIN", -1.0);
            this->declare_parameter("enable_ramp", true);
            this->declare_parameter("ramp_rate", 1.0);

            PIDParameters p;
            p.kP = this->get_parameter("Kp").as_double();
            p.kI = this->get_parameter("Ki").as_double();
            p.kD = this->get_parameter("Kd").as_double();
            p.kDt = 0.01;
            p.kUMax = this->get_parameter("U_MAX").as_double();
            p.kUMin = this->get_parameter("U_MIN").as_double();
            p.enable_ramp_rate_limit = this->get_parameter("enable_ramp").as_bool();
            p.ramp_rate = this->get_parameter("ramp_rate").as_double();
            return p;
        }

        void update() {
            controller_.updateNonLinearFunctions(f_x_, g_x_);
            u_ = controller_.calculateControlSignals(vel_, vel_d_);
            // u_ = controller_.get_control_signal();
            controller_.updateDBSignals(vel_, vel_d_, u_);
            double d_ = controller_.get_D_();
            std::cout << "vel: " << vel_ << std::endl;
            
            // if(u_ < -0.3 || u_ > 0.2) {
            if(d_ < -0. || d_ > 0.) {
                throttle_msg.data = d_;
            } else {
                throttle_msg.data = 0.0;
            }
            throttle_pub_->publish(throttle_msg);
        }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<VelPidNode>());
    rclcpp::shutdown();
    return 0;
}