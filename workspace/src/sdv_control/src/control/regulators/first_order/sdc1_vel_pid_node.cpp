/** ----------------------------------------------------------------------------
 * @file: sdc1_vel_pid_node.cpp
 * @date: August 15, 2023
 * @author: Sebas Mtz
 * @email: sebas.martp@gmail.com
 *
 * @brief: Self-Driving Car 1 velocity pid node. Based on SDC1 car dyn model.
 * -----------------------------------------------------------------------------
 **/

#include <stdio.h>
#include "rclcpp/rclcpp.hpp"

#include "controllers/feedback_linearization/model_based/SDCs/regulators/vtec_sdc1_pid.hpp"
#include "utils/utils.hpp"

#include "geometry_msgs/msg/accel.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "std_msgs/msg/multi_array_dimension.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/u_int8.hpp"
#include "std_msgs/msg/string.hpp"

#include "sdv_msgs/msg/eta_pose.hpp"
#include "vectornav_msgs/msg/ins_group.hpp"
#include "vectornav_msgs/msg/common_group.hpp"
#include "geometry_msgs/msg/twist_with_covariance_stamped.hpp"

#include "nav_msgs/msg/odometry.hpp"

// #include "std_msgs/msg/float32.hpp"

class CarControlNode : public rclcpp::Node
{
    private:
        float sample_time_;
        bool is_simulation_;
        bool vel_msgs_received_{false};
        std::string drive_mode_;
        std::string auto_mode_;
        
        /* PID Params */
        float kp_;
        float ki_;
        float kd_;
        uint8_t D_MAX_;
        double U_MAX_{12800};     // MAX THROTTLE (pasarnos de esto no es bueno
                                  // de acuerdo a sims con modelo parametrizado hasta step 95)
        double U_MIN_{0};
        
        float vel_d_{0.0};
        float vel_body_x_{0.0};
        DOFControllerType_E controller_type_{LINEAR_DOF};

        /* Model Params */
        std::shared_ptr<VTecSDC1DynamicModel> car_;
        std::unique_ptr<VTEC_SDC1_1DOF_PID> pid_;
        std::vector<double> init_pose_ = {0,0,0};
        PIDParameters pid_params_;

        rclcpp::TimerBase::SharedPtr timer_;
        geometry_msgs::msg::Accel accel_;
        geometry_msgs::msg::Twist vel_;
        sdv_msgs::msg::EtaPose pose_;

        /* Publishers */
        rclcpp::Publisher<geometry_msgs::msg::Accel>::SharedPtr car_accel_;
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr car_vel_;
        rclcpp::Publisher<sdv_msgs::msg::EtaPose>::SharedPtr car_eta_pose_;
        rclcpp::Publisher<std_msgs::msg::UInt8>::SharedPtr calc_throttle_;

        /* Subscribers */
        rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr car_steering_sim_;
        rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr car_steering_;
        rclcpp::Subscription<vectornav_msgs::msg::InsGroup>::SharedPtr current_velocity_;
        rclcpp::Subscription<vectornav_msgs::msg::CommonGroup>::SharedPtr current_attitude_;
        rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr desired_velocity_;
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr drive_mode_sub_;
        rclcpp::Subscription<geometry_msgs::msg::TwistWithCovarianceStamped>::SharedPtr imu_velocity_sub_;
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr auto_mode_sub_;

        // rclcpp::Publisher<sdv_msgs::msg::ThrustControl>::SharedPtr car_force_;

