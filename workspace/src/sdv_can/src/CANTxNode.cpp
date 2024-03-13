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

  vel_sub = this->create_subscription<geometry_msgs::msg::Twist>(
      "cmd_vel", 10, [this](const geometry_msgs::msg::Twist &msg){
        vanttec::CANMessage steerMsg;
        // steerMsg.id = 1;
        vanttec::packFloat(steerMsg, 0x01, msg.angular.z);
        this->handler->update_write();
        this->handler->write(steerMsg);
      });

  steering_sub = this->create_subscription<geometry_msgs::msg::Vector3>(
      "steering_brake", 10, std::bind(&CANTxNode::steering_callback, this, _1));
      
  updateTimer =
      this->create_wall_timer(10ms, std::bind(&CANTxNode::update, this));
}

void CANTxNode::update() { handler->update_write(); }

void CANTxNode::steering_callback(const geometry_msgs::msg::Vector3 &msg) {
  // RCLCPP_INFO(this->get_logger(), "Message received");

  // Steppers msg: ID #STEPS1 #STEPS2 X DIR
  uint32_t stpr_frame = 0;
  uint8_t dir = msg.x > 0 ? 1:(msg.x < 0 ? 0:2); // Normal -> CW:0, CCW:1, but inverted due to gears
  uint16_t steps = (uint16_t) msg.y;

  // stpr_frame |= steps << 16;
  // stpr_frame |= 0x000000FF & dir;

  // printf("Steps: %X, Dir: %X\n", steps, dir);
  // printf("%X \n", stpr_frame);

  // RCLCPP_WARN(this->get_logger(),"SDFFFF%d", dir);


  // if (msg == lastMotorArray) return;
  // vanttec::CANMessage steerMsg;
  // // steerMsg.id = 1;
  // vanttec::packByte(steerMsg, 0x10, dir);

  // handler->write(steerMsg);

/*
  vanttec::CANMessage brakeMsg;
  float brake = msg.z;
  vanttec::packFloat(brakeMsg, 0x17, brake);

  handler->write(brakeMsg);
*/
  // lastMotorArray = msg;
}
