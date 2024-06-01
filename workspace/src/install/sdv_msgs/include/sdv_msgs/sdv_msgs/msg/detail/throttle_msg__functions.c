// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sdv_msgs:msg/ThrottleMsg.idl
// generated code does not contain a copyright notice
#include "sdv_msgs/msg/detail/throttle_msg__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `maxvel`
// Member `pot`
#include "std_msgs/msg/detail/float64__functions.h"
// Member `increase_maxvel`
// Member `decrease_maxvel`
// Member `car_mode`
// Member `pot_mode`
#include "std_msgs/msg/detail/int16__functions.h"

bool
sdv_msgs__msg__ThrottleMsg__init(sdv_msgs__msg__ThrottleMsg * msg)
{
  if (!msg) {
    return false;
  }
  // maxvel
  if (!std_msgs__msg__Float64__init(&msg->maxvel)) {
    sdv_msgs__msg__ThrottleMsg__fini(msg);
    return false;
  }
  // pot
  if (!std_msgs__msg__Float64__init(&msg->pot)) {
    sdv_msgs__msg__ThrottleMsg__fini(msg);
    return false;
  }
  // increase_maxvel
  if (!std_msgs__msg__Int16__init(&msg->increase_maxvel)) {
    sdv_msgs__msg__ThrottleMsg__fini(msg);
    return false;
  }
  // decrease_maxvel
  if (!std_msgs__msg__Int16__init(&msg->decrease_maxvel)) {
    sdv_msgs__msg__ThrottleMsg__fini(msg);
    return false;
  }
  // car_mode
  if (!std_msgs__msg__Int16__init(&msg->car_mode)) {
    sdv_msgs__msg__ThrottleMsg__fini(msg);
    return false;
  }
  // pot_mode
  if (!std_msgs__msg__Int16__init(&msg->pot_mode)) {
    sdv_msgs__msg__ThrottleMsg__fini(msg);
    return false;
  }
  return true;
}

void
sdv_msgs__msg__ThrottleMsg__fini(sdv_msgs__msg__ThrottleMsg * msg)
{
  if (!msg) {
    return;
  }
  // maxvel
  std_msgs__msg__Float64__fini(&msg->maxvel);
  // pot
  std_msgs__msg__Float64__fini(&msg->pot);
  // increase_maxvel
  std_msgs__msg__Int16__fini(&msg->increase_maxvel);
  // decrease_maxvel
  std_msgs__msg__Int16__fini(&msg->decrease_maxvel);
  // car_mode
  std_msgs__msg__Int16__fini(&msg->car_mode);
  // pot_mode
  std_msgs__msg__Int16__fini(&msg->pot_mode);
}

bool
sdv_msgs__msg__ThrottleMsg__are_equal(const sdv_msgs__msg__ThrottleMsg * lhs, const sdv_msgs__msg__ThrottleMsg * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // maxvel
  if (!std_msgs__msg__Float64__are_equal(
      &(lhs->maxvel), &(rhs->maxvel)))
  {
    return false;
  }
  // pot
  if (!std_msgs__msg__Float64__are_equal(
      &(lhs->pot), &(rhs->pot)))
  {
    return false;
  }
  // increase_maxvel
  if (!std_msgs__msg__Int16__are_equal(
      &(lhs->increase_maxvel), &(rhs->increase_maxvel)))
  {
    return false;
  }
  // decrease_maxvel
  if (!std_msgs__msg__Int16__are_equal(
      &(lhs->decrease_maxvel), &(rhs->decrease_maxvel)))
  {
    return false;
  }
  // car_mode
  if (!std_msgs__msg__Int16__are_equal(
      &(lhs->car_mode), &(rhs->car_mode)))
  {
    return false;
  }
  // pot_mode
  if (!std_msgs__msg__Int16__are_equal(
      &(lhs->pot_mode), &(rhs->pot_mode)))
  {
    return false;
  }
  return true;
}

