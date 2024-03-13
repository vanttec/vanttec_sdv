// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sdv_msgs:msg/CollisionEvent.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__COLLISION_EVENT__STRUCT_H_
#define SDV_MSGS__MSG__DETAIL__COLLISION_EVENT__STRUCT_H_

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
// Member 'normal_impulse'
#include "geometry_msgs/msg/detail/vector3__struct.h"

/// Struct defined in msg/CollisionEvent in the package sdv_msgs.
/**
  * Copyright (c) 2019 Intel Corporation.
  *
  * This work is licensed under the terms of the MIT license.
  * For a copy, see <https://opensource.org/licenses/MIT>.
  *
  * A collision event
 */
typedef struct sdv_msgs__msg__CollisionEvent
{
  std_msgs__msg__Header header;
  uint32_t other_actor_id;
  geometry_msgs__msg__Vector3 normal_impulse;
} sdv_msgs__msg__CollisionEvent;

// Struct for a sequence of sdv_msgs__msg__CollisionEvent.
typedef struct sdv_msgs__msg__CollisionEvent__Sequence
{
  sdv_msgs__msg__CollisionEvent * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sdv_msgs__msg__CollisionEvent__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SDV_MSGS__MSG__DETAIL__COLLISION_EVENT__STRUCT_H_
