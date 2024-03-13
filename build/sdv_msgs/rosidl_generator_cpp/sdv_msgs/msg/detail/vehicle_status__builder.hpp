// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sdv_msgs:msg/VehicleStatus.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__VEHICLE_STATUS__BUILDER_HPP_
#define SDV_MSGS__MSG__DETAIL__VEHICLE_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sdv_msgs/msg/detail/vehicle_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sdv_msgs
{

namespace msg
{

namespace builder
{

class Init_VehicleStatus_control
{
public:
  explicit Init_VehicleStatus_control(::sdv_msgs::msg::VehicleStatus & msg)
  : msg_(msg)
  {}
  ::sdv_msgs::msg::VehicleStatus control(::sdv_msgs::msg::VehicleStatus::_control_type arg)
  {
    msg_.control = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleStatus msg_;
};

class Init_VehicleStatus_orientation
{
public:
  explicit Init_VehicleStatus_orientation(::sdv_msgs::msg::VehicleStatus & msg)
  : msg_(msg)
  {}
  Init_VehicleStatus_control orientation(::sdv_msgs::msg::VehicleStatus::_orientation_type arg)
  {
    msg_.orientation = std::move(arg);
    return Init_VehicleStatus_control(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleStatus msg_;
};

class Init_VehicleStatus_acceleration
{
public:
  explicit Init_VehicleStatus_acceleration(::sdv_msgs::msg::VehicleStatus & msg)
  : msg_(msg)
  {}
  Init_VehicleStatus_orientation acceleration(::sdv_msgs::msg::VehicleStatus::_acceleration_type arg)
  {
    msg_.acceleration = std::move(arg);
    return Init_VehicleStatus_orientation(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleStatus msg_;
};

class Init_VehicleStatus_velocity
{
public:
  explicit Init_VehicleStatus_velocity(::sdv_msgs::msg::VehicleStatus & msg)
  : msg_(msg)
  {}
  Init_VehicleStatus_acceleration velocity(::sdv_msgs::msg::VehicleStatus::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_VehicleStatus_acceleration(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleStatus msg_;
};

class Init_VehicleStatus_header
{
public:
  Init_VehicleStatus_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VehicleStatus_velocity header(::sdv_msgs::msg::VehicleStatus::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_VehicleStatus_velocity(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sdv_msgs::msg::VehicleStatus>()
{
  return sdv_msgs::msg::builder::Init_VehicleStatus_header();
}

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__VEHICLE_STATUS__BUILDER_HPP_
