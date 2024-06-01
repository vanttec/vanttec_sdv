// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sdv_msgs:msg/ThrustControl.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__THRUST_CONTROL__BUILDER_HPP_
#define SDV_MSGS__MSG__DETAIL__THRUST_CONTROL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sdv_msgs/msg/detail/thrust_control__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sdv_msgs
{

namespace msg
{

namespace builder
{

class Init_ThrustControl_tau_psi
{
public:
  explicit Init_ThrustControl_tau_psi(::sdv_msgs::msg::ThrustControl & msg)
  : msg_(msg)
  {}
  ::sdv_msgs::msg::ThrustControl tau_psi(::sdv_msgs::msg::ThrustControl::_tau_psi_type arg)
  {
    msg_.tau_psi = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sdv_msgs::msg::ThrustControl msg_;
};

class Init_ThrustControl_tau_theta
{
public:
  explicit Init_ThrustControl_tau_theta(::sdv_msgs::msg::ThrustControl & msg)
  : msg_(msg)
  {}
  Init_ThrustControl_tau_psi tau_theta(::sdv_msgs::msg::ThrustControl::_tau_theta_type arg)
  {
    msg_.tau_theta = std::move(arg);
    return Init_ThrustControl_tau_psi(msg_);
  }

private:
  ::sdv_msgs::msg::ThrustControl msg_;
};

class Init_ThrustControl_tau_phi
{
public:
  explicit Init_ThrustControl_tau_phi(::sdv_msgs::msg::ThrustControl & msg)
  : msg_(msg)
  {}
  Init_ThrustControl_tau_theta tau_phi(::sdv_msgs::msg::ThrustControl::_tau_phi_type arg)
  {
    msg_.tau_phi = std::move(arg);
    return Init_ThrustControl_tau_theta(msg_);
  }

private:
  ::sdv_msgs::msg::ThrustControl msg_;
};

class Init_ThrustControl_tau_z
{
public:
  explicit Init_ThrustControl_tau_z(::sdv_msgs::msg::ThrustControl & msg)
  : msg_(msg)
  {}
  Init_ThrustControl_tau_phi tau_z(::sdv_msgs::msg::ThrustControl::_tau_z_type arg)
  {
    msg_.tau_z = std::move(arg);
    return Init_ThrustControl_tau_phi(msg_);
  }

private:
  ::sdv_msgs::msg::ThrustControl msg_;
};

class Init_ThrustControl_tau_y
{
public:
  explicit Init_ThrustControl_tau_y(::sdv_msgs::msg::ThrustControl & msg)
  : msg_(msg)
  {}
  Init_ThrustControl_tau_z tau_y(::sdv_msgs::msg::ThrustControl::_tau_y_type arg)
  {
    msg_.tau_y = std::move(arg);
    return Init_ThrustControl_tau_z(msg_);
  }

private:
  ::sdv_msgs::msg::ThrustControl msg_;
};

class Init_ThrustControl_tau_x
{
public:
  Init_ThrustControl_tau_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ThrustControl_tau_y tau_x(::sdv_msgs::msg::ThrustControl::_tau_x_type arg)
  {
    msg_.tau_x = std::move(arg);
    return Init_ThrustControl_tau_y(msg_);
  }

private:
  ::sdv_msgs::msg::ThrustControl msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sdv_msgs::msg::ThrustControl>()
{
  return sdv_msgs::msg::builder::Init_ThrustControl_tau_x();
}

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__THRUST_CONTROL__BUILDER_HPP_
