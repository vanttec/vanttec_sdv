// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sdv_msgs:msg/VehicleInfo.idl
// generated code does not contain a copyright notice
#include "sdv_msgs/msg/detail/vehicle_info__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `type`
// Member `rolename`
#include "rosidl_runtime_c/string_functions.h"
// Member `wheels`
#include "sdv_msgs/msg/detail/vehicle_info_wheel__functions.h"
// Member `center_of_mass`
#include "geometry_msgs/msg/detail/vector3__functions.h"

bool
sdv_msgs__msg__VehicleInfo__init(sdv_msgs__msg__VehicleInfo * msg)
{
  if (!msg) {
    return false;
  }
  // id
  // type
  if (!rosidl_runtime_c__String__init(&msg->type)) {
    sdv_msgs__msg__VehicleInfo__fini(msg);
    return false;
  }
  // rolename
  if (!rosidl_runtime_c__String__init(&msg->rolename)) {
    sdv_msgs__msg__VehicleInfo__fini(msg);
    return false;
  }
  // wheels
  if (!sdv_msgs__msg__VehicleInfoWheel__Sequence__init(&msg->wheels, 0)) {
    sdv_msgs__msg__VehicleInfo__fini(msg);
    return false;
  }
  // max_rpm
  // moi
  // damping_rate_full_throttle
  // damping_rate_zero_throttle_clutch_engaged
  // damping_rate_zero_throttle_clutch_disengaged
  // use_gear_autobox
  // gear_switch_time
  // clutch_strength
  // mass
  // drag_coefficient
  // center_of_mass
  if (!geometry_msgs__msg__Vector3__init(&msg->center_of_mass)) {
    sdv_msgs__msg__VehicleInfo__fini(msg);
    return false;
  }
  return true;
}

void
sdv_msgs__msg__VehicleInfo__fini(sdv_msgs__msg__VehicleInfo * msg)
{
  if (!msg) {
    return;
  }
  // id
  // type
  rosidl_runtime_c__String__fini(&msg->type);
  // rolename
  rosidl_runtime_c__String__fini(&msg->rolename);
  // wheels
  sdv_msgs__msg__VehicleInfoWheel__Sequence__fini(&msg->wheels);
  // max_rpm
  // moi
  // damping_rate_full_throttle
  // damping_rate_zero_throttle_clutch_engaged
  // damping_rate_zero_throttle_clutch_disengaged
  // use_gear_autobox
  // gear_switch_time
  // clutch_strength
  // mass
  // drag_coefficient
  // center_of_mass
  geometry_msgs__msg__Vector3__fini(&msg->center_of_mass);
}

bool
sdv_msgs__msg__VehicleInfo__are_equal(const sdv_msgs__msg__VehicleInfo * lhs, const sdv_msgs__msg__VehicleInfo * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  // type
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->type), &(rhs->type)))
  {
    return false;
  }
  // rolename
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->rolename), &(rhs->rolename)))
  {
    return false;
  }
  // wheels
  if (!sdv_msgs__msg__VehicleInfoWheel__Sequence__are_equal(
      &(lhs->wheels), &(rhs->wheels)))
  {
    return false;
  }
  // max_rpm
  if (lhs->max_rpm != rhs->max_rpm) {
    return false;
  }
  // moi
  if (lhs->moi != rhs->moi) {
    return false;
  }
  // damping_rate_full_throttle
  if (lhs->damping_rate_full_throttle != rhs->damping_rate_full_throttle) {
    return false;
  }
  // damping_rate_zero_throttle_clutch_engaged
  if (lhs->damping_rate_zero_throttle_clutch_engaged != rhs->damping_rate_zero_throttle_clutch_engaged) {
    return false;
  }
  // damping_rate_zero_throttle_clutch_disengaged
  if (lhs->damping_rate_zero_throttle_clutch_disengaged != rhs->damping_rate_zero_throttle_clutch_disengaged) {
    return false;
  }
  // use_gear_autobox
  if (lhs->use_gear_autobox != rhs->use_gear_autobox) {
    return false;
  }
  // gear_switch_time
  if (lhs->gear_switch_time != rhs->gear_switch_time) {
    return false;
  }
  // clutch_strength
  if (lhs->clutch_strength != rhs->clutch_strength) {
    return false;
  }
  // mass
  if (lhs->mass != rhs->mass) {
    return false;
  }
  // drag_coefficient
  if (lhs->drag_coefficient != rhs->drag_coefficient) {
    return false;
  }
  // center_of_mass
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->center_of_mass), &(rhs->center_of_mass)))
  {
    return false;
  }
  return true;
}

