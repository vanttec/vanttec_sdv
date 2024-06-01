// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from sdv_msgs:msg/VehicleInfo.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "sdv_msgs/msg/detail/vehicle_info__rosidl_typesupport_introspection_c.h"
#include "sdv_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "sdv_msgs/msg/detail/vehicle_info__functions.h"
#include "sdv_msgs/msg/detail/vehicle_info__struct.h"


// Include directives for member types
// Member `type`
// Member `rolename`
#include "rosidl_runtime_c/string_functions.h"
// Member `wheels`
#include "sdv_msgs/msg/vehicle_info_wheel.h"
// Member `wheels`
#include "sdv_msgs/msg/detail/vehicle_info_wheel__rosidl_typesupport_introspection_c.h"
// Member `center_of_mass`
#include "geometry_msgs/msg/vector3.h"
// Member `center_of_mass`
#include "geometry_msgs/msg/detail/vector3__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  sdv_msgs__msg__VehicleInfo__init(message_memory);
}

void sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_fini_function(void * message_memory)
{
  sdv_msgs__msg__VehicleInfo__fini(message_memory);
}

size_t sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__size_function__VehicleInfo__wheels(
  const void * untyped_member)
{
  const sdv_msgs__msg__VehicleInfoWheel__Sequence * member =
    (const sdv_msgs__msg__VehicleInfoWheel__Sequence *)(untyped_member);
  return member->size;
}

const void * sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__get_const_function__VehicleInfo__wheels(
  const void * untyped_member, size_t index)
{
  const sdv_msgs__msg__VehicleInfoWheel__Sequence * member =
    (const sdv_msgs__msg__VehicleInfoWheel__Sequence *)(untyped_member);
  return &member->data[index];
}

void * sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__get_function__VehicleInfo__wheels(
  void * untyped_member, size_t index)
{
  sdv_msgs__msg__VehicleInfoWheel__Sequence * member =
    (sdv_msgs__msg__VehicleInfoWheel__Sequence *)(untyped_member);
  return &member->data[index];
}

void sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__fetch_function__VehicleInfo__wheels(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const sdv_msgs__msg__VehicleInfoWheel * item =
    ((const sdv_msgs__msg__VehicleInfoWheel *)
    sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__get_const_function__VehicleInfo__wheels(untyped_member, index));
  sdv_msgs__msg__VehicleInfoWheel * value =
    (sdv_msgs__msg__VehicleInfoWheel *)(untyped_value);
  *value = *item;
}

void sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__assign_function__VehicleInfo__wheels(
  void * untyped_member, size_t index, const void * untyped_value)
{
  sdv_msgs__msg__VehicleInfoWheel * item =
    ((sdv_msgs__msg__VehicleInfoWheel *)
    sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__get_function__VehicleInfo__wheels(untyped_member, index));
  const sdv_msgs__msg__VehicleInfoWheel * value =
    (const sdv_msgs__msg__VehicleInfoWheel *)(untyped_value);
  *item = *value;
}

bool sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__resize_function__VehicleInfo__wheels(
  void * untyped_member, size_t size)
{
  sdv_msgs__msg__VehicleInfoWheel__Sequence * member =
    (sdv_msgs__msg__VehicleInfoWheel__Sequence *)(untyped_member);
  sdv_msgs__msg__VehicleInfoWheel__Sequence__fini(member);
  return sdv_msgs__msg__VehicleInfoWheel__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_message_member_array[15] = {
  {
    "id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__VehicleInfo, id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "type",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__VehicleInfo, type),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "rolename",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__VehicleInfo, rolename),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "wheels",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__VehicleInfo, wheels),  // bytes offset in struct
    NULL,  // default value
    sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__size_function__VehicleInfo__wheels,  // size() function pointer
    sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__get_const_function__VehicleInfo__wheels,  // get_const(index) function pointer
    sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__get_function__VehicleInfo__wheels,  // get(index) function pointer
    sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__fetch_function__VehicleInfo__wheels,  // fetch(index, &value) function pointer
    sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__assign_function__VehicleInfo__wheels,  // assign(index, value) function pointer
    sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__resize_function__VehicleInfo__wheels  // resize(index) function pointer
  },
  {
    "max_rpm",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__VehicleInfo, max_rpm),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "moi",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__VehicleInfo, moi),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "damping_rate_full_throttle",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__VehicleInfo, damping_rate_full_throttle),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "damping_rate_zero_throttle_clutch_engaged",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__VehicleInfo, damping_rate_zero_throttle_clutch_engaged),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "damping_rate_zero_throttle_clutch_disengaged",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__VehicleInfo, damping_rate_zero_throttle_clutch_disengaged),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "use_gear_autobox",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__VehicleInfo, use_gear_autobox),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "gear_switch_time",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__VehicleInfo, gear_switch_time),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "clutch_strength",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__VehicleInfo, clutch_strength),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mass",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__VehicleInfo, mass),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "drag_coefficient",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__VehicleInfo, drag_coefficient),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "center_of_mass",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__msg__VehicleInfo, center_of_mass),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_message_members = {
  "sdv_msgs__msg",  // message namespace
  "VehicleInfo",  // message name
  15,  // number of fields
  sizeof(sdv_msgs__msg__VehicleInfo),
  sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_message_member_array,  // message members
  sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_init_function,  // function to initialize message memory (memory has to be allocated)
  sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_message_type_support_handle = {
  0,
  &sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_sdv_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sdv_msgs, msg, VehicleInfo)() {
  sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sdv_msgs, msg, VehicleInfoWheel)();
  sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_message_member_array[14].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Vector3)();
  if (!sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_message_type_support_handle.typesupport_identifier) {
    sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &sdv_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
