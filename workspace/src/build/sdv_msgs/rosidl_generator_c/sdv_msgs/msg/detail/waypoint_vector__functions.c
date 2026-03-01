// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sdv_msgs:msg/WaypointVector.idl
// generated code does not contain a copyright notice
#include "sdv_msgs/msg/detail/waypoint_vector__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `x_list`
// Member `y_list`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
sdv_msgs__msg__WaypointVector__init(sdv_msgs__msg__WaypointVector * msg)
{
  if (!msg) {
    return false;
  }
  // x_list
  if (!rosidl_runtime_c__float__Sequence__init(&msg->x_list, 0)) {
    sdv_msgs__msg__WaypointVector__fini(msg);
    return false;
  }
  // y_list
  if (!rosidl_runtime_c__float__Sequence__init(&msg->y_list, 0)) {
    sdv_msgs__msg__WaypointVector__fini(msg);
    return false;
  }
  return true;
}

void
sdv_msgs__msg__WaypointVector__fini(sdv_msgs__msg__WaypointVector * msg)
{
  if (!msg) {
    return;
  }
  // x_list
  rosidl_runtime_c__float__Sequence__fini(&msg->x_list);
  // y_list
  rosidl_runtime_c__float__Sequence__fini(&msg->y_list);
}

bool
sdv_msgs__msg__WaypointVector__are_equal(const sdv_msgs__msg__WaypointVector * lhs, const sdv_msgs__msg__WaypointVector * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // x_list
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->x_list), &(rhs->x_list)))
  {
    return false;
  }
  // y_list
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->y_list), &(rhs->y_list)))
  {
    return false;
  }
  return true;
}

bool
sdv_msgs__msg__WaypointVector__copy(
  const sdv_msgs__msg__WaypointVector * input,
  sdv_msgs__msg__WaypointVector * output)
{
  if (!input || !output) {
    return false;
  }
  // x_list
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->x_list), &(output->x_list)))
  {
    return false;
  }
  // y_list
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->y_list), &(output->y_list)))
  {
    return false;
  }
  return true;
}

sdv_msgs__msg__WaypointVector *
sdv_msgs__msg__WaypointVector__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__WaypointVector * msg = (sdv_msgs__msg__WaypointVector *)allocator.allocate(sizeof(sdv_msgs__msg__WaypointVector), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sdv_msgs__msg__WaypointVector));
  bool success = sdv_msgs__msg__WaypointVector__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sdv_msgs__msg__WaypointVector__destroy(sdv_msgs__msg__WaypointVector * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sdv_msgs__msg__WaypointVector__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sdv_msgs__msg__WaypointVector__Sequence__init(sdv_msgs__msg__WaypointVector__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__WaypointVector * data = NULL;

  if (size) {
    data = (sdv_msgs__msg__WaypointVector *)allocator.zero_allocate(size, sizeof(sdv_msgs__msg__WaypointVector), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sdv_msgs__msg__WaypointVector__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sdv_msgs__msg__WaypointVector__fini(&data[i - 1]);
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
sdv_msgs__msg__WaypointVector__Sequence__fini(sdv_msgs__msg__WaypointVector__Sequence * array)
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
      sdv_msgs__msg__WaypointVector__fini(&array->data[i]);
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

sdv_msgs__msg__WaypointVector__Sequence *
sdv_msgs__msg__WaypointVector__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__WaypointVector__Sequence * array = (sdv_msgs__msg__WaypointVector__Sequence *)allocator.allocate(sizeof(sdv_msgs__msg__WaypointVector__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sdv_msgs__msg__WaypointVector__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sdv_msgs__msg__WaypointVector__Sequence__destroy(sdv_msgs__msg__WaypointVector__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sdv_msgs__msg__WaypointVector__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sdv_msgs__msg__WaypointVector__Sequence__are_equal(const sdv_msgs__msg__WaypointVector__Sequence * lhs, const sdv_msgs__msg__WaypointVector__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sdv_msgs__msg__WaypointVector__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sdv_msgs__msg__WaypointVector__Sequence__copy(
  const sdv_msgs__msg__WaypointVector__Sequence * input,
  sdv_msgs__msg__WaypointVector__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sdv_msgs__msg__WaypointVector);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sdv_msgs__msg__WaypointVector * data =
      (sdv_msgs__msg__WaypointVector *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sdv_msgs__msg__WaypointVector__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sdv_msgs__msg__WaypointVector__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sdv_msgs__msg__WaypointVector__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
