#include <stdio.h>

#include "rclcpp/rclcpp.hpp"

#include "vehicles/vtec_sdc1.hpp"

#include "sdv_msgs/msg/eta_pose.hpp"
#include "sdv_msgs/msg/system_dynamics.hpp"
#include "std_msgs/msg/multi_array_dimension.hpp"
#include "std_msgs/msg/float32.hpp"
#include "geometry_msgs/msg/accel.hpp"

using namespace std::chrono_literals;

class CarSimulationNode : public rclcpp::Node
{
  public:
    CarSimulationNode()
    : Node("car_simulation_node")
    {
      car_accel = this->create_publisher<geometry_msgs::msg::Accel>("/vectornav/ins_3d/ins_acc", 10);
      car_vel = this->create_publisher<geometry_msgs::msg::Twist>("/car_simulation/dynamic_model/vel", 10);
      car_eta_pose = this->create_publisher<sdv_msgs::msg::EtaPose>("/car_simulation/dynamic_model/eta_pose", 10);
      car_dynamics = this->create_publisher<sdv_msgs::msg::SystemDynamics>("/car_simulation/dynamic_model/non_linear_functions", 10);
      debug_publisher = this->create_publisher<std_msgs::msg::Float32>("/debug",10);

       timer_ = this->create_wall_timer(
       100ms, std::bind(&CarSimulationNode::timer_callback, this));

      car_functions.g.layout.dim.push_back(std_msgs::msg::MultiArrayDimension());
      car_functions.g.layout.dim.push_back(std_msgs::msg::MultiArrayDimension());
      car_functions.g.layout.dim[0].label = "rows";
      car_functions.g.layout.dim[1].label = "cols";
      car_functions.g.layout.dim[0].size = 3;
      car_functions.g.layout.dim[1].size = 3;
      car_functions.g.layout.dim[0].stride = 3;
      car_functions.g.layout.data_offset = 0;
 
    }
    void configure(){
      car_model = std::make_unique<cafe::Cafe>(shared_from_this(),
            sample_time);
    }
  private:
     void timer_callback()
     {
      //     /* calculate Model States */
      car_model->calculateStates();

      //     /* Publish Odometry */
       car_accel->publish(car_model->accelerations_);
       car_vel->publish(car_model->velocities_);
       car_eta_pose->publish(car_model->eta_pose_);
       /* Publish nonlinear functions */

       car_functions.f = {car_model->f_(0), car_model->f_(1), car_model->f_(2)};
       car_functions.g.data = { car_model->g_(0,0), car_model->g_(0,1), car_model->g_(0,2),
                                 car_model->g_(1,0), car_model->g_(1,1), car_model->g_(1,2),
                                 car_model->g_(2,0), car_model->g_(2,1), car_model->g_(2,2)}; 
       car_dynamics->publish(car_functions);
       std_msgs::msg::Float32 debug;
       debug.data= car_model->F_throttle_;
       debug_publisher->publish(debug);
    }
    int frequency = 100;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Accel>::SharedPtr car_accel;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr car_vel;
    rclcpp::Publisher<sdv_msgs::msg::EtaPose>::SharedPtr car_eta_pose;
    rclcpp::Publisher<sdv_msgs::msg::SystemDynamics>::SharedPtr car_dynamics;
    sdv_msgs::msg::SystemDynamics car_functions;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr debug_publisher;

    float sample_time = 1.0/frequency;
    protected:
    std::unique_ptr<cafe::Cafe> car_model;

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto merging_node = std::make_shared<CarSimulationNode>();
  merging_node->configure();
  rclcpp::spin(merging_node->get_node_base_interface());
  rclcpp::shutdown();
  return 0;
}