#include "can_node_base.h"
#include "Vanttec_CANLib/CANMessage.h"
#include <std_msgs/msg/float64.hpp>
#include <std_srvs/srv/empty.hpp>
#include "sdv_msgs/srv/uint8.hpp"

class CanNodeSDV : public CanNodeBase {
public:
    CanNodeSDV() : CanNodeBase("sdv_can_node"){
        using namespace std::placeholders;

        // [joystick] -> [this node] -> [stepper pcb] -> [stepper motor]
        // [this node][motor_angle_sub] : convert FLoat64 to CANMessage and send it
        motor_angle_sub = this->create_subscription<std_msgs::msg::Float64>(
            "/sdv/steering/setpoint", 10, [this](const std_msgs::msg::Float64::SharedPtr msg){
                RCLCPP_INFO(this->get_logger(), "Setpoint: %f", msg->data);
                vanttec::CANMessage can_msg;
                vanttec::packFloat(can_msg, 0x01, msg->data);
                send_frame(0x410, can_msg);
            }
        );

        // [ros] -> [this node] -> [stepper pcb] -> [stepper motor]
        // [this node][zero_service] : if called, send a CAN message to zero the encoder on current position
        zero_service = this->create_service<std_srvs::srv::Empty>(
            "/sdv/steering/reset_encoder",
            std::bind(
                &CanNodeSDV::zero_encoder, this, _1, _2
            )
        );

        // [ros] -> [this node] -> [CAN network]
        // [this node][mode_service] : will send the value of the service as the current mode to CAN 
        mode_service = this->create_service<sdv_msgs::srv::Uint8>(
            "/sdv/steering/set_mode",
            std::bind(
                &CanNodeSDV::set_mode, this, _1, _2
            )
        );
        
        // [britter encoder] -> [CAN] -> [this node] -> [ros]
        // [this node][steering_angle_pub] : convert encoder's angle to Float64 and publish it
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
        
        auto steady_clock = rclcpp::Clock();

        RCLCPP_INFO(this->get_logger(), "Got message from: %#X  with vttec id: %#X", can_id, vttec_msg_id);

        if(can_id == 0x407){
            if(vttec_msg_id == 0x03){
                std_msgs::msg::Float64 encoder_msg;
                encoder_msg.data  = vanttec::getFloat(msg);
                
                RCLCPP_WARN_THROTTLE(this->get_logger(), steady_clock, 1000, "Got encoder message: %f", encoder_msg.data);

                steering_angle_pub->publish(encoder_msg);
            }
        }
    }

    void zero_encoder(const std::shared_ptr<std_srvs::srv::Empty::Request> request,
        std::shared_ptr<std_srvs::srv::Empty::Response> response) {
        
        RCLCPP_INFO(this->get_logger(), "setting encoder to zero");

        vanttec::CANMessage set_zero_msg{0x23,0x03,0x60,0x00,0x00,0x00,0x00,0x80};
        vanttec::CANMessage store_params_msg{0x23,0x10,0x10,0x01,0x73,0x61,0x76,0x65};

        send_frame(0x620, set_zero_msg);
        send_frame(0x620, store_params_msg);
    }

    void set_mode(const std::shared_ptr<sdv_msgs::srv::Uint8::Request> request,
        std::shared_ptr<sdv_msgs::srv::Uint8::Response> response) {
        
        uint8_t data = request.get()->data;

        RCLCPP_INFO(this->get_logger(), "setting mode to %d", data);

        vanttec::CANMessage set_mode_msg{0x2, data};

        send_frame(0x410, set_mode_msg);
    }

private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Service<std_srvs::srv::Empty>::SharedPtr zero_service;
    rclcpp::Service<sdv_msgs::srv::Uint8>::SharedPtr mode_service;
    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr motor_angle_sub;
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr steering_angle_pub;
};

int main(int argc, char * argv[]){
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CanNodeSDV>());
  rclcpp::shutdown();
  return 0;
}
