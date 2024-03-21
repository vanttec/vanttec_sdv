#include "can_node_base.h"
#include "Vanttec_CANLib/CANMessage.h"
#include <std_msgs/msg/float64.hpp>
#include "std_srvs/srv/empty.hpp"

class CanNodeSDV : public CanNodeBase {
public:
    CanNodeSDV() : CanNodeBase("sdv_can_node"){
        using namespace std::placeholders;

        // Send to 0x410 (stepper board), message id: 0x01
        motor_angle_sub = this->create_subscription<std_msgs::msg::Float64>(
            "/sdv/steering/setpoint", 10, [this](const std_msgs::msg::Float64::SharedPtr msg){
                RCLCPP_INFO(this->get_logger(), "Setpoint: %f", msg->data);
                vanttec::CANMessage can_msg;
                vanttec::packFloat(can_msg, 0x01, msg->data);
                send_frame(0x410, can_msg);
            }
        );

        zero_service = this->create_service<std_srvs::srv::Empty>("/sdv/steering/reset_encoder", std::bind(&CanNodeSDV::zero_encoder, this, _1, _2));

        steering_angle_pub = this->create_publisher<std_msgs::msg::Float64>(
            "/sdv/steering/position", 10
        );
    }
protected:
    void parse_frame(const struct can_frame &frame) override {
        vanttec::CANMessage msg;
        std::copy(std::begin(frame.data), std::end(frame.data), std::begin(msg.data));
        msg.len = frame.can_dlc;
        uint8_t vttec_msg_id = vanttec::getId(msg);
        uint32_t can_id = frame.can_id;
        RCLCPP_INFO(this->get_logger(), "Got message from: %#X  with vttec id: %#X", can_id, vttec_msg_id);

        if(can_id == 0x407){
            if(vttec_msg_id == 0x03){
                std_msgs::msg::Float64 encoder_msg;
                encoder_msg.data  = vanttec::getFloat(msg);
                RCLCPP_WARN(this->get_logger(), "Got encoder message: %f", encoder_msg.data);
                steering_angle_pub->publish(encoder_msg);
            }
        }
    }

    void zero_encoder(const std::shared_ptr<std_srvs::srv::Empty::Request> request,
        std::shared_ptr<std_srvs::srv::Empty::Response> response) {
        RCLCPP_ERROR(this->get_logger(), "Setting encoder to zero");
        vanttec::CANMessage can_msg1{0x23,0x03,0x60,0x00,0x00,0x00,0x00,0x80};
        vanttec::CANMessage can_msg2{0x23,0x10,0x10,0x01,0x73,0x61,0x76,0x65};
        send_frame(0x620, can_msg1);
        send_frame(0x620, can_msg2);
    }

private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Service<std_srvs::srv::Empty>::SharedPtr zero_service;
    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr motor_angle_sub;
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr steering_angle_pub;
};

int main(int argc, char * argv[]){
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CanNodeSDV>());
  rclcpp::shutdown();
  return 0;
}