bool
sdv_msgs__msg__VehicleInfo__copy(
  const sdv_msgs__msg__VehicleInfo * input,
  sdv_msgs__msg__VehicleInfo * output)
{
  if (!input || !output) {
    return false;
  }
  // id
  output->id = input->id;
  // type
  if (!rosidl_runtime_c__String__copy(
      &(input->type), &(output->type)))
  {
    return false;
  }
  // rolename
  if (!rosidl_runtime_c__String__copy(
      &(input->rolename), &(output->rolename)))
  {
    return false;
  }
  // wheels
  if (!sdv_msgs__msg__VehicleInfoWheel__Sequence__copy(
      &(input->wheels), &(output->wheels)))
  {
    return false;
  }
  // max_rpm
  output->max_rpm = input->max_rpm;
  // moi
  output->moi = input->moi;
  // damping_rate_full_throttle
  output->damping_rate_full_throttle = input->damping_rate_full_throttle;
  // damping_rate_zero_throttle_clutch_engaged
  output->damping_rate_zero_throttle_clutch_engaged = input->damping_rate_zero_throttle_clutch_engaged;
  // damping_rate_zero_throttle_clutch_disengaged
  output->damping_rate_zero_throttle_clutch_disengaged = input->damping_rate_zero_throttle_clutch_disengaged;
  // use_gear_autobox
  output->use_gear_autobox = input->use_gear_autobox;
  // gear_switch_time
  output->gear_switch_time = input->gear_switch_time;
  // clutch_strength
  output->clutch_strength = input->clutch_strength;
  // mass
  output->mass = input->mass;
  // drag_coefficient
  output->drag_coefficient = input->drag_coefficient;
  // center_of_mass
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->center_of_mass), &(output->center_of_mass)))
  {
    return false;
  }
  return true;
}

sdv_msgs__msg__VehicleInfo *
sdv_msgs__msg__VehicleInfo__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__VehicleInfo * msg = (sdv_msgs__msg__VehicleInfo *)allocator.allocate(sizeof(sdv_msgs__msg__VehicleInfo), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sdv_msgs__msg__VehicleInfo));
  bool success = sdv_msgs__msg__VehicleInfo__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sdv_msgs__msg__VehicleInfo__destroy(sdv_msgs__msg__VehicleInfo * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sdv_msgs__msg__VehicleInfo__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sdv_msgs__msg__VehicleInfo__Sequence__init(sdv_msgs__msg__VehicleInfo__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__VehicleInfo * data = NULL;

  if (size) {
    data = (sdv_msgs__msg__VehicleInfo *)allocator.zero_allocate(size, sizeof(sdv_msgs__msg__VehicleInfo), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sdv_msgs__msg__VehicleInfo__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sdv_msgs__msg__VehicleInfo__fini(&data[i - 1]);
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
sdv_msgs__msg__VehicleInfo__Sequence__fini(sdv_msgs__msg__VehicleInfo__Sequence * array)
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
      sdv_msgs__msg__VehicleInfo__fini(&array->data[i]);
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

sdv_msgs__msg__VehicleInfo__Sequence *
sdv_msgs__msg__VehicleInfo__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__VehicleInfo__Sequence * array = (sdv_msgs__msg__VehicleInfo__Sequence *)allocator.allocate(sizeof(sdv_msgs__msg__VehicleInfo__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sdv_msgs__msg__VehicleInfo__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sdv_msgs__msg__VehicleInfo__Sequence__destroy(sdv_msgs__msg__VehicleInfo__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sdv_msgs__msg__VehicleInfo__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sdv_msgs__msg__VehicleInfo__Sequence__are_equal(const sdv_msgs__msg__VehicleInfo__Sequence * lhs, const sdv_msgs__msg__VehicleInfo__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sdv_msgs__msg__VehicleInfo__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sdv_msgs__msg__VehicleInfo__Sequence__copy(
  const sdv_msgs__msg__VehicleInfo__Sequence * input,
  sdv_msgs__msg__VehicleInfo__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sdv_msgs__msg__VehicleInfo);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sdv_msgs__msg__VehicleInfo * data =
      (sdv_msgs__msg__VehicleInfo *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sdv_msgs__msg__VehicleInfo__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sdv_msgs__msg__VehicleInfo__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sdv_msgs__msg__VehicleInfo__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
