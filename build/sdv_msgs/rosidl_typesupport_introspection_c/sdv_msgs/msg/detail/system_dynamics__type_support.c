// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from sdv_msgs:msg/SystemDynamics.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "sdv_msgs/msg/detail/system_dynamics__rosidl_typesupport_introspection_c.h"
#include "sdv_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "sdv_msgs/msg/detail/system_dynamics__functions.h"
#include "sdv_msgs/msg/detail/system_dynamics__struct.h"


// Include directives for member types
// Member `g`
#include "std_msgs/msg/float32_multi_array.h"
// Member `g`
#include "std_msgs/msg/detail/float32_multi_array__rosidl_typesupport_introspection_c.h"
// Member `f`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__SystemDynamics_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  sdv_msgs__msg__SystemDynamics__init(message_memory);
}

void sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__SystemDynamics_fini_function(void * message_memory)
{
  sdv_msgs__msg__SystemDynamics__fini(message_memory);
}

size_t sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__size_function__SystemDynamics__f(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__get_const_function__SystemDynamics__f(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__get_function__SystemDynamics__f(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__fetch_function__SystemDynamics__f(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__get_const_function__SystemDynamics__f(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__assign_function__SystemDynamics__f(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__get_function__SystemDynamics__f(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__resize_function__SystemDynamics__f(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__SystemDynamics_message_member_array[2] = {
  {
    "g",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__SystemDynamics, g),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "f",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__SystemDynamics, f),  // bytes offset in struct
    NULL,  // default value
    sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__size_function__SystemDynamics__f,  // size() function pointer
    sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__get_const_function__SystemDynamics__f,  // get_const(index) function pointer
    sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__get_function__SystemDynamics__f,  // get(index) function pointer
    sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__fetch_function__SystemDynamics__f,  // fetch(index, &value) function pointer
    sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__assign_function__SystemDynamics__f,  // assign(index, value) function pointer
    sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__resize_function__SystemDynamics__f  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__SystemDynamics_message_members = {
  "sdv_msgs__msg",  // message namespace
  "SystemDynamics",  // message name
  2,  // number of fields
  sizeof(sdv_msgs__msg__SystemDynamics),
  sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__SystemDynamics_message_member_array,  // message members
  sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__SystemDynamics_init_function,  // function to initialize message memory (memory has to be allocated)
  sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__SystemDynamics_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__SystemDynamics_message_type_support_handle = {
  0,
  &sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__SystemDynamics_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_sdv_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sdv_msgs, msg, SystemDynamics)() {
  sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__SystemDynamics_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Float32MultiArray)();
  if (!sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__SystemDynamics_message_type_support_handle.typesupport_identifier) {
    sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__SystemDynamics_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &sdv_msgs__msg__SystemDynamics__rosidl_typesupport_introspection_c__SystemDynamics_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
