// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sdv_msgs:msg/SystemDynamics.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__SYSTEM_DYNAMICS__STRUCT_H_
#define SDV_MSGS__MSG__DETAIL__SYSTEM_DYNAMICS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'g'
#include "std_msgs/msg/detail/float32_multi_array__struct.h"
// Member 'f'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/SystemDynamics in the package sdv_msgs.
typedef struct sdv_msgs__msg__SystemDynamics
{
  std_msgs__msg__Float32MultiArray g;
  rosidl_runtime_c__float__Sequence f;
} sdv_msgs__msg__SystemDynamics;

// Struct for a sequence of sdv_msgs__msg__SystemDynamics.
typedef struct sdv_msgs__msg__SystemDynamics__Sequence
{
  sdv_msgs__msg__SystemDynamics * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sdv_msgs__msg__SystemDynamics__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SDV_MSGS__MSG__DETAIL__SYSTEM_DYNAMICS__STRUCT_H_
