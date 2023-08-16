/** ----------------------------------------------------------------------------
 * @file: sdc1_vel_asmc_node.cpp
 * @date: August 13, 2023
 * @author: Sebas Mtz
 * @email: sebas.martp@gmail.com
 *
 * @brief: Self-Driving Car 1 velocity asmc node. Based on SDC1 car dyn model.
 * -----------------------------------------------------------------------------
 **/

#include <stdio.h>
#include "rclcpp/rclcpp.hpp"

// #include <sdv_control/stanley_controller.hpp>
#include "controllers/feedback_linearization/model_based_controllers/SDCs/regulators/vtec_sdc1_asmc.hpp"
#include "utils/utils.hpp"

#include "geometry_msgs/msg/accel.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "std_msgs/msg/multi_array_dimension.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/u_int8.hpp"
#include "diagnostic_msgs/msg/diagnostic_status.hpp"
#include "diagnostic_msgs/msg/key_value.hpp"

#include "sdv_msgs/msg/eta_pose.hpp"
#include "vectornav_msgs/msg/ins_group.hpp"

class CarControlNode : public rclcpp::Node
{
    private:
        float sample_time_;

        ASMC_Config config_;
        float lambda2_;

        uint8_t D_MAX_;
        float U_MAX_{12800};    // MAX THROTTLE (pasarnos de esto no es bueno
                                // de acuerdo a sims con modelo parametrizado hasta step 95)
        bool is_simulation_;
        bool vel_msgs_arrived_{false};
        float vel_d_{0.0};
        float vel_body_x_{0.0};

        std::vector<float> init_pose_ = {0,0,0};

        std::unique_ptr<VTEC_SDC1_1DOF_ASMC> model_;
        DOFControllerType_E controller_type_{LINEAR_DOF};
        diagnostic_msgs::msg::DiagnosticStatus throttle_diag_;

        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Publisher<geometry_msgs::msg::Accel>::SharedPtr car_accel_;
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr car_vel_;
        rclcpp::Publisher<sdv_msgs::msg::EtaPose>::SharedPtr car_eta_pose_;
        rclcpp::Publisher<diagnostic_msgs::msg::DiagnosticStatus>::SharedPtr throttle_diag_pub;
        rclcpp::Publisher<std_msgs::msg::UInt8>::SharedPtr calc_throttle_;

        rclcpp::Subscription<vectornav_msgs::msg::InsGroup>::SharedPtr current_velocity_;
        rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr desired_velocity_;

        // rclcpp::Publisher<sdv_msgs::msg::ThrustControl>::SharedPtr car_force_;
        // rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr car_steering;
        // rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr follow_path;

        void timer_callback()
        {

            /* calculate Model States */
            model_->calculateModelParams();

            model_->calculateStates();

            model_->updateNonLinearFunctions();
            
            if(is_simulation_){
                model_->calculateControlSignals();
                model_->updateControlSignals();
                model_->updateDBSignals(vel_d_);
            } else {
                if(vel_msgs_arrived_){
                    RCLCPP_INFO(this->get_logger(), "Vectornav vel received");
                    model_->calculateControlSignals(vel_body_x_);
                    model_->updateControlSignals();
                    model_->updateDBSignals(vel_d_);
                } else
                    RCLCPP_INFO(this->get_logger(), "Waiting for vectornav");
            }
            
            /* Publish Odometry */
            car_accel_->publish(model_->accelerations_);
            car_vel_->publish(model_->velocities_);
            car_eta_pose_->publish(model_->eta_pose_);

            /* Publish diagnostics */
            // TODO. Check for errors in throttle computation (maybe there are no real values) to updated diagnostics
            // value.value = model_->u_(0);
            // RCLCPP_INFO(this->get_logger(), "U: %f",  model_->u_(0));
            // diagnostic_msgs::msg::KeyValue value;
            // throttle_diag_.level = 0;
            // value.key = "throttle_signal";
            // value.value = std::to_string(model_->D_);
            // throttle_diag_.values.push_back(value);
            // throttle_diag_pub->publish(throttle_diag_);

            std_msgs::msg::UInt8 D;
            D.data = model_->D_;
            calc_throttle_->publish(D);
        }
        
        void set_reference(const std_msgs::msg::Float32& msg) //const
        {
            vel_d_ = msg.data;
            model_->updateCurrentReference(vel_d_, 0);
        }

