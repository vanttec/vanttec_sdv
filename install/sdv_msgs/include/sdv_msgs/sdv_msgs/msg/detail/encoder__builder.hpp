// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sdv_msgs:msg/Encoder.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__ENCODER__BUILDER_HPP_
#define SDV_MSGS__MSG__DETAIL__ENCODER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sdv_msgs/msg/detail/encoder__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sdv_msgs
{

namespace msg
{

namespace builder
{

class Init_Encoder_turn
{
public:
  explicit Init_Encoder_turn(::sdv_msgs::msg::Encoder & msg)
  : msg_(msg)
  {}
  ::sdv_msgs::msg::Encoder turn(::sdv_msgs::msg::Encoder::_turn_type arg)
  {
    msg_.turn = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sdv_msgs::msg::Encoder msg_;
};

class Init_Encoder_angle
{
public:
  explicit Init_Encoder_angle(::sdv_msgs::msg::Encoder & msg)
  : msg_(msg)
  {}
  Init_Encoder_turn angle(::sdv_msgs::msg::Encoder::_angle_type arg)
  {
    msg_.angle = std::move(arg);
    return Init_Encoder_turn(msg_);
  }

private:
  ::sdv_msgs::msg::Encoder msg_;
};

class Init_Encoder_abs_angle
{
public:
  Init_Encoder_abs_angle()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Encoder_angle abs_angle(::sdv_msgs::msg::Encoder::_abs_angle_type arg)
  {
    msg_.abs_angle = std::move(arg);
    return Init_Encoder_angle(msg_);
  }

private:
  ::sdv_msgs::msg::Encoder msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sdv_msgs::msg::Encoder>()
{
  return sdv_msgs::msg::builder::Init_Encoder_abs_angle();
}

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__ENCODER__BUILDER_HPP_
