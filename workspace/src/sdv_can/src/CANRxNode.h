//
// Created by Abiel on 3/22/23.
//

#ifndef SDV_CANRXNODE_H
#define SDV_CANRXNODE_H

#include "Utils/CANDeserialization.h"
#include "Utils/CANSerialization.h"
#include "CANHandler.h"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"
#include "std_msgs/msg/u_int16.hpp"

class CANRxNode : public rclcpp::Node {
 public:
  CANRxNode(const std::shared_ptr<vanttec::CANHandler> &handler);

  void update();

 private:
  std::shared_ptr<vanttec::CANHandler> handler{nullptr};
  rclcpp::TimerBase::SharedPtr updateTimer;

  rclcpp::Publisher<std_msgs::msg::UInt16>::SharedPtr pingPublisher;

  std::stringstream debugLogBuffer;

 protected:
  void handleDebugMsg(can_frame frame);

  void handlePingMsg(can_frame frame);
};

#endif  // SDV_CANRXNODE_H