        void timer_callback()
        {

                if(is_simulation_){

                    /* calculate Model States */
                    car_->calculateModelParams();
                    car_->computeDynamics();

                    pid_->updateNonLinearFunctions();
                    pid_->calculateControlSignals(car_->velocities_(0), vel_d_, 0);
                    pid_->updateControlSignals();

                    car_->updateDBSignals(vel_d_);

                    /* Publish Odometry */
                    accel_.linear.x = car_->accelerations_(0);
                    accel_.linear.y = car_->accelerations_(1);
                    
                    vel_.linear.x = car_->velocities_(0);
                    vel_.linear.y = car_->velocities_(1);

                    pose_.x = car_->eta_pose_(0);
                    pose_.y = car_->eta_pose_(1);

                    car_accel_->publish(accel_);
                    car_vel_->publish(vel_);
                    car_eta_pose_->publish(pose_);
                } else {

                    if(drive_mode_ == "Automatic"){
                        RCLCPP_INFO(this->get_logger(), "Autonomous mode enabled");

                        if(vel_msgs_received_){

                            /* calculate Model States */
                            car_->calculateModelParams();
                            car_->computeDynamics();

                            pid_->updateNonLinearFunctions();
                            RCLCPP_INFO(this->get_logger(), "Vectornav vel received");
                            pid_->calculateControlSignals(vel_body_x_, vel_d_, 0);
                            pid_->updateControlSignals();

                            car_->updateDBSignals(vel_d_);
                        } else
                            RCLCPP_INFO(this->get_logger(), "Waiting for vectornav");
                    } else {
                        RCLCPP_WARN(this->get_logger(), "Warning: Manual mode enabled");
                    }
                }
            

            // RCLCPP_INFO(this->get_logger(), "U: %f",  pid_->u_(0));

            std_msgs::msg::UInt8 D;
            D.data = car_->D_;
            calc_throttle_->publish(D);

            // pid_->calculateCrosstrackError(x0,y0,x1,y1);
            // std_msgs::msg::Float32 deltainfo;
            // deltainfo.data = pid_->delta_;
            // // car_steering_->publish(deltainfo);

            // pid_->updateSetpoint(4,0);
            // sdv_msgs::msg::ThrustControl u;
            // u.tau_x = pid_->u_;
            // car_force_->publish(u);

        }
        
        void set_reference(const std_msgs::msg::Float32& msg) //const
        {
            vel_d_ = msg.data;
        }

        void save_velocity(const vectornav_msgs::msg::InsGroup::SharedPtr msg_in) //const
        {
            vel_body_x_ = msg_in->velbody.x;
            // pid_->updateCurrentReference(vel_body_x_, 0);
            vel_msgs_received_ = true;
        }

        void set_pitch(const vectornav_msgs::msg::CommonGroup::SharedPtr msg_in) //const
        {
            if(this->is_simulation_)
                car_->setPitch(msg_in->yawpitchroll.y * M_PI / 180.0);
        }

        void set_steering(const std_msgs::msg::Float32& msg) //const
        {
            if(this->is_simulation_){
                car_->setSteering(msg.data);
            } else {
                // std::cout << std::to_string(msg.data * M_PI / 180.0) <<std::endl;
                car_->setSteering(/*msg.data * M_PI / 180.0*/0.0);
            }
        }

        void set_drive_mode(const std_msgs::msg::String& msg)
        {
            drive_mode_ = msg.data;
        }

        void set_auto_mode(const std_msgs::msg::String& msg)
        {
            auto_mode_ = msg.data;
        }

