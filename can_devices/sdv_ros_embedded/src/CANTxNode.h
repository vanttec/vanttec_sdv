//
// Created by Abiel on 3/22/23.
//

#ifndef USV_ROS2_CANTXNODE_H
#define USV_ROS2_CANTXNODE_H

#include "Vanttec_CANLib/Utils/CANDeserialization.h"
#include "Vanttec_CANLib/Utils/CANSerialization.h"
#include "Vanttec_CANLib_Linux/CANHandler.h"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"
#include "std_msgs/msg/u_int16.hpp"
#include "geometry_msgs/msg/vector3.hpp"

class CANTxNode : public rclcpp::Node {
 public:
  CANTxNode(const std::shared_ptr<vanttec::CANHandler> &handler);
  void update();

 private:
  std::shared_ptr<vanttec::CANHandler> handler{nullptr};
  rclcpp::TimerBase::SharedPtr updateTimer;

  rclcpp::Subscription<geometry_msgs::msg::Vector3>::SharedPtr steering_sub;
  geometry_msgs::msg::Vector3 lastMotorArray{geometry_msgs::msg::Vector3()};

 protected:
  void steering_callback(const geometry_msgs::msg::Vector3 &msg);
};

#endif  // USV_ROS2_CANTXNODE_H