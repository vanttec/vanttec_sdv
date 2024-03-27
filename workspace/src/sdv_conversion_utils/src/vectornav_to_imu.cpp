#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "vectornav_msgs/msg/common_group.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class VectornavToImuNode : public rclcpp::Node {
public:
  VectornavToImuNode() : Node("vectornav_to_imu") {
    imu_publisher_ = this->create_publisher<sensor_msgs::msg::Imu>("/imu", 10);

    vectornav_subscription_ =
        this->create_subscription<vectornav_msgs::msg::CommonGroup>(
            "/vectornav/raw/common", 10,
            std::bind(&VectornavToImuNode::vectornav_callback, this, _1));
  }

private:
  void vectornav_callback(
      const vectornav_msgs::msg::CommonGroup::SharedPtr vn_msg) const {
    sensor_msgs::msg::Imu imu_msg;

    imu_msg.header.stamp = vn_msg->header.stamp;
    imu_msg.orientation = vn_msg->quaternion;
    imu_msg.angular_velocity = vn_msg->angularrate;
    imu_msg.linear_acceleration = vn_msg->accel;

    imu_publisher_->publish(imu_msg);
  }

  rclcpp::Subscription<vectornav_msgs::msg::CommonGroup>::SharedPtr
      vectornav_subscription_;
  rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr imu_publisher_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<VectornavToImuNode>());
  rclcpp::shutdown();
  return 0;
}