// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sdv_msgs:msg/GuidanceWaypoints.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__GUIDANCE_WAYPOINTS__BUILDER_HPP_
#define SDV_MSGS__MSG__DETAIL__GUIDANCE_WAYPOINTS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sdv_msgs/msg/detail/guidance_waypoints__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sdv_msgs
{

namespace msg
{

namespace builder
{

class Init_GuidanceWaypoints_heading_setpoint
{
public:
  explicit Init_GuidanceWaypoints_heading_setpoint(::sdv_msgs::msg::GuidanceWaypoints & msg)
  : msg_(msg)
  {}
  ::sdv_msgs::msg::GuidanceWaypoints heading_setpoint(::sdv_msgs::msg::GuidanceWaypoints::_heading_setpoint_type arg)
  {
    msg_.heading_setpoint = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sdv_msgs::msg::GuidanceWaypoints msg_;
};

class Init_GuidanceWaypoints_depth_setpoint
{
public:
  explicit Init_GuidanceWaypoints_depth_setpoint(::sdv_msgs::msg::GuidanceWaypoints & msg)
  : msg_(msg)
  {}
  Init_GuidanceWaypoints_heading_setpoint depth_setpoint(::sdv_msgs::msg::GuidanceWaypoints::_depth_setpoint_type arg)
  {
    msg_.depth_setpoint = std::move(arg);
    return Init_GuidanceWaypoints_heading_setpoint(msg_);
  }

private:
  ::sdv_msgs::msg::GuidanceWaypoints msg_;
};

class Init_GuidanceWaypoints_waypoint_list_z
{
public:
  explicit Init_GuidanceWaypoints_waypoint_list_z(::sdv_msgs::msg::GuidanceWaypoints & msg)
  : msg_(msg)
  {}
  Init_GuidanceWaypoints_depth_setpoint waypoint_list_z(::sdv_msgs::msg::GuidanceWaypoints::_waypoint_list_z_type arg)
  {
    msg_.waypoint_list_z = std::move(arg);
    return Init_GuidanceWaypoints_depth_setpoint(msg_);
  }

private:
  ::sdv_msgs::msg::GuidanceWaypoints msg_;
};

class Init_GuidanceWaypoints_waypoint_list_y
{
public:
  explicit Init_GuidanceWaypoints_waypoint_list_y(::sdv_msgs::msg::GuidanceWaypoints & msg)
  : msg_(msg)
  {}
  Init_GuidanceWaypoints_waypoint_list_z waypoint_list_y(::sdv_msgs::msg::GuidanceWaypoints::_waypoint_list_y_type arg)
  {
    msg_.waypoint_list_y = std::move(arg);
    return Init_GuidanceWaypoints_waypoint_list_z(msg_);
  }

private:
  ::sdv_msgs::msg::GuidanceWaypoints msg_;
};

class Init_GuidanceWaypoints_waypoint_list_x
{
public:
  explicit Init_GuidanceWaypoints_waypoint_list_x(::sdv_msgs::msg::GuidanceWaypoints & msg)
  : msg_(msg)
  {}
  Init_GuidanceWaypoints_waypoint_list_y waypoint_list_x(::sdv_msgs::msg::GuidanceWaypoints::_waypoint_list_x_type arg)
  {
    msg_.waypoint_list_x = std::move(arg);
    return Init_GuidanceWaypoints_waypoint_list_y(msg_);
  }

private:
  ::sdv_msgs::msg::GuidanceWaypoints msg_;
};

class Init_GuidanceWaypoints_waypoint_list_length
{
public:
  explicit Init_GuidanceWaypoints_waypoint_list_length(::sdv_msgs::msg::GuidanceWaypoints & msg)
  : msg_(msg)
  {}
  Init_GuidanceWaypoints_waypoint_list_x waypoint_list_length(::sdv_msgs::msg::GuidanceWaypoints::_waypoint_list_length_type arg)
  {
    msg_.waypoint_list_length = std::move(arg);
    return Init_GuidanceWaypoints_waypoint_list_x(msg_);
  }

private:
  ::sdv_msgs::msg::GuidanceWaypoints msg_;
};

class Init_GuidanceWaypoints_guidance_law
{
public:
  Init_GuidanceWaypoints_guidance_law()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GuidanceWaypoints_waypoint_list_length guidance_law(::sdv_msgs::msg::GuidanceWaypoints::_guidance_law_type arg)
  {
    msg_.guidance_law = std::move(arg);
    return Init_GuidanceWaypoints_waypoint_list_length(msg_);
  }

private:
  ::sdv_msgs::msg::GuidanceWaypoints msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sdv_msgs::msg::GuidanceWaypoints>()
{
  return sdv_msgs::msg::builder::Init_GuidanceWaypoints_guidance_law();
}

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__GUIDANCE_WAYPOINTS__BUILDER_HPP_
