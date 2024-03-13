// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sdv_msgs:msg/Status.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__STATUS__STRUCT_H_
#define SDV_MSGS__MSG__DETAIL__STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Status in the package sdv_msgs.
/**
  * Copyright (c) 2019 Intel Corporation.
  *
  * This work is licensed under the terms of the MIT license.
  * For a copy, see <https://opensource.org/licenses/MIT>.
 */
typedef struct sdv_msgs__msg__Status
{
  /// frame number
  uint64_t frame;
  /// duration of one frame
  float fixed_delta_seconds;
  /// sdv is in synchronous mode
  bool synchronous_mode;
  /// true: running, false: paused
  bool synchronous_mode_running;
} sdv_msgs__msg__Status;

// Struct for a sequence of sdv_msgs__msg__Status.
typedef struct sdv_msgs__msg__Status__Sequence
{
  sdv_msgs__msg__Status * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sdv_msgs__msg__Status__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SDV_MSGS__MSG__DETAIL__STATUS__STRUCT_H_
