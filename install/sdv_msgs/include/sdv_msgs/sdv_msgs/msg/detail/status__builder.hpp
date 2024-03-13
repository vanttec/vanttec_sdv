// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sdv_msgs:msg/Status.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__STATUS__BUILDER_HPP_
#define SDV_MSGS__MSG__DETAIL__STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sdv_msgs/msg/detail/status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sdv_msgs
{

namespace msg
{

namespace builder
{

class Init_Status_synchronous_mode_running
{
public:
  explicit Init_Status_synchronous_mode_running(::sdv_msgs::msg::Status & msg)
  : msg_(msg)
  {}
  ::sdv_msgs::msg::Status synchronous_mode_running(::sdv_msgs::msg::Status::_synchronous_mode_running_type arg)
  {
    msg_.synchronous_mode_running = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sdv_msgs::msg::Status msg_;
};

class Init_Status_synchronous_mode
{
public:
  explicit Init_Status_synchronous_mode(::sdv_msgs::msg::Status & msg)
  : msg_(msg)
  {}
  Init_Status_synchronous_mode_running synchronous_mode(::sdv_msgs::msg::Status::_synchronous_mode_type arg)
  {
    msg_.synchronous_mode = std::move(arg);
    return Init_Status_synchronous_mode_running(msg_);
  }

private:
  ::sdv_msgs::msg::Status msg_;
};

class Init_Status_fixed_delta_seconds
{
public:
  explicit Init_Status_fixed_delta_seconds(::sdv_msgs::msg::Status & msg)
  : msg_(msg)
  {}
  Init_Status_synchronous_mode fixed_delta_seconds(::sdv_msgs::msg::Status::_fixed_delta_seconds_type arg)
  {
    msg_.fixed_delta_seconds = std::move(arg);
    return Init_Status_synchronous_mode(msg_);
  }

private:
  ::sdv_msgs::msg::Status msg_;
};

class Init_Status_frame
{
public:
  Init_Status_frame()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Status_fixed_delta_seconds frame(::sdv_msgs::msg::Status::_frame_type arg)
  {
    msg_.frame = std::move(arg);
    return Init_Status_fixed_delta_seconds(msg_);
  }

private:
  ::sdv_msgs::msg::Status msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sdv_msgs::msg::Status>()
{
  return sdv_msgs::msg::builder::Init_Status_frame();
}

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__STATUS__BUILDER_HPP_
