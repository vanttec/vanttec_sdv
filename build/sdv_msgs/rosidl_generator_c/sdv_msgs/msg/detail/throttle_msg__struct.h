// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sdv_msgs:msg/ThrottleMsg.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__THROTTLE_MSG__STRUCT_H_
#define SDV_MSGS__MSG__DETAIL__THROTTLE_MSG__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'maxvel'
// Member 'pot'
#include "std_msgs/msg/detail/float64__struct.h"
// Member 'increase_maxvel'
// Member 'decrease_maxvel'
// Member 'car_mode'
// Member 'pot_mode'
#include "std_msgs/msg/detail/int16__struct.h"

/// Struct defined in msg/ThrottleMsg in the package sdv_msgs.
typedef struct sdv_msgs__msg__ThrottleMsg
{
  std_msgs__msg__Float64 maxvel;
  std_msgs__msg__Float64 pot;
  std_msgs__msg__Int16 increase_maxvel;
  std_msgs__msg__Int16 decrease_maxvel;
  std_msgs__msg__Int16 car_mode;
  std_msgs__msg__Int16 pot_mode;
} sdv_msgs__msg__ThrottleMsg;

// Struct for a sequence of sdv_msgs__msg__ThrottleMsg.
typedef struct sdv_msgs__msg__ThrottleMsg__Sequence
{
  sdv_msgs__msg__ThrottleMsg * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sdv_msgs__msg__ThrottleMsg__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SDV_MSGS__MSG__DETAIL__THROTTLE_MSG__STRUCT_H_
