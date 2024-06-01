// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sdv_msgs:msg/ThrottleMsg.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__THROTTLE_MSG__BUILDER_HPP_
#define SDV_MSGS__MSG__DETAIL__THROTTLE_MSG__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sdv_msgs/msg/detail/throttle_msg__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sdv_msgs
{

namespace msg
{

namespace builder
{

class Init_ThrottleMsg_pot_mode
{
public:
  explicit Init_ThrottleMsg_pot_mode(::sdv_msgs::msg::ThrottleMsg & msg)
  : msg_(msg)
  {}
  ::sdv_msgs::msg::ThrottleMsg pot_mode(::sdv_msgs::msg::ThrottleMsg::_pot_mode_type arg)
  {
    msg_.pot_mode = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sdv_msgs::msg::ThrottleMsg msg_;
};

class Init_ThrottleMsg_car_mode
{
public:
  explicit Init_ThrottleMsg_car_mode(::sdv_msgs::msg::ThrottleMsg & msg)
  : msg_(msg)
  {}
  Init_ThrottleMsg_pot_mode car_mode(::sdv_msgs::msg::ThrottleMsg::_car_mode_type arg)
  {
    msg_.car_mode = std::move(arg);
    return Init_ThrottleMsg_pot_mode(msg_);
  }

private:
  ::sdv_msgs::msg::ThrottleMsg msg_;
};

class Init_ThrottleMsg_decrease_maxvel
{
public:
  explicit Init_ThrottleMsg_decrease_maxvel(::sdv_msgs::msg::ThrottleMsg & msg)
  : msg_(msg)
  {}
  Init_ThrottleMsg_car_mode decrease_maxvel(::sdv_msgs::msg::ThrottleMsg::_decrease_maxvel_type arg)
  {
    msg_.decrease_maxvel = std::move(arg);
    return Init_ThrottleMsg_car_mode(msg_);
  }

private:
  ::sdv_msgs::msg::ThrottleMsg msg_;
};

class Init_ThrottleMsg_increase_maxvel
{
public:
  explicit Init_ThrottleMsg_increase_maxvel(::sdv_msgs::msg::ThrottleMsg & msg)
  : msg_(msg)
  {}
  Init_ThrottleMsg_decrease_maxvel increase_maxvel(::sdv_msgs::msg::ThrottleMsg::_increase_maxvel_type arg)
  {
    msg_.increase_maxvel = std::move(arg);
    return Init_ThrottleMsg_decrease_maxvel(msg_);
  }

private:
  ::sdv_msgs::msg::ThrottleMsg msg_;
};

class Init_ThrottleMsg_pot
{
public:
  explicit Init_ThrottleMsg_pot(::sdv_msgs::msg::ThrottleMsg & msg)
  : msg_(msg)
  {}
  Init_ThrottleMsg_increase_maxvel pot(::sdv_msgs::msg::ThrottleMsg::_pot_type arg)
  {
    msg_.pot = std::move(arg);
    return Init_ThrottleMsg_increase_maxvel(msg_);
  }

private:
  ::sdv_msgs::msg::ThrottleMsg msg_;
};

class Init_ThrottleMsg_maxvel
{
public:
  Init_ThrottleMsg_maxvel()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ThrottleMsg_pot maxvel(::sdv_msgs::msg::ThrottleMsg::_maxvel_type arg)
  {
    msg_.maxvel = std::move(arg);
    return Init_ThrottleMsg_pot(msg_);
  }

private:
  ::sdv_msgs::msg::ThrottleMsg msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sdv_msgs::msg::ThrottleMsg>()
{
  return sdv_msgs::msg::builder::Init_ThrottleMsg_maxvel();
}

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__THROTTLE_MSG__BUILDER_HPP_
