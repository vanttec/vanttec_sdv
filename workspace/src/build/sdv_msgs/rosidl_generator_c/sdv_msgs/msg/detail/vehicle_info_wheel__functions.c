// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sdv_msgs:msg/VehicleInfoWheel.idl
// generated code does not contain a copyright notice
#include "sdv_msgs/msg/detail/vehicle_info_wheel__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `position`
#include "geometry_msgs/msg/detail/vector3__functions.h"

bool
sdv_msgs__msg__VehicleInfoWheel__init(sdv_msgs__msg__VehicleInfoWheel * msg)
{
  if (!msg) {
    return false;
  }
  // tire_friction
  // damping_rate
  // max_steer_angle
  // radius
  // max_brake_torque
  // max_handbrake_torque
  // position
  if (!geometry_msgs__msg__Vector3__init(&msg->position)) {
    sdv_msgs__msg__VehicleInfoWheel__fini(msg);
    return false;
  }
  return true;
}

void
sdv_msgs__msg__VehicleInfoWheel__fini(sdv_msgs__msg__VehicleInfoWheel * msg)
{
  if (!msg) {
    return;
  }
  // tire_friction
  // damping_rate
  // max_steer_angle
  // radius
  // max_brake_torque
  // max_handbrake_torque
  // position
  geometry_msgs__msg__Vector3__fini(&msg->position);
}

bool
sdv_msgs__msg__VehicleInfoWheel__are_equal(const sdv_msgs__msg__VehicleInfoWheel * lhs, const sdv_msgs__msg__VehicleInfoWheel * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // tire_friction
  if (lhs->tire_friction != rhs->tire_friction) {
    return false;
  }
  // damping_rate
  if (lhs->damping_rate != rhs->damping_rate) {
    return false;
  }
  // max_steer_angle
  if (lhs->max_steer_angle != rhs->max_steer_angle) {
    return false;
  }
  // radius
  if (lhs->radius != rhs->radius) {
    return false;
  }
  // max_brake_torque
  if (lhs->max_brake_torque != rhs->max_brake_torque) {
    return false;
  }
  // max_handbrake_torque
  if (lhs->max_handbrake_torque != rhs->max_handbrake_torque) {
    return false;
  }
  // position
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->position), &(rhs->position)))
  {
    return false;
  }
  return true;
}

bool
sdv_msgs__msg__VehicleInfoWheel__copy(
  const sdv_msgs__msg__VehicleInfoWheel * input,
  sdv_msgs__msg__VehicleInfoWheel * output)
{
  if (!input || !output) {
    return false;
  }
  // tire_friction
  output->tire_friction = input->tire_friction;
  // damping_rate
  output->damping_rate = input->damping_rate;
  // max_steer_angle
  output->max_steer_angle = input->max_steer_angle;
  // radius
  output->radius = input->radius;
  // max_brake_torque
  output->max_brake_torque = input->max_brake_torque;
  // max_handbrake_torque
  output->max_handbrake_torque = input->max_handbrake_torque;
  // position
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->position), &(output->position)))
  {
    return false;
  }
  return true;
}

sdv_msgs__msg__VehicleInfoWheel *
sdv_msgs__msg__VehicleInfoWheel__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__VehicleInfoWheel * msg = (sdv_msgs__msg__VehicleInfoWheel *)allocator.allocate(sizeof(sdv_msgs__msg__VehicleInfoWheel), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sdv_msgs__msg__VehicleInfoWheel));
  bool success = sdv_msgs__msg__VehicleInfoWheel__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sdv_msgs__msg__VehicleInfoWheel__destroy(sdv_msgs__msg__VehicleInfoWheel * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sdv_msgs__msg__VehicleInfoWheel__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sdv_msgs__msg__VehicleInfoWheel__Sequence__init(sdv_msgs__msg__VehicleInfoWheel__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__VehicleInfoWheel * data = NULL;

  if (size) {
    data = (sdv_msgs__msg__VehicleInfoWheel *)allocator.zero_allocate(size, sizeof(sdv_msgs__msg__VehicleInfoWheel), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sdv_msgs__msg__VehicleInfoWheel__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sdv_msgs__msg__VehicleInfoWheel__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
sdv_msgs__msg__VehicleInfoWheel__Sequence__fini(sdv_msgs__msg__VehicleInfoWheel__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      sdv_msgs__msg__VehicleInfoWheel__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

sdv_msgs__msg__VehicleInfoWheel__Sequence *
sdv_msgs__msg__VehicleInfoWheel__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__VehicleInfoWheel__Sequence * array = (sdv_msgs__msg__VehicleInfoWheel__Sequence *)allocator.allocate(sizeof(sdv_msgs__msg__VehicleInfoWheel__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sdv_msgs__msg__VehicleInfoWheel__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sdv_msgs__msg__VehicleInfoWheel__Sequence__destroy(sdv_msgs__msg__VehicleInfoWheel__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sdv_msgs__msg__VehicleInfoWheel__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sdv_msgs__msg__VehicleInfoWheel__Sequence__are_equal(const sdv_msgs__msg__VehicleInfoWheel__Sequence * lhs, const sdv_msgs__msg__VehicleInfoWheel__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sdv_msgs__msg__VehicleInfoWheel__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sdv_msgs__msg__VehicleInfoWheel__Sequence__copy(
  const sdv_msgs__msg__VehicleInfoWheel__Sequence * input,
  sdv_msgs__msg__VehicleInfoWheel__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sdv_msgs__msg__VehicleInfoWheel);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sdv_msgs__msg__VehicleInfoWheel * data =
      (sdv_msgs__msg__VehicleInfoWheel *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sdv_msgs__msg__VehicleInfoWheel__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sdv_msgs__msg__VehicleInfoWheel__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sdv_msgs__msg__VehicleInfoWheel__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
