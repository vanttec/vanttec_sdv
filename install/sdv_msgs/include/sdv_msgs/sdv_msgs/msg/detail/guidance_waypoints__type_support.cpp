// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from sdv_msgs:msg/GuidanceWaypoints.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "sdv_msgs/msg/detail/guidance_waypoints__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace sdv_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void GuidanceWaypoints_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) sdv_msgs::msg::GuidanceWaypoints(_init);
}

void GuidanceWaypoints_fini_function(void * message_memory)
{
  auto typed_message = static_cast<sdv_msgs::msg::GuidanceWaypoints *>(message_memory);
  typed_message->~GuidanceWaypoints();
}

size_t size_function__GuidanceWaypoints__waypoint_list_x(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GuidanceWaypoints__waypoint_list_x(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__GuidanceWaypoints__waypoint_list_x(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__GuidanceWaypoints__waypoint_list_x(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__GuidanceWaypoints__waypoint_list_x(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__GuidanceWaypoints__waypoint_list_x(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__GuidanceWaypoints__waypoint_list_x(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__GuidanceWaypoints__waypoint_list_x(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

size_t size_function__GuidanceWaypoints__waypoint_list_y(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GuidanceWaypoints__waypoint_list_y(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__GuidanceWaypoints__waypoint_list_y(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__GuidanceWaypoints__waypoint_list_y(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__GuidanceWaypoints__waypoint_list_y(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__GuidanceWaypoints__waypoint_list_y(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__GuidanceWaypoints__waypoint_list_y(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__GuidanceWaypoints__waypoint_list_y(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

size_t size_function__GuidanceWaypoints__waypoint_list_z(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GuidanceWaypoints__waypoint_list_z(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__GuidanceWaypoints__waypoint_list_z(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__GuidanceWaypoints__waypoint_list_z(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__GuidanceWaypoints__waypoint_list_z(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__GuidanceWaypoints__waypoint_list_z(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__GuidanceWaypoints__waypoint_list_z(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__GuidanceWaypoints__waypoint_list_z(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember GuidanceWaypoints_message_member_array[7] = {
  {
    "guidance_law",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs::msg::GuidanceWaypoints, guidance_law),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "waypoint_list_length",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs::msg::GuidanceWaypoints, waypoint_list_length),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "waypoint_list_x",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs::msg::GuidanceWaypoints, waypoint_list_x),  // bytes offset in struct
    nullptr,  // default value
    size_function__GuidanceWaypoints__waypoint_list_x,  // size() function pointer
    get_const_function__GuidanceWaypoints__waypoint_list_x,  // get_const(index) function pointer
    get_function__GuidanceWaypoints__waypoint_list_x,  // get(index) function pointer
    fetch_function__GuidanceWaypoints__waypoint_list_x,  // fetch(index, &value) function pointer
    assign_function__GuidanceWaypoints__waypoint_list_x,  // assign(index, value) function pointer
    resize_function__GuidanceWaypoints__waypoint_list_x  // resize(index) function pointer
  },
  {
    "waypoint_list_y",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs::msg::GuidanceWaypoints, waypoint_list_y),  // bytes offset in struct
    nullptr,  // default value
    size_function__GuidanceWaypoints__waypoint_list_y,  // size() function pointer
    get_const_function__GuidanceWaypoints__waypoint_list_y,  // get_const(index) function pointer
    get_function__GuidanceWaypoints__waypoint_list_y,  // get(index) function pointer
    fetch_function__GuidanceWaypoints__waypoint_list_y,  // fetch(index, &value) function pointer
    assign_function__GuidanceWaypoints__waypoint_list_y,  // assign(index, value) function pointer
    resize_function__GuidanceWaypoints__waypoint_list_y  // resize(index) function pointer
  },
  {
    "waypoint_list_z",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs::msg::GuidanceWaypoints, waypoint_list_z),  // bytes offset in struct
    nullptr,  // default value
    size_function__GuidanceWaypoints__waypoint_list_z,  // size() function pointer
    get_const_function__GuidanceWaypoints__waypoint_list_z,  // get_const(index) function pointer
    get_function__GuidanceWaypoints__waypoint_list_z,  // get(index) function pointer
    fetch_function__GuidanceWaypoints__waypoint_list_z,  // fetch(index, &value) function pointer
    assign_function__GuidanceWaypoints__waypoint_list_z,  // assign(index, value) function pointer
    resize_function__GuidanceWaypoints__waypoint_list_z  // resize(index) function pointer
  },
  {
    "depth_setpoint",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs::msg::GuidanceWaypoints, depth_setpoint),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "heading_setpoint",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs::msg::GuidanceWaypoints, heading_setpoint),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers GuidanceWaypoints_message_members = {
  "sdv_msgs::msg",  // message namespace
  "GuidanceWaypoints",  // message name
  7,  // number of fields
  sizeof(sdv_msgs::msg::GuidanceWaypoints),
  GuidanceWaypoints_message_member_array,  // message members
  GuidanceWaypoints_init_function,  // function to initialize message memory (memory has to be allocated)
  GuidanceWaypoints_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t GuidanceWaypoints_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GuidanceWaypoints_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace sdv_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<sdv_msgs::msg::GuidanceWaypoints>()
{
  return &::sdv_msgs::msg::rosidl_typesupport_introspection_cpp::GuidanceWaypoints_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, sdv_msgs, msg, GuidanceWaypoints)() {
  return &::sdv_msgs::msg::rosidl_typesupport_introspection_cpp::GuidanceWaypoints_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
