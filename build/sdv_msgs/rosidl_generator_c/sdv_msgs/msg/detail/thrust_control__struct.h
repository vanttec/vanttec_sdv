// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sdv_msgs:msg/ThrustControl.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__THRUST_CONTROL__STRUCT_H_
#define SDV_MSGS__MSG__DETAIL__THRUST_CONTROL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/ThrustControl in the package sdv_msgs.
typedef struct sdv_msgs__msg__ThrustControl
{
  float tau_x;
  float tau_y;
  float tau_z;
  float tau_phi;
  float tau_theta;
  float tau_psi;
} sdv_msgs__msg__ThrustControl;

// Struct for a sequence of sdv_msgs__msg__ThrustControl.
typedef struct sdv_msgs__msg__ThrustControl__Sequence
{
  sdv_msgs__msg__ThrustControl * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sdv_msgs__msg__ThrustControl__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SDV_MSGS__MSG__DETAIL__THRUST_CONTROL__STRUCT_H_
