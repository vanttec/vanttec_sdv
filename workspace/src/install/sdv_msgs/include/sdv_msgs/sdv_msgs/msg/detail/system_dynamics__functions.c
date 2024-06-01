// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sdv_msgs:msg/SystemDynamics.idl
// generated code does not contain a copyright notice
#include "sdv_msgs/msg/detail/system_dynamics__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `g`
#include "std_msgs/msg/detail/float32_multi_array__functions.h"
// Member `f`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
sdv_msgs__msg__SystemDynamics__init(sdv_msgs__msg__SystemDynamics * msg)
{
  if (!msg) {
    return false;
  }
  // g
  if (!std_msgs__msg__Float32MultiArray__init(&msg->g)) {
    sdv_msgs__msg__SystemDynamics__fini(msg);
    return false;
  }
  // f
  if (!rosidl_runtime_c__float__Sequence__init(&msg->f, 0)) {
    sdv_msgs__msg__SystemDynamics__fini(msg);
    return false;
  }
  return true;
}

void
sdv_msgs__msg__SystemDynamics__fini(sdv_msgs__msg__SystemDynamics * msg)
{
  if (!msg) {
    return;
  }
  // g
  std_msgs__msg__Float32MultiArray__fini(&msg->g);
  // f
  rosidl_runtime_c__float__Sequence__fini(&msg->f);
}

bool
sdv_msgs__msg__SystemDynamics__are_equal(const sdv_msgs__msg__SystemDynamics * lhs, const sdv_msgs__msg__SystemDynamics * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // g
  if (!std_msgs__msg__Float32MultiArray__are_equal(
      &(lhs->g), &(rhs->g)))
  {
    return false;
  }
  // f
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->f), &(rhs->f)))
  {
    return false;
  }
  return true;
}

bool
sdv_msgs__msg__SystemDynamics__copy(
  const sdv_msgs__msg__SystemDynamics * input,
  sdv_msgs__msg__SystemDynamics * output)
{
  if (!input || !output) {
    return false;
  }
  // g
  if (!std_msgs__msg__Float32MultiArray__copy(
      &(input->g), &(output->g)))
  {
    return false;
  }
  // f
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->f), &(output->f)))
  {
    return false;
  }
  return true;
}

sdv_msgs__msg__SystemDynamics *
sdv_msgs__msg__SystemDynamics__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__SystemDynamics * msg = (sdv_msgs__msg__SystemDynamics *)allocator.allocate(sizeof(sdv_msgs__msg__SystemDynamics), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sdv_msgs__msg__SystemDynamics));
  bool success = sdv_msgs__msg__SystemDynamics__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sdv_msgs__msg__SystemDynamics__destroy(sdv_msgs__msg__SystemDynamics * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sdv_msgs__msg__SystemDynamics__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sdv_msgs__msg__SystemDynamics__Sequence__init(sdv_msgs__msg__SystemDynamics__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__SystemDynamics * data = NULL;

  if (size) {
    data = (sdv_msgs__msg__SystemDynamics *)allocator.zero_allocate(size, sizeof(sdv_msgs__msg__SystemDynamics), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sdv_msgs__msg__SystemDynamics__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sdv_msgs__msg__SystemDynamics__fini(&data[i - 1]);
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
sdv_msgs__msg__SystemDynamics__Sequence__fini(sdv_msgs__msg__SystemDynamics__Sequence * array)
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
      sdv_msgs__msg__SystemDynamics__fini(&array->data[i]);
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

sdv_msgs__msg__SystemDynamics__Sequence *
sdv_msgs__msg__SystemDynamics__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__SystemDynamics__Sequence * array = (sdv_msgs__msg__SystemDynamics__Sequence *)allocator.allocate(sizeof(sdv_msgs__msg__SystemDynamics__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sdv_msgs__msg__SystemDynamics__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sdv_msgs__msg__SystemDynamics__Sequence__destroy(sdv_msgs__msg__SystemDynamics__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sdv_msgs__msg__SystemDynamics__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sdv_msgs__msg__SystemDynamics__Sequence__are_equal(const sdv_msgs__msg__SystemDynamics__Sequence * lhs, const sdv_msgs__msg__SystemDynamics__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sdv_msgs__msg__SystemDynamics__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sdv_msgs__msg__SystemDynamics__Sequence__copy(
  const sdv_msgs__msg__SystemDynamics__Sequence * input,
  sdv_msgs__msg__SystemDynamics__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sdv_msgs__msg__SystemDynamics);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sdv_msgs__msg__SystemDynamics * data =
      (sdv_msgs__msg__SystemDynamics *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sdv_msgs__msg__SystemDynamics__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sdv_msgs__msg__SystemDynamics__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sdv_msgs__msg__SystemDynamics__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
