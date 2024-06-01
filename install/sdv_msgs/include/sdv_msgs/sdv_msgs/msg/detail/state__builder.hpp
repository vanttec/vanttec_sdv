// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sdv_msgs:msg/State.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__STATE__BUILDER_HPP_
#define SDV_MSGS__MSG__DETAIL__STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sdv_msgs/msg/detail/state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sdv_msgs
{

namespace msg
{

namespace builder
{

class Init_State_accx
{
public:
  explicit Init_State_accx(::sdv_msgs::msg::State & msg)
  : msg_(msg)
  {}
  ::sdv_msgs::msg::State accx(::sdv_msgs::msg::State::_accx_type arg)
  {
    msg_.accx = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sdv_msgs::msg::State msg_;
};

class Init_State_steer
{
public:
  explicit Init_State_steer(::sdv_msgs::msg::State & msg)
  : msg_(msg)
  {}
  Init_State_accx steer(::sdv_msgs::msg::State::_steer_type arg)
  {
    msg_.steer = std::move(arg);
    return Init_State_accx(msg_);
  }

private:
  ::sdv_msgs::msg::State msg_;
};

class Init_State_vx
{
public:
  explicit Init_State_vx(::sdv_msgs::msg::State & msg)
  : msg_(msg)
  {}
  Init_State_steer vx(::sdv_msgs::msg::State::_vx_type arg)
  {
    msg_.vx = std::move(arg);
    return Init_State_steer(msg_);
  }

private:
  ::sdv_msgs::msg::State msg_;
};

class Init_State_yaw
{
public:
  explicit Init_State_yaw(::sdv_msgs::msg::State & msg)
  : msg_(msg)
  {}
  Init_State_vx yaw(::sdv_msgs::msg::State::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return Init_State_vx(msg_);
  }

private:
  ::sdv_msgs::msg::State msg_;
};

class Init_State_y
{
public:
  explicit Init_State_y(::sdv_msgs::msg::State & msg)
  : msg_(msg)
  {}
  Init_State_yaw y(::sdv_msgs::msg::State::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_State_yaw(msg_);
  }

private:
  ::sdv_msgs::msg::State msg_;
};

class Init_State_x
{
public:
  Init_State_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_State_y x(::sdv_msgs::msg::State::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_State_y(msg_);
  }

private:
  ::sdv_msgs::msg::State msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sdv_msgs::msg::State>()
{
  return sdv_msgs::msg::builder::Init_State_x();
}

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__STATE__BUILDER_HPP_
