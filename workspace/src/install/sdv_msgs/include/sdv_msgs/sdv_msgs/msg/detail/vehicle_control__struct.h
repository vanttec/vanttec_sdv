// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sdv_msgs:msg/VehicleControl.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__VEHICLE_CONTROL__STRUCT_H_
#define SDV_MSGS__MSG__DETAIL__VEHICLE_CONTROL__STRUCT_H_

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

/// Struct defined in msg/VehicleControl in the package sdv_msgs.
/**
  * Copyright (c) 2018-2019 Intel Corporation.
  *
  * This work is licensed under the terms of the MIT license.
  * For a copy, see <https://opensource.org/licenses/MIT>.
  *
  * This represents a vehicle control message sent to SDV simulator
 */
typedef struct sdv_msgs__msg__VehicleControl
{
  std_msgs__msg__Header header;
  /// The SDV vehicle control data
  /// 0. <= throttle <= 1.
  float throttle;
  /// -1. <= steer <= 1.
  float steer;
  /// 0. <= brake <= 1.
  float brake;
  /// hand_brake 0 or 1
  bool hand_brake;
  /// reverse 0 or 1
  bool reverse;
  /// gear
  int32_t gear;
  /// manual gear shift
  bool manual_gear_shift;
} sdv_msgs__msg__VehicleControl;

// Struct for a sequence of sdv_msgs__msg__VehicleControl.
typedef struct sdv_msgs__msg__VehicleControl__Sequence
{
  sdv_msgs__msg__VehicleControl * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sdv_msgs__msg__VehicleControl__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SDV_MSGS__MSG__DETAIL__VEHICLE_CONTROL__STRUCT_H_
