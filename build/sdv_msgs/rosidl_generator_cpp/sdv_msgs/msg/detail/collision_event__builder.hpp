// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sdv_msgs:msg/CollisionEvent.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__COLLISION_EVENT__BUILDER_HPP_
#define SDV_MSGS__MSG__DETAIL__COLLISION_EVENT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sdv_msgs/msg/detail/collision_event__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sdv_msgs
{

namespace msg
{

namespace builder
{

class Init_CollisionEvent_normal_impulse
{
public:
  explicit Init_CollisionEvent_normal_impulse(::sdv_msgs::msg::CollisionEvent & msg)
  : msg_(msg)
  {}
  ::sdv_msgs::msg::CollisionEvent normal_impulse(::sdv_msgs::msg::CollisionEvent::_normal_impulse_type arg)
  {
    msg_.normal_impulse = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sdv_msgs::msg::CollisionEvent msg_;
};

class Init_CollisionEvent_other_actor_id
{
public:
  explicit Init_CollisionEvent_other_actor_id(::sdv_msgs::msg::CollisionEvent & msg)
  : msg_(msg)
  {}
  Init_CollisionEvent_normal_impulse other_actor_id(::sdv_msgs::msg::CollisionEvent::_other_actor_id_type arg)
  {
    msg_.other_actor_id = std::move(arg);
    return Init_CollisionEvent_normal_impulse(msg_);
  }

private:
  ::sdv_msgs::msg::CollisionEvent msg_;
};

class Init_CollisionEvent_header
{
public:
  Init_CollisionEvent_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CollisionEvent_other_actor_id header(::sdv_msgs::msg::CollisionEvent::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_CollisionEvent_other_actor_id(msg_);
  }

private:
  ::sdv_msgs::msg::CollisionEvent msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sdv_msgs::msg::CollisionEvent>()
{
  return sdv_msgs::msg::builder::Init_CollisionEvent_header();
}

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__COLLISION_EVENT__BUILDER_HPP_
