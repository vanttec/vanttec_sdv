// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sdv_msgs:msg/EtaPose.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__ETA_POSE__STRUCT_H_
#define SDV_MSGS__MSG__DETAIL__ETA_POSE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/EtaPose in the package sdv_msgs.
typedef struct sdv_msgs__msg__EtaPose
{
  double x;
  double y;
  double z;
  double phi;
  double theta;
  double psi;
} sdv_msgs__msg__EtaPose;

// Struct for a sequence of sdv_msgs__msg__EtaPose.
typedef struct sdv_msgs__msg__EtaPose__Sequence
{
  sdv_msgs__msg__EtaPose * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sdv_msgs__msg__EtaPose__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SDV_MSGS__MSG__DETAIL__ETA_POSE__STRUCT_H_
