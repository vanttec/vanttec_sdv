/** ----------------------------------------------------------------------------
 * @file: sdc1_simulation_node.cpp
 * @date: August 12, 2023
 * @author: Sebas Mtz
 * @email: sebas.martp@gmail.com
 * @author: Edison Altamirano
 * 
 * @brief: Self-Driving Car 1 simulation node. Based on Sebas' car dyn model.
 * -----------------------------------------------------------------------------
 **/

#include <stdio.h>
#include "rclcpp/rclcpp.hpp"

#include "vehicles/vtec_sdc1.hpp"

#include "geometry_msgs/msg/accel.hpp"
#include "std_msgs/msg/multi_array_dimension.hpp"
#include "std_msgs/msg/float32.hpp"
#include "diagnostic_msgs/msg/diagnostic_status.hpp"
#include "diagnostic_msgs/msg/key_value.hpp"

#include "sdv_msgs/msg/eta_pose.hpp"
#include "sdv_msgs/msg/system_dynamics.hpp"

using namespace std::chrono_literals;

class CarSimulationNode : public rclcpp::Node
{
  private:
    int frequency_;
    float sample_time_;

    std::unique_ptr<VTecSDC1> car_model_;
    rclcpp::TimerBase::SharedPtr timer_;
    diagnostic_msgs::msg::DiagnosticStatus throttle_diag_;

    rclcpp::Publisher<geometry_msgs::msg::Accel>::SharedPtr car_accel_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr car_vel_;
    rclcpp::Publisher<sdv_msgs::msg::EtaPose>::SharedPtr car_eta_pose_;
    rclcpp::Publisher<sdv_msgs::msg::SystemDynamics>::SharedPtr car_dynamics_;
    rclcpp::Publisher<diagnostic_msgs::msg::DiagnosticStatus>::SharedPtr diagnostics_publisher_;


    void timer_callback()
    {
      /* calculate Model States */
      car_model_->calculateStates();

      /* Publish Odometry */
      car_accel_->publish(car_model_->accelerations_);
      car_vel_->publish(car_model_->velocities_);
      car_eta_pose_->publish(car_model_->eta_pose_);

      /* Publish diagnostics */
      diagnostic_msgs::msg::KeyValue value;
      // TODO. Check for errors in throttle computation (maybe there are no real values) to updated diagnostics
      throttle_diag_.level = 0;
      value.key = "D";
      value.value = car_model_->u_(0);
      // RCLCPP_INFO(this->get_logger(), "U: %f",  car_model_->u_(0));
      
      throttle_diag_.values.push_back(value);
      diagnostics_publisher_->publish(throttle_diag_);
    }
    
  public:
    CarSimulationNode() : Node("sdc1_simulation_node")
    {
      this->declare_parameter("frequency", 0);    // Super important to get parameters from launch files!!
      this->get_parameter_or("frequency", frequency_, 100);
      sample_time_ = 1000 / static_cast<float>(frequency_);

      car_accel_ = this->create_publisher<geometry_msgs::msg::Accel>("/vectornav/ins_3d/ins_acc", 10);
      car_vel_ = this->create_publisher<geometry_msgs::msg::Twist>("/car_simulation/dynamic_model/vel", 10);
      car_eta_pose_ = this->create_publisher<sdv_msgs::msg::EtaPose>("/car_simulation/dynamic_model/eta_pose", 10);
      diagnostics_publisher_ = this->create_publisher<diagnostic_msgs::msg::DiagnosticStatus>("/diagnostics",10);

      throttle_diag_.name = "Throttle command (D)";
      throttle_diag_.message = "Expected value must be integer in the range of [0, 255]";
      throttle_diag_.hardware_id = "Throttle";

      timer_ = this->create_wall_timer(
        std::chrono::milliseconds(1000 / frequency_),
        std::bind(&CarSimulationNode::timer_callback, this));
    }

    ~CarSimulationNode(){}

    void configure()
    {
      car_model_ = std::make_unique<VTecSDC1>(sample_time_);
    }
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto model_node = std::make_shared<CarSimulationNode>();
  model_node->configure();
  rclcpp::spin(model_node->get_node_base_interface());
  rclcpp::shutdown();
  return 0;
}