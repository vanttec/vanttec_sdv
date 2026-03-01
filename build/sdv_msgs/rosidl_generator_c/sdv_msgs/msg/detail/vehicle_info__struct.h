// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sdv_msgs:msg/VehicleInfo.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__VEHICLE_INFO__STRUCT_H_
#define SDV_MSGS__MSG__DETAIL__VEHICLE_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'type'
// Member 'rolename'
#include "rosidl_runtime_c/string.h"
// Member 'wheels'
#include "sdv_msgs/msg/detail/vehicle_info_wheel__struct.h"
// Member 'center_of_mass'
#include "geometry_msgs/msg/detail/vector3__struct.h"

/// Struct defined in msg/VehicleInfo in the package sdv_msgs.
/**
  * Copyright (c) 2019 Intel Corporation.
  *
  * This work is licensed under the terms of the MIT license.
  * For a copy, see <https://opensource.org/licenses/MIT>.
 */
typedef struct sdv_msgs__msg__VehicleInfo
{
  uint32_t id;
  rosidl_runtime_c__String type;
  rosidl_runtime_c__String rolename;
  sdv_msgs__msg__VehicleInfoWheel__Sequence wheels;
  float max_rpm;
  float moi;
  float damping_rate_full_throttle;
  float damping_rate_zero_throttle_clutch_engaged;
  float damping_rate_zero_throttle_clutch_disengaged;
  bool use_gear_autobox;
  float gear_switch_time;
  float clutch_strength;
  float mass;
  float drag_coefficient;
  geometry_msgs__msg__Vector3 center_of_mass;
} sdv_msgs__msg__VehicleInfo;

// Struct for a sequence of sdv_msgs__msg__VehicleInfo.
typedef struct sdv_msgs__msg__VehicleInfo__Sequence
{
  sdv_msgs__msg__VehicleInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sdv_msgs__msg__VehicleInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SDV_MSGS__MSG__DETAIL__VEHICLE_INFO__STRUCT_H_
