// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sdv_msgs:msg/VehicleInfoWheel.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__VEHICLE_INFO_WHEEL__BUILDER_HPP_
#define SDV_MSGS__MSG__DETAIL__VEHICLE_INFO_WHEEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sdv_msgs/msg/detail/vehicle_info_wheel__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sdv_msgs
{

namespace msg
{

namespace builder
{

class Init_VehicleInfoWheel_position
{
public:
  explicit Init_VehicleInfoWheel_position(::sdv_msgs::msg::VehicleInfoWheel & msg)
  : msg_(msg)
  {}
  ::sdv_msgs::msg::VehicleInfoWheel position(::sdv_msgs::msg::VehicleInfoWheel::_position_type arg)
  {
    msg_.position = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleInfoWheel msg_;
};

class Init_VehicleInfoWheel_max_handbrake_torque
{
public:
  explicit Init_VehicleInfoWheel_max_handbrake_torque(::sdv_msgs::msg::VehicleInfoWheel & msg)
  : msg_(msg)
  {}
  Init_VehicleInfoWheel_position max_handbrake_torque(::sdv_msgs::msg::VehicleInfoWheel::_max_handbrake_torque_type arg)
  {
    msg_.max_handbrake_torque = std::move(arg);
    return Init_VehicleInfoWheel_position(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleInfoWheel msg_;
};

class Init_VehicleInfoWheel_max_brake_torque
{
public:
  explicit Init_VehicleInfoWheel_max_brake_torque(::sdv_msgs::msg::VehicleInfoWheel & msg)
  : msg_(msg)
  {}
  Init_VehicleInfoWheel_max_handbrake_torque max_brake_torque(::sdv_msgs::msg::VehicleInfoWheel::_max_brake_torque_type arg)
  {
    msg_.max_brake_torque = std::move(arg);
    return Init_VehicleInfoWheel_max_handbrake_torque(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleInfoWheel msg_;
};

class Init_VehicleInfoWheel_radius
{
public:
  explicit Init_VehicleInfoWheel_radius(::sdv_msgs::msg::VehicleInfoWheel & msg)
  : msg_(msg)
  {}
  Init_VehicleInfoWheel_max_brake_torque radius(::sdv_msgs::msg::VehicleInfoWheel::_radius_type arg)
  {
    msg_.radius = std::move(arg);
    return Init_VehicleInfoWheel_max_brake_torque(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleInfoWheel msg_;
};

class Init_VehicleInfoWheel_max_steer_angle
{
public:
  explicit Init_VehicleInfoWheel_max_steer_angle(::sdv_msgs::msg::VehicleInfoWheel & msg)
  : msg_(msg)
  {}
  Init_VehicleInfoWheel_radius max_steer_angle(::sdv_msgs::msg::VehicleInfoWheel::_max_steer_angle_type arg)
  {
    msg_.max_steer_angle = std::move(arg);
    return Init_VehicleInfoWheel_radius(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleInfoWheel msg_;
};

class Init_VehicleInfoWheel_damping_rate
{
public:
  explicit Init_VehicleInfoWheel_damping_rate(::sdv_msgs::msg::VehicleInfoWheel & msg)
  : msg_(msg)
  {}
  Init_VehicleInfoWheel_max_steer_angle damping_rate(::sdv_msgs::msg::VehicleInfoWheel::_damping_rate_type arg)
  {
    msg_.damping_rate = std::move(arg);
    return Init_VehicleInfoWheel_max_steer_angle(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleInfoWheel msg_;
};

class Init_VehicleInfoWheel_tire_friction
{
public:
  Init_VehicleInfoWheel_tire_friction()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VehicleInfoWheel_damping_rate tire_friction(::sdv_msgs::msg::VehicleInfoWheel::_tire_friction_type arg)
  {
    msg_.tire_friction = std::move(arg);
    return Init_VehicleInfoWheel_damping_rate(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleInfoWheel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sdv_msgs::msg::VehicleInfoWheel>()
{
  return sdv_msgs::msg::builder::Init_VehicleInfoWheel_tire_friction();
}

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__VEHICLE_INFO_WHEEL__BUILDER_HPP_