bool
sdv_msgs__msg__ThrottleMsg__copy(
  const sdv_msgs__msg__ThrottleMsg * input,
  sdv_msgs__msg__ThrottleMsg * output)
{
  if (!input || !output) {
    return false;
  }
  // maxvel
  if (!std_msgs__msg__Float64__copy(
      &(input->maxvel), &(output->maxvel)))
  {
    return false;
  }
  // pot
  if (!std_msgs__msg__Float64__copy(
      &(input->pot), &(output->pot)))
  {
    return false;
  }
  // increase_maxvel
  if (!std_msgs__msg__Int16__copy(
      &(input->increase_maxvel), &(output->increase_maxvel)))
  {
    return false;
  }
  // decrease_maxvel
  if (!std_msgs__msg__Int16__copy(
      &(input->decrease_maxvel), &(output->decrease_maxvel)))
  {
    return false;
  }
  // car_mode
  if (!std_msgs__msg__Int16__copy(
      &(input->car_mode), &(output->car_mode)))
  {
    return false;
  }
  // pot_mode
  if (!std_msgs__msg__Int16__copy(
      &(input->pot_mode), &(output->pot_mode)))
  {
    return false;
  }
  return true;
}

sdv_msgs__msg__ThrottleMsg *
sdv_msgs__msg__ThrottleMsg__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__ThrottleMsg * msg = (sdv_msgs__msg__ThrottleMsg *)allocator.allocate(sizeof(sdv_msgs__msg__ThrottleMsg), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sdv_msgs__msg__ThrottleMsg));
  bool success = sdv_msgs__msg__ThrottleMsg__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sdv_msgs__msg__ThrottleMsg__destroy(sdv_msgs__msg__ThrottleMsg * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sdv_msgs__msg__ThrottleMsg__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sdv_msgs__msg__ThrottleMsg__Sequence__init(sdv_msgs__msg__ThrottleMsg__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__ThrottleMsg * data = NULL;

  if (size) {
    data = (sdv_msgs__msg__ThrottleMsg *)allocator.zero_allocate(size, sizeof(sdv_msgs__msg__ThrottleMsg), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sdv_msgs__msg__ThrottleMsg__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sdv_msgs__msg__ThrottleMsg__fini(&data[i - 1]);
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
sdv_msgs__msg__ThrottleMsg__Sequence__fini(sdv_msgs__msg__ThrottleMsg__Sequence * array)
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
      sdv_msgs__msg__ThrottleMsg__fini(&array->data[i]);
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

sdv_msgs__msg__ThrottleMsg__Sequence *
sdv_msgs__msg__ThrottleMsg__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__ThrottleMsg__Sequence * array = (sdv_msgs__msg__ThrottleMsg__Sequence *)allocator.allocate(sizeof(sdv_msgs__msg__ThrottleMsg__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sdv_msgs__msg__ThrottleMsg__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sdv_msgs__msg__ThrottleMsg__Sequence__destroy(sdv_msgs__msg__ThrottleMsg__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sdv_msgs__msg__ThrottleMsg__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sdv_msgs__msg__ThrottleMsg__Sequence__are_equal(const sdv_msgs__msg__ThrottleMsg__Sequence * lhs, const sdv_msgs__msg__ThrottleMsg__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sdv_msgs__msg__ThrottleMsg__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sdv_msgs__msg__ThrottleMsg__Sequence__copy(
  const sdv_msgs__msg__ThrottleMsg__Sequence * input,
  sdv_msgs__msg__ThrottleMsg__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sdv_msgs__msg__ThrottleMsg);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sdv_msgs__msg__ThrottleMsg * data =
      (sdv_msgs__msg__ThrottleMsg *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sdv_msgs__msg__ThrottleMsg__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sdv_msgs__msg__ThrottleMsg__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sdv_msgs__msg__ThrottleMsg__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
