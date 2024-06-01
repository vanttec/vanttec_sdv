// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sdv_msgs:msg/State.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__STATE__STRUCT_H_
#define SDV_MSGS__MSG__DETAIL__STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/State in the package sdv_msgs.
typedef struct sdv_msgs__msg__State
{
  double x;
  double y;
  double yaw;
  double vx;
  double steer;
  double accx;
} sdv_msgs__msg__State;

// Struct for a sequence of sdv_msgs__msg__State.
typedef struct sdv_msgs__msg__State__Sequence
{
  sdv_msgs__msg__State * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sdv_msgs__msg__State__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SDV_MSGS__MSG__DETAIL__STATE__STRUCT_H_
