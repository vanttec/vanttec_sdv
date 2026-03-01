// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sdv_msgs:msg/GuidanceWaypoints.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__GUIDANCE_WAYPOINTS__STRUCT_H_
#define SDV_MSGS__MSG__DETAIL__GUIDANCE_WAYPOINTS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'waypoint_list_x'
// Member 'waypoint_list_y'
// Member 'waypoint_list_z'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/GuidanceWaypoints in the package sdv_msgs.
typedef struct sdv_msgs__msg__GuidanceWaypoints
{
  uint8_t guidance_law;
  uint8_t waypoint_list_length;
  rosidl_runtime_c__float__Sequence waypoint_list_x;
  rosidl_runtime_c__float__Sequence waypoint_list_y;
  rosidl_runtime_c__float__Sequence waypoint_list_z;
  float depth_setpoint;
  float heading_setpoint;
} sdv_msgs__msg__GuidanceWaypoints;

// Struct for a sequence of sdv_msgs__msg__GuidanceWaypoints.
typedef struct sdv_msgs__msg__GuidanceWaypoints__Sequence
{
  sdv_msgs__msg__GuidanceWaypoints * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sdv_msgs__msg__GuidanceWaypoints__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SDV_MSGS__MSG__DETAIL__GUIDANCE_WAYPOINTS__STRUCT_H_
