/** ----------------------------------------------------------------------------
 * @file: sdc1_vel_control_node.cpp
 * @date: August 13, 2023
 * @author: Sebas Mtz
 * @email: sebas.martp@gmail.com
 *
 * @brief: Self-Driving Car 1 velocity control node. Based on SDC1 car dyn model.
 * -----------------------------------------------------------------------------
 **/

#include <stdio.h>
#include "rclcpp/rclcpp.hpp"

// #include <sdv_control/stanley_controller.hpp>
#include "controllers/feedback_linearization/model_based_controllers/SDCs/regulators/vtec_sdc1_pid.hpp"
#include "utils/utils.hpp"

#include "geometry_msgs/msg/accel.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "std_msgs/msg/multi_array_dimension.hpp"
#include "std_msgs/msg/u_int8.hpp"
#include "diagnostic_msgs/msg/diagnostic_status.hpp"
#include "diagnostic_msgs/msg/key_value.hpp"

#include "sdv_msgs/msg/eta_pose.hpp"

// #include "std_msgs/msg/float32.hpp"
// #include "geometry_msgs/msg/pose_stamped.hpp"
// #include "nav_msgs/msg/path.hpp"

class CarControlNode : public rclcpp::Node
{
    private:
        float sample_time_;
        float kp_ = 1;
        float ki_ = 0;
        float kd_ = 1;
        uint8_t D_MAX_ = 100;
        float U_MAX_ = 5000;     // MAX THROTTLE

        std::vector<float> init_pose_ = {0,0,0};

        std::unique_ptr<VTEC_SDC1_1DOF_PID> model_;
        DOFControllerType_E controller_type_{LINEAR_DOF};
        diagnostic_msgs::msg::DiagnosticStatus throttle_diag_;

        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Publisher<geometry_msgs::msg::Accel>::SharedPtr car_accel_;
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr car_vel_;
        rclcpp::Publisher<sdv_msgs::msg::EtaPose>::SharedPtr car_eta_pose_;
        rclcpp::Publisher<diagnostic_msgs::msg::DiagnosticStatus>::SharedPtr cal_throttle_;

        rclcpp::Subscription<std_msgs::msg::UInt8>::SharedPtr desired_velocity_;

        // rclcpp::Publisher<sdv_msgs::msg::ThrustControl>::SharedPtr car_force_;
        // rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr car_steering;
        // rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr follow_path;

        void timer_callback()
        {

            /* calculate Model States */
            model_->calculateModelParams();

            model_->calculateStates();

            model_->updateNonLinearFunctions();

            model_->calculateControlSignals();

            model_->updateControlSignals();

            model_->updateDBSignals();
            
            /* Publish Odometry */
            car_accel_->publish(model_->accelerations_);
            car_vel_->publish(model_->velocities_);
            car_eta_pose_->publish(model_->eta_pose_);

            /* Publish diagnostics */
            // TODO. Check for errors in throttle computation (maybe there are no real values) to updated diagnostics
            // value.value = model_->u_(0);
            // RCLCPP_INFO(this->get_logger(), "U: %f",  model_->u_(0));
            diagnostic_msgs::msg::KeyValue value;
            throttle_diag_.level = 0;
            value.key = "throttle_signal";
            value.value = model_->D_;
            throttle_diag_.values.push_back(value);
            cal_throttle_->publish(throttle_diag_);



            // model_->calculateCrosstrackError(x0,y0,x1,y1);
            // std_msgs::msg::Float32 deltainfo;
            // deltainfo.data = model_->delta_;
            // // car_steering->publish(deltainfo);

            // model_->updateSetpoint(4,0);
            // sdv_msgs::msg::ThrustControl u;
            // u.tau_x = model_->u_;
            // car_force_->publish(u);

            // geometry_msgs::msg::PoseStamped pose;
            // nav_msgs::msg::Path path;

            // pose.header.stamp       = rclcpp::Clock().now();
            // pose.header.frame_id    = "world";
            // pose.pose.position.x    = x0;
            // pose.pose.position.y    = y0;

            // path.header.stamp     = rclcpp::Clock().now();
            // path.header.frame_id  = "world";
            // path.poses.push_back(pose);

            // pose.header.stamp       = rclcpp::Clock().now();
            // pose.header.frame_id    = "world";
            // pose.pose.position.x    = x1;
            // pose.pose.position.y    = y1;

            // path.header.stamp     = rclcpp::Clock().now();
            // path.header.frame_id  = "world";
            // path.poses.push_back(pose);

            // follow_path->publish(path);
        }
        
        void set_reference(const std_msgs::msg::UInt8& msg) const
        {
            model_->updateCurrentReference(static_cast<float>(msg.data), 0);
        }

    public:
        CarControlNode() : Node("car_control_node")
        {
            int frequency;

            this->declare_parameter("frequency", 100);    // Super important to get parameters from launch files!!
            this->declare_parameter("kp", 0);
            this->declare_parameter("ki", 0);
            this->declare_parameter("kd", 0);
            this->declare_parameter("D_MAX", 0);

            this->get_parameter_or("frequency", frequency, 100);
            this->get_parameter_or("kp", kp_, static_cast<float>(1.0));
            this->get_parameter_or("ki", ki_, static_cast<float>(0.01));
            this->get_parameter_or("kd", kd_, static_cast<float>(0.01));
            this->get_parameter_or("D_MAX", D_MAX_, static_cast<uint8_t>(100));

            sample_time_ = 1.0 / static_cast<float>(frequency);

            car_accel_ = this->create_publisher<geometry_msgs::msg::Accel>("/car_simulation/dynamic_model/accel", 10);
            car_vel_ = this->create_publisher<geometry_msgs::msg::Twist>("/car_simulation/dynamic_model/vel", 10);
            car_eta_pose_ = this->create_publisher<sdv_msgs::msg::EtaPose>("/car_simulation/dynamic_model/eta_pose", 10);
            cal_throttle_ = this->create_publisher<diagnostic_msgs::msg::DiagnosticStatus>("/diagnostics",10);
            // car_steering = this->create_publisher<std_msgs::msg::Float32>("/car_control/car_control_node/steering",1);
            // follow_path = this->create_publisher<nav_msgs::msg::Path>("/car_path_to_follow",1);
            // car_force_ = this->create_publisher<sdv_msgs::msg::ThrustControl>("/car_control/car_control_node/force",1);

            desired_velocity_ = this->create_subscription<std_msgs::msg::UInt8>("/car_simulation/dynamic_model/set_vel_d",
                                1, std::bind(&CarControlNode::set_reference, this, std::placeholders::_1));


            throttle_diag_.name = "Throttle command (D)";
            throttle_diag_.message = "Integer in the range of [0, 255] for motor controller";
            throttle_diag_.hardware_id = "Throttle";

            timer_ = this->create_wall_timer( std::chrono::milliseconds(1000 / frequency),
                                                std::bind(&CarControlNode::timer_callback, this));

            // float delta_max = 1;
            // float k = 0.3;
            // float k_soft = 1;
            // float x0 = 0;
            // float y0 = -10;
            // float x1 = 0;
            // float y1 = 10;
        }

        ~CarControlNode(){model_.reset();}

        void configure(){
            model_ = std::make_unique<VTEC_SDC1_1DOF_PID>(sample_time_, kp_, ki_, kd_,
                                                            U_MAX_, controller_type_, D_MAX_);
            model_->setInitPose(init_pose_);
        }
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto control_node = std::make_shared<CarControlNode>();
    control_node->configure();
    rclcpp::spin(control_node->get_node_base_interface());
    rclcpp::shutdown();
    return 0;
}
