// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from sdv_msgs:msg/GuidanceWaypoints.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "sdv_msgs/msg/detail/guidance_waypoints__rosidl_typesupport_introspection_c.h"
#include "sdv_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "sdv_msgs/msg/detail/guidance_waypoints__functions.h"
#include "sdv_msgs/msg/detail/guidance_waypoints__struct.h"


// Include directives for member types
// Member `waypoint_list_x`
// Member `waypoint_list_y`
// Member `waypoint_list_z`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__GuidanceWaypoints_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  sdv_msgs__msg__GuidanceWaypoints__init(message_memory);
}

void sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__GuidanceWaypoints_fini_function(void * message_memory)
{
  sdv_msgs__msg__GuidanceWaypoints__fini(message_memory);
}

size_t sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__size_function__GuidanceWaypoints__waypoint_list_x(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__get_const_function__GuidanceWaypoints__waypoint_list_x(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__get_function__GuidanceWaypoints__waypoint_list_x(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__fetch_function__GuidanceWaypoints__waypoint_list_x(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__get_const_function__GuidanceWaypoints__waypoint_list_x(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__assign_function__GuidanceWaypoints__waypoint_list_x(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__get_function__GuidanceWaypoints__waypoint_list_x(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__resize_function__GuidanceWaypoints__waypoint_list_x(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__size_function__GuidanceWaypoints__waypoint_list_y(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__get_const_function__GuidanceWaypoints__waypoint_list_y(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__get_function__GuidanceWaypoints__waypoint_list_y(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__fetch_function__GuidanceWaypoints__waypoint_list_y(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__get_const_function__GuidanceWaypoints__waypoint_list_y(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__assign_function__GuidanceWaypoints__waypoint_list_y(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__get_function__GuidanceWaypoints__waypoint_list_y(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__resize_function__GuidanceWaypoints__waypoint_list_y(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__size_function__GuidanceWaypoints__waypoint_list_z(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__get_const_function__GuidanceWaypoints__waypoint_list_z(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__get_function__GuidanceWaypoints__waypoint_list_z(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__fetch_function__GuidanceWaypoints__waypoint_list_z(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__get_const_function__GuidanceWaypoints__waypoint_list_z(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__assign_function__GuidanceWaypoints__waypoint_list_z(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__get_function__GuidanceWaypoints__waypoint_list_z(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__resize_function__GuidanceWaypoints__waypoint_list_z(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__GuidanceWaypoints_message_member_array[7] = {
  {
    "guidance_law",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__GuidanceWaypoints, guidance_law),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "waypoint_list_length",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__GuidanceWaypoints, waypoint_list_length),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "waypoint_list_x",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__GuidanceWaypoints, waypoint_list_x),  // bytes offset in struct
    NULL,  // default value
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__size_function__GuidanceWaypoints__waypoint_list_x,  // size() function pointer
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__get_const_function__GuidanceWaypoints__waypoint_list_x,  // get_const(index) function pointer
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__get_function__GuidanceWaypoints__waypoint_list_x,  // get(index) function pointer
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__fetch_function__GuidanceWaypoints__waypoint_list_x,  // fetch(index, &value) function pointer
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__assign_function__GuidanceWaypoints__waypoint_list_x,  // assign(index, value) function pointer
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__resize_function__GuidanceWaypoints__waypoint_list_x  // resize(index) function pointer
  },
  {
    "waypoint_list_y",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__GuidanceWaypoints, waypoint_list_y),  // bytes offset in struct
    NULL,  // default value
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__size_function__GuidanceWaypoints__waypoint_list_y,  // size() function pointer
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__get_const_function__GuidanceWaypoints__waypoint_list_y,  // get_const(index) function pointer
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__get_function__GuidanceWaypoints__waypoint_list_y,  // get(index) function pointer
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__fetch_function__GuidanceWaypoints__waypoint_list_y,  // fetch(index, &value) function pointer
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__assign_function__GuidanceWaypoints__waypoint_list_y,  // assign(index, value) function pointer
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__resize_function__GuidanceWaypoints__waypoint_list_y  // resize(index) function pointer
  },
  {
    "waypoint_list_z",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__GuidanceWaypoints, waypoint_list_z),  // bytes offset in struct
    NULL,  // default value
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__size_function__GuidanceWaypoints__waypoint_list_z,  // size() function pointer
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__get_const_function__GuidanceWaypoints__waypoint_list_z,  // get_const(index) function pointer
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__get_function__GuidanceWaypoints__waypoint_list_z,  // get(index) function pointer
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__fetch_function__GuidanceWaypoints__waypoint_list_z,  // fetch(index, &value) function pointer
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__assign_function__GuidanceWaypoints__waypoint_list_z,  // assign(index, value) function pointer
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__resize_function__GuidanceWaypoints__waypoint_list_z  // resize(index) function pointer
  },
  {
    "depth_setpoint",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__GuidanceWaypoints, depth_setpoint),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "heading_setpoint",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__GuidanceWaypoints, heading_setpoint),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__GuidanceWaypoints_message_members = {
  "sdv_msgs__msg",  // message namespace
  "GuidanceWaypoints",  // message name
  7,  // number of fields
  sizeof(sdv_msgs__msg__GuidanceWaypoints),
  sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__GuidanceWaypoints_message_member_array,  // message members
  sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__GuidanceWaypoints_init_function,  // function to initialize message memory (memory has to be allocated)
  sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__GuidanceWaypoints_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__GuidanceWaypoints_message_type_support_handle = {
  0,
  &sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__GuidanceWaypoints_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_sdv_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sdv_msgs, msg, GuidanceWaypoints)() {
  if (!sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__GuidanceWaypoints_message_type_support_handle.typesupport_identifier) {
    sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__GuidanceWaypoints_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &sdv_msgs__msg__GuidanceWaypoints__rosidl_typesupport_introspection_c__GuidanceWaypoints_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
