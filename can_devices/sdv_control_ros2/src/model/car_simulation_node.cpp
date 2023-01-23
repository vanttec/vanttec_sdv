//int main(int argc, char **argv){
//    int frequency = 100;
    // ros::init(argc, argv, "el_rasho_simulation_node");
    // ros::NodeHandle nh("~");

    // nh.getParam("node_frequency",frequency);    
    // ros::Rate cycle_rate(frequency);
    // Cafe car_model(float(1.0/frequency));
    // vanttec_msgs::SystemDynamics  car_functions;
    
    // ros::Publisher  car_accel     = nh.advertise<geometry_msgs::Vector3>("/vectornav/ins_3d/ins_acc", 10);
    // ros::Publisher  car_vel       = nh.advertise<geometry_msgs::Twist>("/car_simulation/dynamic_model/vel", 10);
    // ros::Publisher  car_eta_pose  = nh.advertise<vanttec_msgs::EtaPose>("/car_simulation/dynamic_model/eta_pose", 10);
    // ros::Publisher  car_dynamics  = nh.advertise<vanttec_msgs::SystemDynamics>("/car_simulation/dynamic_model/non_linear_functions", 10);

    // ros::Subscriber car_force_input = nh.subscribe("/car_control/car_control_node/force", 
    //                                                 10, 
    //                                                 &CarDynamicModel::setForceInput,
    //                                                 dynamic_cast<CarDynamicModel*> (&car_model));

    // ros::Subscriber car_steering_input = nh.subscribe("/car_control/car_control_node/steering", 
    //                                                 10, 
    //                                                 &CarDynamicModel::setSteeringInput,
    //                                                 dynamic_cast<CarDynamicModel*> (&car_model));
            
    // car_functions.g.layout.dim.push_back(std_msgs::MultiArrayDimension());
    // car_functions.g.layout.dim.push_back(std_msgs::MultiArrayDimension());
    // car_functions.g.layout.dim[0].label = "rows";
    // car_functions.g.layout.dim[1].label = "cols";
    // car_functions.g.layout.dim[0].size = 3;
    // car_functions.g.layout.dim[1].size = 3;
    // car_functions.g.layout.dim[0].stride = 3;
    // car_functions.g.layout.data_offset = 0;

    // while(ros::ok())
    // {
    //     /* Run Queued Callbacks */
    //     ros::spinOnce();

    //     /* calculate Model States */
    //     car_model.calculateStates();

    //     /* Publish Odometry */
    //     car_accel.publish(car_model.accelerations_);
    //     car_vel.publish(car_model.velocities_);
    //     car_eta_pose.publish(car_model.eta_pose_);
        
    //     /* Publish nonlinear functions */

    //     car_functions.f = {car_model.f_(0), car_model.f_(1), car_model.f_(2)};
    //     car_functions.g.data = { car_model.g_(0,0), car_model.g_(0,1), car_model.g_(0,2),
    //                              car_model.g_(1,0), car_model.g_(1,1), car_model.g_(1,2),
    //                              car_model.g_(2,0), car_model.g_(2,1), car_model.g_(2,2)};
        
    //     car_dynamics.publish(car_functions);

    //     /* Sleep for 10ms */
    //     cycle_rate.sleep();
    //}

//   return 0;
//}

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include "sdv_control_ros2/el_rasho.hpp"
#include "sdv_control_ros2/car_3dof_dynamic_model.hpp"
#include "sdv_msg/msg/eta_pose.hpp"
#include "sdv_msg/msg/system_dynamics.hpp"
#include "std_msgs/msg/multi_array_dimension.hpp"
#include "std_msgs/msg/float32.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include <stdio.h>
#include "rclcpp/rclcpp.hpp"
#include <pluginlib/class_loader.hpp>

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class CarSimulationNode : public rclcpp::Node
{
  public:
    CarSimulationNode()
    : Node("minimal_publisher")
    {
      car_accel = this->create_publisher<geometry_msgs::msg::Vector3>("/vectornav/ins_3d/ins_acc", 10);
      car_vel = this->create_publisher<geometry_msgs::msg::Twist>("/car_simulation/dynamic_model/vel", 10);
      car_eta_pose = this->create_publisher<sdv_msg::msg::EtaPose>("/car_simulation/dynamic_model/eta_pose", 10);
      car_dynamics = this->create_publisher<sdv_msg::msg::SystemDynamics>("/car_simulation/dynamic_model/non_linear_functions", 10);

      timer_ = this->create_wall_timer(
      500ms, std::bind(&CarSimulationNode::timer_callback, this));
      //model = std::make_unique<CarDynamicModel>(shared_from_this());

      // ros::Subscriber car_steering_input = nh.subscribe("/car_control/car_control_node/steering", 
      //                                                 10, 
      //                                                 &CarDynamicModel::setSteeringInput,
      //                                                 dynamic_cast<CarDynamicModel*> (&car_model));
      //float a = car_model.B_
      car_functions.g.layout.dim.push_back(std_msgs::msg::MultiArrayDimension());
      car_functions.g.layout.dim.push_back(std_msgs::msg::MultiArrayDimension());
      car_functions.g.layout.dim[0].label = "rows";
      car_functions.g.layout.dim[1].label = "cols";
      car_functions.g.layout.dim[0].size = 3;
      car_functions.g.layout.dim[1].size = 3;
      car_functions.g.layout.dim[0].stride = 3;
      car_functions.g.layout.data_offset = 0;
    }

  private:
    void timer_callback()
    {
        
       // car_accel->publish(car_model.accelerations_);
        // car_vel->publish(car_model.velocities_);
        // car_eta_pose->publish(car_model.eta_pose_);
        //auto message = std_msgs::msg::String();
        //message.data = "Hello, world! " + std::to_string(count_++);
        //RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        //car_accel->publish(message);
    }
    int frequency = 100;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr car_accel;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr car_vel;
    rclcpp::Publisher<sdv_msg::msg::EtaPose>::SharedPtr car_eta_pose;
    rclcpp::Publisher<sdv_msg::msg::SystemDynamics>::SharedPtr car_dynamics;
    float sample_time = 1.0/frequency;
    //dynamic_model::Cafe car_model(float sample_time);
    // pluginlib::ClassLoader<cardynamicmodel::CarDynamicModel> poly_loader("cardynamicmodel", "cardynamicmodel::CarDynamicModel");
    // std::shared_ptr<cardynamicmodel::CarDynamicModel> car_model = poly_loader.createSharedInstance("dynamic_model::Cafe");
    sdv_msg::msg::SystemDynamics  car_functions;

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CarSimulationNode>());
  rclcpp::shutdown();
  return 0;
}