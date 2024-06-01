// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sdv_msgs:msg/XboxMsg.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__XBOX_MSG__STRUCT_H_
#define SDV_MSGS__MSG__DETAIL__XBOX_MSG__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'connected'
#include "std_msgs/msg/detail/bool__struct.h"
// Member 'back'
// Member 'a'
// Member 'b'
// Member 'x'
// Member 'y'
// Member 'dpad_up'
// Member 'dpad_down'
// Member 'dpad_left'
// Member 'dpad_right'
#include "std_msgs/msg/detail/int16__struct.h"
// Member 'leftx'
// Member 'lefty'
// Member 'right_trigger'
#include "std_msgs/msg/detail/float64__struct.h"

/// Struct defined in msg/XboxMsg in the package sdv_msgs.
typedef struct sdv_msgs__msg__XboxMsg
{
  std_msgs__msg__Bool connected;
  std_msgs__msg__Int16 back;
  std_msgs__msg__Float64 leftx;
  std_msgs__msg__Float64 lefty;
  std_msgs__msg__Float64 right_trigger;
  std_msgs__msg__Int16 a;
  std_msgs__msg__Int16 b;
  std_msgs__msg__Int16 x;
  std_msgs__msg__Int16 y;
  std_msgs__msg__Int16 dpad_up;
  std_msgs__msg__Int16 dpad_down;
  std_msgs__msg__Int16 dpad_left;
  std_msgs__msg__Int16 dpad_right;
} sdv_msgs__msg__XboxMsg;

// Struct for a sequence of sdv_msgs__msg__XboxMsg.
typedef struct sdv_msgs__msg__XboxMsg__Sequence
{
  sdv_msgs__msg__XboxMsg * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sdv_msgs__msg__XboxMsg__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SDV_MSGS__MSG__DETAIL__XBOX_MSG__STRUCT_H_
