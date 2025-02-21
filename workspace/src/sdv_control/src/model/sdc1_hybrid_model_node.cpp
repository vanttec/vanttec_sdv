/** ----------------------------------------------------------------------------
 * @file: sdc1_hybrid_model_node.cpp
 * @date: Feb 6, 2025
 * @author: Sebas Mtz
 * @email: sebas.martp@gmail.com
 *
 * @brief: Self-Driving Car 1 Hybrid Dynamic Model Sim node.
 * -----------------------------------------------------------------------------
 **/

#include <stdio.h>
#include <cstdio>
#include "rclcpp/rclcpp.hpp"

#include "geometry_msgs/msg/vector3.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "rclcpp/rclcpp.hpp"

#include "geometry_msgs/msg/accel.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "std_msgs/msg/u_int8.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

#include "sdv_msgs/msg/eta_pose.hpp"
#include "sdv_msgs/msg/nonlinear_functions.hpp"

#include "dynamic_models/ground_vehicles/car_like/vehicles/vtec_sdc1_hybrid.hpp"


class SDC1ModelNode : public rclcpp::Node
{
 	private:
        float sample_time_;
        uint8_t D_MAX_;
        std::vector<double> init_pose_{0,0,0};
		uint8_t D_;

		// sdv_msgs::msg::NonlinearFunctions nlfunc_msg_;
        bool throttle_changed_ = false;

        /* Publishers */
		rclcpp::Publisher<sdv_msgs::msg::NonlinearFunctions>::SharedPtr non_linear_func_pub_;
		
        rclcpp::Publisher<geometry_msgs::msg::Accel>::SharedPtr car_accel_;
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr car_vel_;
        rclcpp::Publisher<sdv_msgs::msg::EtaPose>::SharedPtr car_eta_pose_;
        rclcpp::Publisher<std_msgs::msg::UInt8>::SharedPtr throttle_;
        rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr car_steering_;

		rclcpp::TimerBase::SharedPtr sim_timer_;
		rclcpp::TimerBase::SharedPtr pub_timer_;
		rclcpp::TimerBase::SharedPtr throttle_timer_;

		geometry_msgs::msg::Accel accel_;
		geometry_msgs::msg::Twist vel_;
		sdv_msgs::msg::EtaPose pose_;
		std_msgs::msg::UInt8 D_msg_;
		std_msgs::msg::Float32 delta_;

        /* Subscribers */
		// rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr throttle_sub_;

		/* Model */
        std::unique_ptr<VTecSDC1HybridModel> sdc1_;

        void throttle_timer_callback() {
            // Change throttle value
			D_ = 0;	// Adjust this value as needed

            // Set flag to indicate throttle has been changed
            throttle_changed_ = true;

            // Optionally, you can cancel the timer here if you only want the change to happen once
            throttle_timer_->cancel();
        }

		void update() {

            if (!throttle_changed_) {
				D_ = 90;
            }
			sdc1_->setThrottle(D_);

			sdc1_->calculateModelParams();
			sdc1_->computeDynamics();

			pose_.x = sdc1_->eta_pose_(0);
			pose_.y = sdc1_->eta_pose_(1);
			pose_.psi = sdc1_->eta_pose_(2);

			vel_.linear.x = sdc1_->velocities_(0);
			vel_.linear.y = sdc1_->velocities_(1);
			vel_.angular.z = sdc1_->velocities_(2);

			accel_.linear.x = sdc1_->accelerations_(0);
			accel_.linear.y = sdc1_->accelerations_(1);
			accel_.angular.z = sdc1_->accelerations_(2);

			D_msg_.data = D_;
		
           	delta_.data = sdc1_->delta_;

			// psi = std::fmod(psi + M_PI, 2*M_PI) - M_PI; // [-pi, pi]

			// nlfunc_msg_.f_x = sdc1_->get_f_();
			// nlfunc_msg_.g_x = sdc1_->get_g_();
		}

