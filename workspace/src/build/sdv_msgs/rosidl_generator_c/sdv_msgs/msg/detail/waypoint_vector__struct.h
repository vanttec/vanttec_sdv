// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sdv_msgs:msg/WaypointVector.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__WAYPOINT_VECTOR__STRUCT_H_
#define SDV_MSGS__MSG__DETAIL__WAYPOINT_VECTOR__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'x_list'
// Member 'y_list'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/WaypointVector in the package sdv_msgs.
typedef struct sdv_msgs__msg__WaypointVector
{
  /// List of x coordinates of the waypoints
  rosidl_runtime_c__float__Sequence x_list;
  /// List of y coordinates of the waypoints
  rosidl_runtime_c__float__Sequence y_list;
} sdv_msgs__msg__WaypointVector;

// Struct for a sequence of sdv_msgs__msg__WaypointVector.
typedef struct sdv_msgs__msg__WaypointVector__Sequence
{
  sdv_msgs__msg__WaypointVector * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sdv_msgs__msg__WaypointVector__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SDV_MSGS__MSG__DETAIL__WAYPOINT_VECTOR__STRUCT_H_
