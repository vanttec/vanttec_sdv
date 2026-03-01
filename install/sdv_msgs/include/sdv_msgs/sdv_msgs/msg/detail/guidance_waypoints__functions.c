// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sdv_msgs:msg/GuidanceWaypoints.idl
// generated code does not contain a copyright notice
#include "sdv_msgs/msg/detail/guidance_waypoints__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `waypoint_list_x`
// Member `waypoint_list_y`
// Member `waypoint_list_z`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
sdv_msgs__msg__GuidanceWaypoints__init(sdv_msgs__msg__GuidanceWaypoints * msg)
{
  if (!msg) {
    return false;
  }
  // guidance_law
  // waypoint_list_length
  // waypoint_list_x
  if (!rosidl_runtime_c__float__Sequence__init(&msg->waypoint_list_x, 0)) {
    sdv_msgs__msg__GuidanceWaypoints__fini(msg);
    return false;
  }
  // waypoint_list_y
  if (!rosidl_runtime_c__float__Sequence__init(&msg->waypoint_list_y, 0)) {
    sdv_msgs__msg__GuidanceWaypoints__fini(msg);
    return false;
  }
  // waypoint_list_z
  if (!rosidl_runtime_c__float__Sequence__init(&msg->waypoint_list_z, 0)) {
    sdv_msgs__msg__GuidanceWaypoints__fini(msg);
    return false;
  }
  // depth_setpoint
  // heading_setpoint
  return true;
}

void
sdv_msgs__msg__GuidanceWaypoints__fini(sdv_msgs__msg__GuidanceWaypoints * msg)
{
  if (!msg) {
    return;
  }
  // guidance_law
  // waypoint_list_length
  // waypoint_list_x
  rosidl_runtime_c__float__Sequence__fini(&msg->waypoint_list_x);
  // waypoint_list_y
  rosidl_runtime_c__float__Sequence__fini(&msg->waypoint_list_y);
  // waypoint_list_z
  rosidl_runtime_c__float__Sequence__fini(&msg->waypoint_list_z);
  // depth_setpoint
  // heading_setpoint
}

bool
sdv_msgs__msg__GuidanceWaypoints__are_equal(const sdv_msgs__msg__GuidanceWaypoints * lhs, const sdv_msgs__msg__GuidanceWaypoints * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // guidance_law
  if (lhs->guidance_law != rhs->guidance_law) {
    return false;
  }
  // waypoint_list_length
  if (lhs->waypoint_list_length != rhs->waypoint_list_length) {
    return false;
  }
  // waypoint_list_x
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->waypoint_list_x), &(rhs->waypoint_list_x)))
  {
    return false;
  }
  // waypoint_list_y
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->waypoint_list_y), &(rhs->waypoint_list_y)))
  {
    return false;
  }
  // waypoint_list_z
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->waypoint_list_z), &(rhs->waypoint_list_z)))
  {
    return false;
  }
  // depth_setpoint
  if (lhs->depth_setpoint != rhs->depth_setpoint) {
    return false;
  }
  // heading_setpoint
  if (lhs->heading_setpoint != rhs->heading_setpoint) {
    return false;
  }
  return true;
}

bool
sdv_msgs__msg__GuidanceWaypoints__copy(
  const sdv_msgs__msg__GuidanceWaypoints * input,
  sdv_msgs__msg__GuidanceWaypoints * output)
{
  if (!input || !output) {
    return false;
  }
  // guidance_law
  output->guidance_law = input->guidance_law;
  // waypoint_list_length
  output->waypoint_list_length = input->waypoint_list_length;
  // waypoint_list_x
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->waypoint_list_x), &(output->waypoint_list_x)))
  {
    return false;
  }
  // waypoint_list_y
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->waypoint_list_y), &(output->waypoint_list_y)))
  {
    return false;
  }
  // waypoint_list_z
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->waypoint_list_z), &(output->waypoint_list_z)))
  {
    return false;
  }
  // depth_setpoint
  output->depth_setpoint = input->depth_setpoint;
  // heading_setpoint
  output->heading_setpoint = input->heading_setpoint;
  return true;
}

sdv_msgs__msg__GuidanceWaypoints *
sdv_msgs__msg__GuidanceWaypoints__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__GuidanceWaypoints * msg = (sdv_msgs__msg__GuidanceWaypoints *)allocator.allocate(sizeof(sdv_msgs__msg__GuidanceWaypoints), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sdv_msgs__msg__GuidanceWaypoints));
  bool success = sdv_msgs__msg__GuidanceWaypoints__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sdv_msgs__msg__GuidanceWaypoints__destroy(sdv_msgs__msg__GuidanceWaypoints * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sdv_msgs__msg__GuidanceWaypoints__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sdv_msgs__msg__GuidanceWaypoints__Sequence__init(sdv_msgs__msg__GuidanceWaypoints__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__GuidanceWaypoints * data = NULL;

  if (size) {
    data = (sdv_msgs__msg__GuidanceWaypoints *)allocator.zero_allocate(size, sizeof(sdv_msgs__msg__GuidanceWaypoints), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sdv_msgs__msg__GuidanceWaypoints__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sdv_msgs__msg__GuidanceWaypoints__fini(&data[i - 1]);
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
sdv_msgs__msg__GuidanceWaypoints__Sequence__fini(sdv_msgs__msg__GuidanceWaypoints__Sequence * array)
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
      sdv_msgs__msg__GuidanceWaypoints__fini(&array->data[i]);
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

sdv_msgs__msg__GuidanceWaypoints__Sequence *
sdv_msgs__msg__GuidanceWaypoints__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__GuidanceWaypoints__Sequence * array = (sdv_msgs__msg__GuidanceWaypoints__Sequence *)allocator.allocate(sizeof(sdv_msgs__msg__GuidanceWaypoints__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sdv_msgs__msg__GuidanceWaypoints__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sdv_msgs__msg__GuidanceWaypoints__Sequence__destroy(sdv_msgs__msg__GuidanceWaypoints__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sdv_msgs__msg__GuidanceWaypoints__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sdv_msgs__msg__GuidanceWaypoints__Sequence__are_equal(const sdv_msgs__msg__GuidanceWaypoints__Sequence * lhs, const sdv_msgs__msg__GuidanceWaypoints__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sdv_msgs__msg__GuidanceWaypoints__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sdv_msgs__msg__GuidanceWaypoints__Sequence__copy(
  const sdv_msgs__msg__GuidanceWaypoints__Sequence * input,
  sdv_msgs__msg__GuidanceWaypoints__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sdv_msgs__msg__GuidanceWaypoints);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sdv_msgs__msg__GuidanceWaypoints * data =
      (sdv_msgs__msg__GuidanceWaypoints *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sdv_msgs__msg__GuidanceWaypoints__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sdv_msgs__msg__GuidanceWaypoints__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sdv_msgs__msg__GuidanceWaypoints__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
