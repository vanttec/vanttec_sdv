//
// Created by Abiel on 3/22/23.
//

#include "CANTxNode.h"

using namespace std::chrono_literals;
using namespace std::placeholders;

CANTxNode::CANTxNode(const std::shared_ptr<vanttec::CANHandler> &handler)
    : Node("CANTxNode") {

  RCLCPP_INFO(this->get_logger(), "Starting CAN Tx");

  this->handler = handler;

  steering_sub = this->create_subscription<geometry_msgs::msg::Vector3>(
      "steering", 10, std::bind(&CANTxNode::steering_callback, this, _1));
      
  updateTimer =
      this->create_wall_timer(10ms, std::bind(&CANTxNode::update, this));
}

void CANTxNode::update() { handler->update_write(); }

void CANTxNode::steering_callback(const geometry_msgs::msg::Vector3 &msg) {
  // RCLCPP_INFO(this->get_logger(), "Message received");

  // Steppers msg: ID #STEPS1 #STEPS2 X DIR
  uint32_t stpr_frame = 0;
  int8_t dir = msg.x > 0 ? 0:(msg.x < 0 ? 1:2); //CW:0, CCW:1, IDLE:2
  uint16_t steps = (uint16_t) msg.y;

  stpr_frame |= steps << 16;
  stpr_frame |= 0x000000FF & dir;

  // printf("Steps: %X, Dir: %X\n", steps, dir);
  // printf("%X \n", stpr_frame);

  if (msg == lastMotorArray) return;
  vanttec::CANMessage canMsg;
  vanttec::packLong(canMsg, 0x16, stpr_frame);
  handler->write(canMsg);

  lastMotorArray = msg;
}