        void save_velocity(const vectornav_msgs::msg::InsGroup::SharedPtr msg_in) //const
        {
            vel_body_x_ = msg_in->velbody.x;
            vel_msgs_arrived_ = true;
        }

    public:
        CarControlNode() : Node("car_control_node")
        {
            int frequency;
            //https://roboticsbackend.com/rclcpp-params-tutorial-get-set-ros2-params-with-cpp/
            this->declare_parameter("is_simulation", rclcpp::PARAMETER_BOOL);
            this->declare_parameter("frequency", rclcpp::PARAMETER_INTEGER);    // Super important to get parameters from launch files!!
            this->declare_parameter("lambda1", rclcpp::PARAMETER_DOUBLE);
            this->declare_parameter("lambda2", rclcpp::PARAMETER_DOUBLE);
            this->declare_parameter("K2", rclcpp::PARAMETER_DOUBLE);
            this->declare_parameter("K_alpha", rclcpp::PARAMETER_DOUBLE);
            this->declare_parameter("K1_init", rclcpp::PARAMETER_DOUBLE);
            this->declare_parameter("K_min", rclcpp::PARAMETER_DOUBLE);
            this->declare_parameter("mu", rclcpp::PARAMETER_DOUBLE);
            this->declare_parameter("D_MAX", rclcpp::PARAMETER_INTEGER);

            frequency = this->get_parameter("frequency").as_int();
            is_simulation_ = this->get_parameter("is_simulation").as_bool();

            config_.lambda = this->get_parameter("lambda1").as_double();
            lambda2_ = this->get_parameter("lambda2").as_double();
            config_.K2 = this->get_parameter("K2").as_double();
            config_.K_alpha = this->get_parameter("K_alpha").as_double();
            config_.K1_init = this->get_parameter("K1_init").as_double();
            config_.K_min = this->get_parameter("K_min").as_double();
            config_.mu = this->get_parameter("mu").as_double();
            config_.u_max = __FLT_MAX__;
            config_.type = LINEAR_DOF;

            this->get_parameter_or("D_MAX", D_MAX_, static_cast<uint8_t>(180));

            // std::cout << "Freq = " << frequency << std::endl;
            // std::cout << "kp = " << kp_ << std::endl;
            // std::cout << "ki = " << ki_ << std::endl;
            // std::cout << "kd = " << kd_ << std::endl;
            // std::cout << "D_MAX = " << static_cast<int>(D_MAX_) << std::endl;

            sample_time_ = 1.0 / static_cast<float>(frequency);
            
            car_accel_ = this->create_publisher<geometry_msgs::msg::Accel>("/car_simulation/dynamic_model/accel", 10);
            car_vel_ = this->create_publisher<geometry_msgs::msg::Twist>("/car_simulation/dynamic_model/vel", 10);
            car_eta_pose_ = this->create_publisher<sdv_msgs::msg::EtaPose>("/car_simulation/dynamic_model/eta_pose", 10);

            throttle_diag_pub = this->create_publisher<diagnostic_msgs::msg::DiagnosticStatus>("/diagnostics",10);
            calc_throttle_ = this->create_publisher<std_msgs::msg::UInt8>("/car_control/control_signal/D",10);

            current_velocity_ = this->create_subscription<vectornav_msgs::msg::InsGroup>("/vectornav/raw/ins",
                                1, std::bind(&CarControlNode::save_velocity, this, std::placeholders::_1));
            desired_velocity_ = this->create_subscription<std_msgs::msg::Float32>("/car_control/setpoint/velocity",
                                1, std::bind(&CarControlNode::set_reference, this, std::placeholders::_1));

            throttle_diag_.name = "Throttle command (D)";
            throttle_diag_.message = "Integer in the range of [0, 255] for motor controller";
            throttle_diag_.hardware_id = "Throttle";

            timer_ = this->create_wall_timer( std::chrono::milliseconds(1000 / frequency),
                                                std::bind(&CarControlNode::timer_callback, this));
        }

        ~CarControlNode(){model_.reset();}

        void configure(){

            model_ = std::make_unique<VTEC_SDC1_1DOF_ASMC>(sample_time_, config_, lambda2_, U_MAX_, D_MAX_);
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
