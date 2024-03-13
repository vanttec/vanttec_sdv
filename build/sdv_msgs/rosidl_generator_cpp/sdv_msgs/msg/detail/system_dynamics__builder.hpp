// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sdv_msgs:msg/SystemDynamics.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__SYSTEM_DYNAMICS__BUILDER_HPP_
#define SDV_MSGS__MSG__DETAIL__SYSTEM_DYNAMICS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sdv_msgs/msg/detail/system_dynamics__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sdv_msgs
{

namespace msg
{

namespace builder
{

class Init_SystemDynamics_f
{
public:
  explicit Init_SystemDynamics_f(::sdv_msgs::msg::SystemDynamics & msg)
  : msg_(msg)
  {}
  ::sdv_msgs::msg::SystemDynamics f(::sdv_msgs::msg::SystemDynamics::_f_type arg)
  {
    msg_.f = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sdv_msgs::msg::SystemDynamics msg_;
};

class Init_SystemDynamics_g
{
public:
  Init_SystemDynamics_g()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SystemDynamics_f g(::sdv_msgs::msg::SystemDynamics::_g_type arg)
  {
    msg_.g = std::move(arg);
    return Init_SystemDynamics_f(msg_);
  }

private:
  ::sdv_msgs::msg::SystemDynamics msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sdv_msgs::msg::SystemDynamics>()
{
  return sdv_msgs::msg::builder::Init_SystemDynamics_g();
}

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__SYSTEM_DYNAMICS__BUILDER_HPP_
