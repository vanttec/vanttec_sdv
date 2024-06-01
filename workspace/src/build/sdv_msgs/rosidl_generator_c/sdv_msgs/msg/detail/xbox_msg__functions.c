// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sdv_msgs:msg/XboxMsg.idl
// generated code does not contain a copyright notice
#include "sdv_msgs/msg/detail/xbox_msg__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `connected`
#include "std_msgs/msg/detail/bool__functions.h"
// Member `back`
// Member `a`
// Member `b`
// Member `x`
// Member `y`
// Member `dpad_up`
// Member `dpad_down`
// Member `dpad_left`
// Member `dpad_right`
#include "std_msgs/msg/detail/int16__functions.h"
// Member `leftx`
// Member `lefty`
// Member `right_trigger`
#include "std_msgs/msg/detail/float64__functions.h"

bool
sdv_msgs__msg__XboxMsg__init(sdv_msgs__msg__XboxMsg * msg)
{
  if (!msg) {
    return false;
  }
  // connected
  if (!std_msgs__msg__Bool__init(&msg->connected)) {
    sdv_msgs__msg__XboxMsg__fini(msg);
    return false;
  }
  // back
  if (!std_msgs__msg__Int16__init(&msg->back)) {
    sdv_msgs__msg__XboxMsg__fini(msg);
    return false;
  }
  // leftx
  if (!std_msgs__msg__Float64__init(&msg->leftx)) {
    sdv_msgs__msg__XboxMsg__fini(msg);
    return false;
  }
  // lefty
  if (!std_msgs__msg__Float64__init(&msg->lefty)) {
    sdv_msgs__msg__XboxMsg__fini(msg);
    return false;
  }
  // right_trigger
  if (!std_msgs__msg__Float64__init(&msg->right_trigger)) {
    sdv_msgs__msg__XboxMsg__fini(msg);
    return false;
  }
  // a
  if (!std_msgs__msg__Int16__init(&msg->a)) {
    sdv_msgs__msg__XboxMsg__fini(msg);
    return false;
  }
  // b
  if (!std_msgs__msg__Int16__init(&msg->b)) {
    sdv_msgs__msg__XboxMsg__fini(msg);
    return false;
  }
  // x
  if (!std_msgs__msg__Int16__init(&msg->x)) {
    sdv_msgs__msg__XboxMsg__fini(msg);
    return false;
  }
  // y
  if (!std_msgs__msg__Int16__init(&msg->y)) {
    sdv_msgs__msg__XboxMsg__fini(msg);
    return false;
  }
  // dpad_up
  if (!std_msgs__msg__Int16__init(&msg->dpad_up)) {
    sdv_msgs__msg__XboxMsg__fini(msg);
    return false;
  }
  // dpad_down
  if (!std_msgs__msg__Int16__init(&msg->dpad_down)) {
    sdv_msgs__msg__XboxMsg__fini(msg);
    return false;
  }
  // dpad_left
  if (!std_msgs__msg__Int16__init(&msg->dpad_left)) {
    sdv_msgs__msg__XboxMsg__fini(msg);
    return false;
  }
  // dpad_right
  if (!std_msgs__msg__Int16__init(&msg->dpad_right)) {
    sdv_msgs__msg__XboxMsg__fini(msg);
    return false;
  }
  return true;
}

void
sdv_msgs__msg__XboxMsg__fini(sdv_msgs__msg__XboxMsg * msg)
{
  if (!msg) {
    return;
  }
  // connected
  std_msgs__msg__Bool__fini(&msg->connected);
  // back
  std_msgs__msg__Int16__fini(&msg->back);
  // leftx
  std_msgs__msg__Float64__fini(&msg->leftx);
  // lefty
  std_msgs__msg__Float64__fini(&msg->lefty);
  // right_trigger
  std_msgs__msg__Float64__fini(&msg->right_trigger);
  // a
  std_msgs__msg__Int16__fini(&msg->a);
  // b
  std_msgs__msg__Int16__fini(&msg->b);
  // x
  std_msgs__msg__Int16__fini(&msg->x);
  // y
  std_msgs__msg__Int16__fini(&msg->y);
  // dpad_up
  std_msgs__msg__Int16__fini(&msg->dpad_up);
  // dpad_down
  std_msgs__msg__Int16__fini(&msg->dpad_down);
  // dpad_left
  std_msgs__msg__Int16__fini(&msg->dpad_left);
  // dpad_right
  std_msgs__msg__Int16__fini(&msg->dpad_right);
}

bool
sdv_msgs__msg__XboxMsg__are_equal(const sdv_msgs__msg__XboxMsg * lhs, const sdv_msgs__msg__XboxMsg * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // connected
  if (!std_msgs__msg__Bool__are_equal(
      &(lhs->connected), &(rhs->connected)))
  {
    return false;
  }
  // back
  if (!std_msgs__msg__Int16__are_equal(
      &(lhs->back), &(rhs->back)))
  {
    return false;
  }
  // leftx
  if (!std_msgs__msg__Float64__are_equal(
      &(lhs->leftx), &(rhs->leftx)))
  {
    return false;
  }
  // lefty
  if (!std_msgs__msg__Float64__are_equal(
      &(lhs->lefty), &(rhs->lefty)))
  {
    return false;
  }
  // right_trigger
  if (!std_msgs__msg__Float64__are_equal(
      &(lhs->right_trigger), &(rhs->right_trigger)))
  {
    return false;
  }
  // a
  if (!std_msgs__msg__Int16__are_equal(
      &(lhs->a), &(rhs->a)))
  {
    return false;
  }
  // b
  if (!std_msgs__msg__Int16__are_equal(
      &(lhs->b), &(rhs->b)))
  {
    return false;
  }
  // x
  if (!std_msgs__msg__Int16__are_equal(
      &(lhs->x), &(rhs->x)))
  {
    return false;
  }
  // y
  if (!std_msgs__msg__Int16__are_equal(
      &(lhs->y), &(rhs->y)))
  {
    return false;
  }
  // dpad_up
  if (!std_msgs__msg__Int16__are_equal(
      &(lhs->dpad_up), &(rhs->dpad_up)))
  {
    return false;
  }
  // dpad_down
  if (!std_msgs__msg__Int16__are_equal(
      &(lhs->dpad_down), &(rhs->dpad_down)))
  {
    return false;
  }
  // dpad_left
  if (!std_msgs__msg__Int16__are_equal(
      &(lhs->dpad_left), &(rhs->dpad_left)))
  {
    return false;
  }
  // dpad_right
  if (!std_msgs__msg__Int16__are_equal(
      &(lhs->dpad_right), &(rhs->dpad_right)))
  {
    return false;
  }
  return true;
}

