#include "can_node_base.h"
#include "Vanttec_CANLib/CANMessage.h"
#include <std_msgs/msg/float64.hpp>

class CanNodeSDV : public CanNodeBase {
public:
    CanNodeSDV() : CanNodeBase("sdv_can_node"){

        // Send to 0x410 (stepper board), message id: 0x01
        motor_angle_sub_ = this->create_subscription<std_msgs::msg::Float64>(
            "sdv/steering/setpoint", 10, [this](const std_msgs::msg::Float64::SharedPtr msg){
                RCLCPP_INFO(this->get_logger(), "Setpoint: %f", msg->data);
                vanttec::CANMessage can_msg;
                vanttec::packFloat(can_msg, 0x01, msg->data);
                send_frame(0x410, can_msg);
            }
        );

    }
protected:
    void parse_frame(const struct can_frame &frame) override {
        vanttec::CANMessage msg;
        std::copy(std::begin(frame.data), std::end(frame.data), std::begin(msg.data));
        msg.len = frame.can_dlc;
        uint8_t vttec_msg_id = vanttec::getId(msg);
        uint32_t can_id = frame.can_id;
        RCLCPP_INFO(this->get_logger(), "Got message from: %#X", can_id);

        // TODO Main parsing switch here...
    }

private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr motor_angle_sub_;
};

int main(int argc, char * argv[]){
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CanNodeSDV>());
  rclcpp::shutdown();
  return 0;
}
