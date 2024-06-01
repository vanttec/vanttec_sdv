// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sdv_msgs:msg/Encoder.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__ENCODER__STRUCT_H_
#define SDV_MSGS__MSG__DETAIL__ENCODER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Encoder in the package sdv_msgs.
typedef struct sdv_msgs__msg__Encoder
{
  float abs_angle;
  float angle;
  int16_t turn;
} sdv_msgs__msg__Encoder;

// Struct for a sequence of sdv_msgs__msg__Encoder.
typedef struct sdv_msgs__msg__Encoder__Sequence
{
  sdv_msgs__msg__Encoder * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sdv_msgs__msg__Encoder__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SDV_MSGS__MSG__DETAIL__ENCODER__STRUCT_H_
