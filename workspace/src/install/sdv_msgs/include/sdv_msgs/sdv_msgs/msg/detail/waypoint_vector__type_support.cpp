// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from sdv_msgs:msg/WaypointVector.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "sdv_msgs/msg/detail/waypoint_vector__struct.hpp"
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

void WaypointVector_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) sdv_msgs::msg::WaypointVector(_init);
}

void WaypointVector_fini_function(void * message_memory)
{
  auto typed_message = static_cast<sdv_msgs::msg::WaypointVector *>(message_memory);
  typed_message->~WaypointVector();
}

size_t size_function__WaypointVector__x_list(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__WaypointVector__x_list(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__WaypointVector__x_list(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__WaypointVector__x_list(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__WaypointVector__x_list(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__WaypointVector__x_list(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__WaypointVector__x_list(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__WaypointVector__x_list(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

size_t size_function__WaypointVector__y_list(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__WaypointVector__y_list(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__WaypointVector__y_list(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__WaypointVector__y_list(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__WaypointVector__y_list(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__WaypointVector__y_list(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__WaypointVector__y_list(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__WaypointVector__y_list(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember WaypointVector_message_member_array[2] = {
  {
    "x_list",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs::msg::WaypointVector, x_list),  // bytes offset in struct
    nullptr,  // default value
    size_function__WaypointVector__x_list,  // size() function pointer
    get_const_function__WaypointVector__x_list,  // get_const(index) function pointer
    get_function__WaypointVector__x_list,  // get(index) function pointer
    fetch_function__WaypointVector__x_list,  // fetch(index, &value) function pointer
    assign_function__WaypointVector__x_list,  // assign(index, value) function pointer
    resize_function__WaypointVector__x_list  // resize(index) function pointer
  },
  {
    "y_list",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs::msg::WaypointVector, y_list),  // bytes offset in struct
    nullptr,  // default value
    size_function__WaypointVector__y_list,  // size() function pointer
    get_const_function__WaypointVector__y_list,  // get_const(index) function pointer
    get_function__WaypointVector__y_list,  // get(index) function pointer
    fetch_function__WaypointVector__y_list,  // fetch(index, &value) function pointer
    assign_function__WaypointVector__y_list,  // assign(index, value) function pointer
    resize_function__WaypointVector__y_list  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers WaypointVector_message_members = {
  "sdv_msgs::msg",  // message namespace
  "WaypointVector",  // message name
  2,  // number of fields
  sizeof(sdv_msgs::msg::WaypointVector),
  WaypointVector_message_member_array,  // message members
  WaypointVector_init_function,  // function to initialize message memory (memory has to be allocated)
  WaypointVector_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t WaypointVector_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &WaypointVector_message_members,
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
get_message_type_support_handle<sdv_msgs::msg::WaypointVector>()
{
  return &::sdv_msgs::msg::rosidl_typesupport_introspection_cpp::WaypointVector_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, sdv_msgs, msg, WaypointVector)() {
  return &::sdv_msgs::msg::rosidl_typesupport_introspection_cpp::WaypointVector_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
