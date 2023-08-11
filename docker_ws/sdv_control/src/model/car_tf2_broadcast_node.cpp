#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <stdio.h>
#include "nav_msgs/msg/path.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sdv_control/tf2_6dof_broadcaster_ros2.hpp"

using namespace std::chrono_literals;

class CarTf2Broadcast : public rclcpp::Node
{
  public:
    CarTf2Broadcast()
    : Node("car_t2_broadcast_node")
    {
      car_path = this->create_publisher<nav_msgs::msg::Path>("/car_simulation/car_tf_broadcast/car_path", 10);

      timer_ = this->create_wall_timer(
      100ms, std::bind(&CarTf2Broadcast::timer_callback, this));   
      }
    void configure(){
      tf_broadcaster = std::make_unique<tf2broadcaster::TF2Broadcaster>(shared_from_this(),
            parent_frame,child_frame);
    }
  private:
    void timer_callback()
    {
      car_path->publish(tf_broadcaster->path);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr car_path;
    protected:
    std::unique_ptr<tf2broadcaster::TF2Broadcaster> tf_broadcaster;
    std::string parent_frame = "world";
    std::string child_frame = "base_link";

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto merging_node = std::make_shared<CarTf2Broadcast>();
  merging_node->configure();
  rclcpp::spin(merging_node->get_node_base_interface());
  rclcpp::shutdown();
  return 0;
}