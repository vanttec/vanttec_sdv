// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sdv_msgs:msg/VehicleControl.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__VEHICLE_CONTROL__BUILDER_HPP_
#define SDV_MSGS__MSG__DETAIL__VEHICLE_CONTROL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sdv_msgs/msg/detail/vehicle_control__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sdv_msgs
{

namespace msg
{

namespace builder
{

class Init_VehicleControl_manual_gear_shift
{
public:
  explicit Init_VehicleControl_manual_gear_shift(::sdv_msgs::msg::VehicleControl & msg)
  : msg_(msg)
  {}
  ::sdv_msgs::msg::VehicleControl manual_gear_shift(::sdv_msgs::msg::VehicleControl::_manual_gear_shift_type arg)
  {
    msg_.manual_gear_shift = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleControl msg_;
};

class Init_VehicleControl_gear
{
public:
  explicit Init_VehicleControl_gear(::sdv_msgs::msg::VehicleControl & msg)
  : msg_(msg)
  {}
  Init_VehicleControl_manual_gear_shift gear(::sdv_msgs::msg::VehicleControl::_gear_type arg)
  {
    msg_.gear = std::move(arg);
    return Init_VehicleControl_manual_gear_shift(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleControl msg_;
};

class Init_VehicleControl_reverse
{
public:
  explicit Init_VehicleControl_reverse(::sdv_msgs::msg::VehicleControl & msg)
  : msg_(msg)
  {}
  Init_VehicleControl_gear reverse(::sdv_msgs::msg::VehicleControl::_reverse_type arg)
  {
    msg_.reverse = std::move(arg);
    return Init_VehicleControl_gear(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleControl msg_;
};

class Init_VehicleControl_hand_brake
{
public:
  explicit Init_VehicleControl_hand_brake(::sdv_msgs::msg::VehicleControl & msg)
  : msg_(msg)
  {}
  Init_VehicleControl_reverse hand_brake(::sdv_msgs::msg::VehicleControl::_hand_brake_type arg)
  {
    msg_.hand_brake = std::move(arg);
    return Init_VehicleControl_reverse(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleControl msg_;
};

class Init_VehicleControl_brake
{
public:
  explicit Init_VehicleControl_brake(::sdv_msgs::msg::VehicleControl & msg)
  : msg_(msg)
  {}
  Init_VehicleControl_hand_brake brake(::sdv_msgs::msg::VehicleControl::_brake_type arg)
  {
    msg_.brake = std::move(arg);
    return Init_VehicleControl_hand_brake(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleControl msg_;
};

class Init_VehicleControl_steer
{
public:
  explicit Init_VehicleControl_steer(::sdv_msgs::msg::VehicleControl & msg)
  : msg_(msg)
  {}
  Init_VehicleControl_brake steer(::sdv_msgs::msg::VehicleControl::_steer_type arg)
  {
    msg_.steer = std::move(arg);
    return Init_VehicleControl_brake(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleControl msg_;
};

class Init_VehicleControl_throttle
{
public:
  explicit Init_VehicleControl_throttle(::sdv_msgs::msg::VehicleControl & msg)
  : msg_(msg)
  {}
  Init_VehicleControl_steer throttle(::sdv_msgs::msg::VehicleControl::_throttle_type arg)
  {
    msg_.throttle = std::move(arg);
    return Init_VehicleControl_steer(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleControl msg_;
};

class Init_VehicleControl_header
{
public:
  Init_VehicleControl_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VehicleControl_throttle header(::sdv_msgs::msg::VehicleControl::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_VehicleControl_throttle(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleControl msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sdv_msgs::msg::VehicleControl>()
{
  return sdv_msgs::msg::builder::Init_VehicleControl_header();
}

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__VEHICLE_CONTROL__BUILDER_HPP_
