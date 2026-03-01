// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sdv_msgs:msg/VehicleStatus.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__VEHICLE_STATUS__STRUCT_H_
#define SDV_MSGS__MSG__DETAIL__VEHICLE_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'acceleration'
#include "geometry_msgs/msg/detail/accel__struct.h"
// Member 'orientation'
#include "geometry_msgs/msg/detail/quaternion__struct.h"
// Member 'control'
#include "sdv_msgs/msg/detail/vehicle_control__struct.h"

/// Struct defined in msg/VehicleStatus in the package sdv_msgs.
/**
  * Copyright (c) 2019 Intel Corporation.
  *
  * This work is licensed under the terms of the MIT license.
  * For a copy, see <https://opensource.org/licenses/MIT>.
 */
typedef struct sdv_msgs__msg__VehicleStatus
{
  std_msgs__msg__Header header;
  float velocity;
  geometry_msgs__msg__Accel acceleration;
  geometry_msgs__msg__Quaternion orientation;
  /// the current control values, as reported by Carla
  sdv_msgs__msg__VehicleControl control;
} sdv_msgs__msg__VehicleStatus;

// Struct for a sequence of sdv_msgs__msg__VehicleStatus.
typedef struct sdv_msgs__msg__VehicleStatus__Sequence
{
  sdv_msgs__msg__VehicleStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sdv_msgs__msg__VehicleStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SDV_MSGS__MSG__DETAIL__VEHICLE_STATUS__STRUCT_H_