    public:
        CarControlNode() : Node("sdc1_control_node")
        {
            int frequency;

            /* Params */
            //https://roboticsbackend.com/rclcpp-params-tutorial-get-set-ros2-params-with-cpp/
            this->declare_parameter("is_simulation", rclcpp::PARAMETER_BOOL);
            this->declare_parameter("frequency", rclcpp::PARAMETER_INTEGER);    // Super important to get parameters from launch files!!
            this->declare_parameter("init_pose", rclcpp::PARAMETER_DOUBLE_ARRAY);
            
            this->declare_parameter("Kp", rclcpp::PARAMETER_DOUBLE);
            this->declare_parameter("Ki", rclcpp::PARAMETER_DOUBLE);
            this->declare_parameter("Kd", rclcpp::PARAMETER_DOUBLE);
            this->declare_parameter("U_MAX", rclcpp::PARAMETER_DOUBLE);
            this->declare_parameter("U_MIN", rclcpp::PARAMETER_DOUBLE);
            this->declare_parameter("D_MAX", rclcpp::PARAMETER_INTEGER);

            frequency = this->get_parameter("frequency").as_int();
            is_simulation_ = this->get_parameter("is_simulation").as_bool();
            init_pose_ = this->get_parameter("init_pose").as_double_array();

            kp_ = this->get_parameter("Kp").as_double();
            ki_ = this->get_parameter("Ki").as_double();
            kd_ = this->get_parameter("Kd").as_double();
            this->get_parameter_or("U_MAX", U_MAX_, static_cast<double>(12800));
            this->get_parameter_or("U_Min", U_MIN_, static_cast<double>(0));
            this->get_parameter_or("D_MAX", D_MAX_, static_cast<uint8_t>(90));

            sample_time_ = 1.0 / static_cast<float>(frequency);
            
            pid_params_.kP = kp_;
            pid_params_.kI = ki_;
            pid_params_.kD = kd_;
            pid_params_.kUMax = U_MAX_;
            pid_params_.kUMin = U_MIN_;
            pid_params_.kDt = sample_time_;
            pid_params_.enable_ramp_rate_limit = true;
            pid_params_.ramp_rate = 1;
            
            /* Publishers */
            if(is_simulation_){
                car_accel_ = this->create_publisher<geometry_msgs::msg::Accel>("/sdc_simulation/dynamic_model/accel", 10);
                car_vel_ = this->create_publisher<geometry_msgs::msg::Twist>("/sdc_simulation/dynamic_model/vel", 10);
                car_eta_pose_ = this->create_publisher<sdv_msgs::msg::EtaPose>("/sdc_simulation/dynamic_model/eta_pose", 10);
            }
            calc_throttle_ = this->create_publisher<std_msgs::msg::UInt8>("/sdc_control/control_signal/D",10);
            // car_force_ = this->create_publisher<sdv_msgs::msg::ThrustControl>("/sdc_control/sdc_control_node/force",1);

            /* Subscribers */
            if(is_simulation_){
                car_steering_sim_     = this->create_subscription<std_msgs::msg::Float32>("/sdc_control/control_signal/delta",
                                    1, std::bind(&CarControlNode::set_steering, this, std::placeholders::_1));
            } else {
                car_steering_     = this->create_subscription<std_msgs::msg::Float32>("/sdc_state/steering",
                                    1, std::bind(&CarControlNode::set_steering, this, std::placeholders::_1));
                current_attitude_ = this->create_subscription<vectornav_msgs::msg::CommonGroup>("/vectornav/raw/common",
                                    1, std::bind(&CarControlNode::set_pitch, this, std::placeholders::_1));
                // current_velocity_ = this->create_subscription<vectornav_msgs::msg::InsGroup>("/vectornav/raw/ins",
                //                     1, std::bind(&CarControlNode::save_velocity, this, std::placeholders::_1));

                imu_velocity_sub_ = this->create_subscription<geometry_msgs::msg::TwistWithCovarianceStamped>("/vectornav/velocity_body",
                    1, [this](const geometry_msgs::msg::TwistWithCovarianceStamped &msg) { 
                        this->vel_body_x_ = msg.twist.twist.linear.x;
                        this->vel_msgs_received_ = true;
                    });
            }

            desired_velocity_ = this->create_subscription<std_msgs::msg::Float32>("/sdc_control/setpoint/velocity",
                                1, std::bind(&CarControlNode::set_reference, this, std::placeholders::_1));
            drive_mode_sub_   = this->create_subscription<std_msgs::msg::String>("/sdv/drive_mode",
                                1, std::bind(&CarControlNode::set_drive_mode, this, std::placeholders::_1));
            auto_mode_sub_   = this->create_subscription<std_msgs::msg::String>("/sdv/xbox_controller/auto_mode",
                    1, std::bind(&CarControlNode::set_auto_mode, this, std::placeholders::_1));

            timer_ = this->create_wall_timer( std::chrono::milliseconds(1000 / frequency),
                                                std::bind(&CarControlNode::timer_callback, this));
        }

        ~CarControlNode(){/*pid_.reset();*/}

        void configure(){
            car_ = std::make_shared<VTecSDC1DynamicModel>(sample_time_, D_MAX_);
            pid_ = std::make_unique<VTEC_SDC1_1DOF_PID>(pid_params_, car_);
            
            Eigen::Vector3f init_pose = {static_cast<float>(init_pose_[0]),
                                         static_cast<float>(init_pose_[1]),
                                         static_cast<float>(init_pose_[2])};
            car_->setInitPose(init_pose);
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
