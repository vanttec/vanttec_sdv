/** ----------------------------------------------------------------------------
 * @file: stanley_controller_node.cpp
 * @date: August 17, 2023
 * @author: Sebas Mtz
 * @email: sebas.martp@gmail.com
 *
 * @brief: Stanley Controller node.
 * -----------------------------------------------------------------------------
 **/

#include <stdio.h>
#include "rclcpp/rclcpp.hpp"

#include "controllers/guidance_laws/stanley_controller.hpp"

#include "std_msgs/msg/float32.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "geometry_msgs/msg/vector3.hpp"

#include "sdv_msgs/msg/eta_pose.hpp"
#include "vectornav_msgs/msg/ins_group.hpp"
#include "vectornav_msgs/msg/common_group.hpp"


class CarGuidanceNode : public rclcpp::Node
{
    private:
        float sample_time_;
        bool is_simulation_;
        bool vel_msgs_arrived_{false};
        std::unique_ptr<StanleyController> stanley_;

        /* Stanley Params */
        float k_{0.3};
        float k_soft_{1};
        float delta_max_{1};

        float vel_;
        std_msgs::msg::Float32 delta_;

        rclcpp::TimerBase::SharedPtr timer_;

        /* Vehicle pose */
        Point vehicle_pos_ = {0, 0};
        // float x_{0};
        // float y_{0};
        float psi_{0};

        /* Path */
        Point p1_ = {0, -10};
        Point p2_ = {0, 0};

        // float x1{0};
        // float y1{-10};
        // float x2{0};
        // float y2{10};

        /* Publishers */
        rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr car_steering_;
        // rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr follow_path;

        /* Subscribers */
        rclcpp::Subscription<sdv_msgs::msg::EtaPose>::SharedPtr car_eta_pose_;
        rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr car_velocity_;
        rclcpp::Subscription<vectornav_msgs::msg::InsGroup>::SharedPtr car_velocity_imu_;
        rclcpp::Subscription<vectornav_msgs::msg::CommonGroup>::SharedPtr current_yaw_;

        void timer_callback()
        {

            stanley_->calculateCrosstrackError(vehicle_pos_, p1_, p2_);

            stanley_->setYawAngle(psi_);
            
            if(is_simulation_){

                stanley_->calculateSteering(vel_);
                delta_.data = stanley_->delta_;
                car_steering_->publish(delta_);

            } else {

                if(vel_msgs_arrived_){
                    RCLCPP_INFO(this->get_logger(), "Vectornav vel received");
                    stanley_->calculateSteering(vel_);
                    delta_.data = stanley_->delta_;
                    car_steering_->publish(delta_);
                } else
                    RCLCPP_INFO(this->get_logger(), "Waiting for vectornav");
            
            }
        }

        void set_velocity_imu(const vectornav_msgs::msg::InsGroup::SharedPtr msg_in)
        {
            // v_norm = std::sqrt(msg_in->velbody.x * msg_in->velbody.x + msg_in->velbody.y * msg_in->velbody.y);
            vel_ = msg_in->velbody.x;
            vel_msgs_arrived_ = true;
        }

        void set_velocity(const geometry_msgs::msg::Twist::SharedPtr msg)
        {
            vel_ = msg->linear.x;
        }

        void set_sim_pose(const sdv_msgs::msg::EtaPose& msg)
        {
            vehicle_pos_.x = msg.x;
            vehicle_pos_.y = msg.y;
            psi_ = msg.psi;
        }

        // void set_real_pose(const sdv_msgs::msg::EtaPose& msg)
        // {
        //     vehicle_pos_.x = msg.x;
        //     vehicle_pos_.y = msg.y;
        //     psi_ = msg_in->yawpitchroll.x;
        // }

        void set_yaw(const vectornav_msgs::msg::CommonGroup::SharedPtr msg_in)
        {
            psi_ = msg_in->yawpitchroll.x;
        }

    public:
        CarGuidanceNode() : Node("car_guidance_node")
        {
            int frequency;

            /* Params */
            //https://roboticsbackend.com/rclcpp-params-tutorial-get-set-ros2-params-with-cpp/
            this->declare_parameter("is_simulation", rclcpp::PARAMETER_BOOL);
            this->declare_parameter("frequency", rclcpp::PARAMETER_INTEGER);    // Super important to get parameters from launch files!!
            this->declare_parameter("K", rclcpp::PARAMETER_DOUBLE);
            this->declare_parameter("K_soft", rclcpp::PARAMETER_DOUBLE);
            this->declare_parameter("Delta_max", rclcpp::PARAMETER_DOUBLE);

            frequency = this->get_parameter("frequency").as_int();
            is_simulation_ = this->get_parameter("is_simulation").as_bool();
            k_ = this->get_parameter("K").as_double();
            k_soft_ = this->get_parameter("K_soft").as_double();
            delta_max_ = this->get_parameter("Delta_max").as_double();

            sample_time_ = 1.0 / static_cast<float>(frequency);
            
            /* Publishers */
            car_steering_ = this->create_publisher<std_msgs::msg::Float32>("/car_control/control_signal/delta", 1);

            /* Subscribers */
            car_eta_pose_ = this->create_subscription<sdv_msgs::msg::EtaPose>("/car_simulation/dynamic_model/eta_pose",
                                1, std::bind(&CarGuidanceNode::set_sim_pose, this, std::placeholders::_1));

            // FALTA RECIBIR POS REAL

            car_velocity_ = this->create_subscription<geometry_msgs::msg::Twist>("/car_simulation/dynamic_model/vel",
                                1, std::bind(&CarGuidanceNode::set_velocity, this, std::placeholders::_1));
            car_velocity_imu_ = this->create_subscription<vectornav_msgs::msg::InsGroup>("/vectornav/raw/ins",
                                1, std::bind(&CarGuidanceNode::set_velocity_imu, this, std::placeholders::_1));
            current_yaw_ = this->create_subscription<vectornav_msgs::msg::CommonGroup>("/vectornav/raw/common",
                                1, std::bind(&CarGuidanceNode::set_yaw, this, std::placeholders::_1));

            timer_ = this->create_wall_timer( std::chrono::milliseconds(1000 / frequency),
                                                std::bind(&CarGuidanceNode::timer_callback, this));
        }

        ~CarGuidanceNode(){stanley_.reset();}

        void configure(){
            stanley_ = std::make_unique<StanleyController>(delta_max_, k_, k_soft_);
        }
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto guidance_node = std::make_shared<CarGuidanceNode>();
    guidance_node->configure();
    rclcpp::spin(guidance_node->get_node_base_interface());
    rclcpp::shutdown();
    return 0;
}
