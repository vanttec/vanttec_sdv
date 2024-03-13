// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sdv_msgs:msg/EtaPose.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__ETA_POSE__BUILDER_HPP_
#define SDV_MSGS__MSG__DETAIL__ETA_POSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sdv_msgs/msg/detail/eta_pose__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sdv_msgs
{

namespace msg
{

namespace builder
{

class Init_EtaPose_psi
{
public:
  explicit Init_EtaPose_psi(::sdv_msgs::msg::EtaPose & msg)
  : msg_(msg)
  {}
  ::sdv_msgs::msg::EtaPose psi(::sdv_msgs::msg::EtaPose::_psi_type arg)
  {
    msg_.psi = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sdv_msgs::msg::EtaPose msg_;
};

class Init_EtaPose_theta
{
public:
  explicit Init_EtaPose_theta(::sdv_msgs::msg::EtaPose & msg)
  : msg_(msg)
  {}
  Init_EtaPose_psi theta(::sdv_msgs::msg::EtaPose::_theta_type arg)
  {
    msg_.theta = std::move(arg);
    return Init_EtaPose_psi(msg_);
  }

private:
  ::sdv_msgs::msg::EtaPose msg_;
};

class Init_EtaPose_phi
{
public:
  explicit Init_EtaPose_phi(::sdv_msgs::msg::EtaPose & msg)
  : msg_(msg)
  {}
  Init_EtaPose_theta phi(::sdv_msgs::msg::EtaPose::_phi_type arg)
  {
    msg_.phi = std::move(arg);
    return Init_EtaPose_theta(msg_);
  }

private:
  ::sdv_msgs::msg::EtaPose msg_;
};

class Init_EtaPose_z
{
public:
  explicit Init_EtaPose_z(::sdv_msgs::msg::EtaPose & msg)
  : msg_(msg)
  {}
  Init_EtaPose_phi z(::sdv_msgs::msg::EtaPose::_z_type arg)
  {
    msg_.z = std::move(arg);
    return Init_EtaPose_phi(msg_);
  }

private:
  ::sdv_msgs::msg::EtaPose msg_;
};

class Init_EtaPose_y
{
public:
  explicit Init_EtaPose_y(::sdv_msgs::msg::EtaPose & msg)
  : msg_(msg)
  {}
  Init_EtaPose_z y(::sdv_msgs::msg::EtaPose::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_EtaPose_z(msg_);
  }

private:
  ::sdv_msgs::msg::EtaPose msg_;
};

class Init_EtaPose_x
{
public:
  Init_EtaPose_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_EtaPose_y x(::sdv_msgs::msg::EtaPose::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_EtaPose_y(msg_);
  }

private:
  ::sdv_msgs::msg::EtaPose msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sdv_msgs::msg::EtaPose>()
{
  return sdv_msgs::msg::builder::Init_EtaPose_x();
}

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__ETA_POSE__BUILDER_HPP_