bool
sdv_msgs__msg__XboxMsg__copy(
  const sdv_msgs__msg__XboxMsg * input,
  sdv_msgs__msg__XboxMsg * output)
{
  if (!input || !output) {
    return false;
  }
  // connected
  if (!std_msgs__msg__Bool__copy(
      &(input->connected), &(output->connected)))
  {
    return false;
  }
  // back
  if (!std_msgs__msg__Int16__copy(
      &(input->back), &(output->back)))
  {
    return false;
  }
  // leftx
  if (!std_msgs__msg__Float64__copy(
      &(input->leftx), &(output->leftx)))
  {
    return false;
  }
  // lefty
  if (!std_msgs__msg__Float64__copy(
      &(input->lefty), &(output->lefty)))
  {
    return false;
  }
  // right_trigger
  if (!std_msgs__msg__Float64__copy(
      &(input->right_trigger), &(output->right_trigger)))
  {
    return false;
  }
  // a
  if (!std_msgs__msg__Int16__copy(
      &(input->a), &(output->a)))
  {
    return false;
  }
  // b
  if (!std_msgs__msg__Int16__copy(
      &(input->b), &(output->b)))
  {
    return false;
  }
  // x
  if (!std_msgs__msg__Int16__copy(
      &(input->x), &(output->x)))
  {
    return false;
  }
  // y
  if (!std_msgs__msg__Int16__copy(
      &(input->y), &(output->y)))
  {
    return false;
  }
  // dpad_up
  if (!std_msgs__msg__Int16__copy(
      &(input->dpad_up), &(output->dpad_up)))
  {
    return false;
  }
  // dpad_down
  if (!std_msgs__msg__Int16__copy(
      &(input->dpad_down), &(output->dpad_down)))
  {
    return false;
  }
  // dpad_left
  if (!std_msgs__msg__Int16__copy(
      &(input->dpad_left), &(output->dpad_left)))
  {
    return false;
  }
  // dpad_right
  if (!std_msgs__msg__Int16__copy(
      &(input->dpad_right), &(output->dpad_right)))
  {
    return false;
  }
  return true;
}

sdv_msgs__msg__XboxMsg *
sdv_msgs__msg__XboxMsg__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__XboxMsg * msg = (sdv_msgs__msg__XboxMsg *)allocator.allocate(sizeof(sdv_msgs__msg__XboxMsg), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sdv_msgs__msg__XboxMsg));
  bool success = sdv_msgs__msg__XboxMsg__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sdv_msgs__msg__XboxMsg__destroy(sdv_msgs__msg__XboxMsg * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sdv_msgs__msg__XboxMsg__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sdv_msgs__msg__XboxMsg__Sequence__init(sdv_msgs__msg__XboxMsg__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__XboxMsg * data = NULL;

  if (size) {
    data = (sdv_msgs__msg__XboxMsg *)allocator.zero_allocate(size, sizeof(sdv_msgs__msg__XboxMsg), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sdv_msgs__msg__XboxMsg__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sdv_msgs__msg__XboxMsg__fini(&data[i - 1]);
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
sdv_msgs__msg__XboxMsg__Sequence__fini(sdv_msgs__msg__XboxMsg__Sequence * array)
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
      sdv_msgs__msg__XboxMsg__fini(&array->data[i]);
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

sdv_msgs__msg__XboxMsg__Sequence *
sdv_msgs__msg__XboxMsg__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__XboxMsg__Sequence * array = (sdv_msgs__msg__XboxMsg__Sequence *)allocator.allocate(sizeof(sdv_msgs__msg__XboxMsg__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sdv_msgs__msg__XboxMsg__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sdv_msgs__msg__XboxMsg__Sequence__destroy(sdv_msgs__msg__XboxMsg__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sdv_msgs__msg__XboxMsg__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sdv_msgs__msg__XboxMsg__Sequence__are_equal(const sdv_msgs__msg__XboxMsg__Sequence * lhs, const sdv_msgs__msg__XboxMsg__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sdv_msgs__msg__XboxMsg__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sdv_msgs__msg__XboxMsg__Sequence__copy(
  const sdv_msgs__msg__XboxMsg__Sequence * input,
  sdv_msgs__msg__XboxMsg__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sdv_msgs__msg__XboxMsg);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sdv_msgs__msg__XboxMsg * data =
      (sdv_msgs__msg__XboxMsg *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sdv_msgs__msg__XboxMsg__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sdv_msgs__msg__XboxMsg__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sdv_msgs__msg__XboxMsg__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
