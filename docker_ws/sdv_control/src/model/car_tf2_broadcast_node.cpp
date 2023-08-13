/** ----------------------------------------------------------------------------
 * @file: car_tf2_broadcast_node.cpp
 * @date: August 12, 2023
 * @author: Sebas Mtz
 * @author: Edison Altamirano
 * 
 * @brief: tf2 broadcast node for RViz
 * -----------------------------------------------------------------------------
 **/

#include <chrono>
#include <stdio.h>
#include "rclcpp/rclcpp.hpp"

#include "simulation/tf2_6dof_broadcaster_ros2.hpp"

#include "nav_msgs/msg/path.hpp"

using namespace std::chrono_literals;

class CarTf2Broadcast : public rclcpp::Node
{
  private:
    int frequency_;

    rclcpp::TimerBase::SharedPtr timer_;
    std::unique_ptr<TF2Broadcaster> tf_broadcaster_;
    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr car_path_;

    std::string parent_frame = "world";
    std::string child_frame = "base_link";

    void timer_callback()
    {
      car_path_->publish(tf_broadcaster_->path_);
    }

  public:
    CarTf2Broadcast() : Node("car_t2_broadcast_node")
    {
      this->declare_parameter("frequency", 0);    // Super important to get parameters from launch files!!
      this->get_parameter_or("frequency", frequency_, 100);

      car_path_ = this->create_publisher<nav_msgs::msg::Path>("/car_simulation/car_tf_broadcast/car_path", 10);

      timer_ = this->create_wall_timer(
        std::chrono::milliseconds(1000 / frequency_),
        std::bind(&CarTf2Broadcast::timer_callback, this));   
    }

    ~CarTf2Broadcast(){}

    void configure()
    {
      tf_broadcaster_ = std::make_unique<TF2Broadcaster>(shared_from_this(),
            parent_frame, child_frame);
    }

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto tf2_node = std::make_shared<CarTf2Broadcast>();
  tf2_node->configure();
  rclcpp::spin(tf2_node->get_node_base_interface());
  rclcpp::shutdown();
  return 0;
}