		void pub_timer_callback() {
			car_accel_->publish(accel_);
			car_vel_->publish(vel_);
			car_eta_pose_->publish(pose_);
			throttle_->publish(D_msg_);
            car_steering_->publish(delta_);
			// non_linear_func_pub_->publish(nlfunc_msg_);
		}

	public:
		SDC1ModelNode() : Node("sdc1_model_node")
		{
			// using namespace std::placeholders;
            int frequency = 100;

            /* Params */
            // this->declare_parameter("frequency", rclcpp::PARAMETER_INTEGER);    // Super important to get parameters from launch files!!
            this->declare_parameter("D_MAX", rclcpp::PARAMETER_INTEGER);
            // this->declare_parameter("init_pose", rclcpp::PARAMETER_DOUBLE_ARRAY);

            // frequency = this->get_parameter("frequency").as_int();
            // this->get_parameter_or("frequency", frequency, static_cast<int>(100));
            this->get_parameter_or("D_MAX", D_MAX_, static_cast<uint8_t>(90));
            // this->get_parameter_or("init_pose", D_MAX_, static_cast<uint8_t>(90));
            // init_pose_ = this->get_parameter("init_pose").as_double_array();

            sample_time_ = 1.0 / static_cast<float>(frequency);

            /* Publishers */
			car_accel_ = this->create_publisher<geometry_msgs::msg::Accel>("/sdc_simulation/dynamic_model/accel", 10);
			car_vel_ = this->create_publisher<geometry_msgs::msg::Twist>("/sdc_simulation/dynamic_model/vel", 10);
			car_eta_pose_ = this->create_publisher<sdv_msgs::msg::EtaPose>("/sdc_simulation/dynamic_model/eta_pose", 10);
            throttle_ = this->create_publisher<std_msgs::msg::UInt8>("/sdc_control/control_signal/D",10);
            car_steering_ = this->create_publisher<std_msgs::msg::Float32>("/sdc_control/control_signal/delta",10);
			non_linear_func_pub_ = this->create_publisher<sdv_msgs::msg::NonlinearFunctions>("/sdc_control/nonlinear_functions", 10);
    
            /* Subscribers */
			// throttle_sub_ = this->create_subscription<std_msgs::msg::Float64>(
				// "/sdv_control/set_throttle", 10,
				// [this](const std_msgs::msg::Float64 &msg) {
				// 	sdc1_->setThrottle(msg.data);
				// });

			sim_timer_ = this->create_wall_timer( std::chrono::milliseconds(static_cast<int>(1000 / frequency)),
											  std::bind(&SDC1ModelNode::update, this));
			throttle_timer_ = this->create_wall_timer(
								std::chrono::milliseconds(static_cast<int>(26.2 * 1000)),
								std::bind(&SDC1ModelNode::throttle_timer_callback, this));
			pub_timer_ = this->create_wall_timer(
								std::chrono::milliseconds(100),
								std::bind(&SDC1ModelNode::pub_timer_callback, this));
		
		}
		
        ~SDC1ModelNode(){} // Destructor

        void configure(){
			sdc1_ = std::make_unique<VTecSDC1HybridModel>(sample_time_, D_MAX_,
							"/docker-ros/ws/src/tests/GRU/test5/gru_residual_dynamics.pt");
            // Eigen::Vector3f init_pose = {static_cast<float>(init_pose_[0]),
            //                              static_cast<float>(init_pose_[1]),
            //                              static_cast<float>(init_pose_[2])};

            Eigen::Vector3f init_pose = {0,
                                         0,
                                         0};
            sdc1_->setInitPose(init_pose);
        }

};

int main(int argc, char **argv) {
	rclcpp::init(argc, argv);
    auto model_node = std::make_shared<SDC1ModelNode>();
    model_node->configure();
	rclcpp::spin(model_node->get_node_base_interface());
	rclcpp::shutdown();
	return 0;
}