// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sdv_msgs:msg/LaneInvasionEvent.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__LANE_INVASION_EVENT__STRUCT_H_
#define SDV_MSGS__MSG__DETAIL__LANE_INVASION_EVENT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'LANE_MARKING_OTHER'.
enum
{
  sdv_msgs__msg__LaneInvasionEvent__LANE_MARKING_OTHER = 0l
};

/// Constant 'LANE_MARKING_BROKEN'.
enum
{
  sdv_msgs__msg__LaneInvasionEvent__LANE_MARKING_BROKEN = 1l
};

/// Constant 'LANE_MARKING_SOLID'.
enum
{
  sdv_msgs__msg__LaneInvasionEvent__LANE_MARKING_SOLID = 2l
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'crossed_lane_markings'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/LaneInvasionEvent in the package sdv_msgs.
/**
  * Copyright (c) 2019 Intel Corporation.
  *
  * This work is licensed under the terms of the MIT license.
  * For a copy, see <https://opensource.org/licenses/MIT>.
  *
  * A lane invasion event
 */
typedef struct sdv_msgs__msg__LaneInvasionEvent
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__int32__Sequence crossed_lane_markings;
} sdv_msgs__msg__LaneInvasionEvent;

// Struct for a sequence of sdv_msgs__msg__LaneInvasionEvent.
typedef struct sdv_msgs__msg__LaneInvasionEvent__Sequence
{
  sdv_msgs__msg__LaneInvasionEvent * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sdv_msgs__msg__LaneInvasionEvent__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SDV_MSGS__MSG__DETAIL__LANE_INVASION_EVENT__STRUCT_H_
