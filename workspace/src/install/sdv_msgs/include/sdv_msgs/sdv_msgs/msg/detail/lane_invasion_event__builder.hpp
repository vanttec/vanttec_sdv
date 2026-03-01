// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sdv_msgs:msg/LaneInvasionEvent.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__LANE_INVASION_EVENT__BUILDER_HPP_
#define SDV_MSGS__MSG__DETAIL__LANE_INVASION_EVENT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sdv_msgs/msg/detail/lane_invasion_event__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sdv_msgs
{

namespace msg
{

namespace builder
{

class Init_LaneInvasionEvent_crossed_lane_markings
{
public:
  explicit Init_LaneInvasionEvent_crossed_lane_markings(::sdv_msgs::msg::LaneInvasionEvent & msg)
  : msg_(msg)
  {}
  ::sdv_msgs::msg::LaneInvasionEvent crossed_lane_markings(::sdv_msgs::msg::LaneInvasionEvent::_crossed_lane_markings_type arg)
  {
    msg_.crossed_lane_markings = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sdv_msgs::msg::LaneInvasionEvent msg_;
};

class Init_LaneInvasionEvent_header
{
public:
  Init_LaneInvasionEvent_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LaneInvasionEvent_crossed_lane_markings header(::sdv_msgs::msg::LaneInvasionEvent::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_LaneInvasionEvent_crossed_lane_markings(msg_);
  }

private:
  ::sdv_msgs::msg::LaneInvasionEvent msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sdv_msgs::msg::LaneInvasionEvent>()
{
  return sdv_msgs::msg::builder::Init_LaneInvasionEvent_header();
}

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__LANE_INVASION_EVENT__BUILDER_HPP_
