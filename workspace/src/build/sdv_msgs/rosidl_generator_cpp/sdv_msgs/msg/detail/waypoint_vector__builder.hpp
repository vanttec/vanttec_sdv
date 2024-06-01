// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sdv_msgs:msg/WaypointVector.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__WAYPOINT_VECTOR__BUILDER_HPP_
#define SDV_MSGS__MSG__DETAIL__WAYPOINT_VECTOR__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sdv_msgs/msg/detail/waypoint_vector__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sdv_msgs
{

namespace msg
{

namespace builder
{

class Init_WaypointVector_y_list
{
public:
  explicit Init_WaypointVector_y_list(::sdv_msgs::msg::WaypointVector & msg)
  : msg_(msg)
  {}
  ::sdv_msgs::msg::WaypointVector y_list(::sdv_msgs::msg::WaypointVector::_y_list_type arg)
  {
    msg_.y_list = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sdv_msgs::msg::WaypointVector msg_;
};

class Init_WaypointVector_x_list
{
public:
  Init_WaypointVector_x_list()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_WaypointVector_y_list x_list(::sdv_msgs::msg::WaypointVector::_x_list_type arg)
  {
    msg_.x_list = std::move(arg);
    return Init_WaypointVector_y_list(msg_);
  }

private:
  ::sdv_msgs::msg::WaypointVector msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sdv_msgs::msg::WaypointVector>()
{
  return sdv_msgs::msg::builder::Init_WaypointVector_x_list();
}

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__WAYPOINT_VECTOR__BUILDER_HPP_
