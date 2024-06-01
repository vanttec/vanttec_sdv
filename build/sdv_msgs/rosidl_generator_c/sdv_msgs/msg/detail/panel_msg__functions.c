// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sdv_msgs:msg/PanelMsg.idl
// generated code does not contain a copyright notice
#include "sdv_msgs/msg/detail/panel_msg__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `wiper`
// Member `horn`
// Member `right_upper_front_light`
// Member `left_upper_front_light`
// Member `right_down_front_light`
// Member `left_down_front_light`
// Member `back`
#include "std_msgs/msg/detail/bool__functions.h"
// Member `xboxcontrol`
#include "std_msgs/msg/detail/byte_multi_array__functions.h"

bool
sdv_msgs__msg__PanelMsg__init(sdv_msgs__msg__PanelMsg * msg)
{
  if (!msg) {
    return false;
  }
  // wiper
  if (!std_msgs__msg__Bool__init(&msg->wiper)) {
    sdv_msgs__msg__PanelMsg__fini(msg);
    return false;
  }
  // horn
  if (!std_msgs__msg__Bool__init(&msg->horn)) {
    sdv_msgs__msg__PanelMsg__fini(msg);
    return false;
  }
  // right_upper_front_light
  if (!std_msgs__msg__Bool__init(&msg->right_upper_front_light)) {
    sdv_msgs__msg__PanelMsg__fini(msg);
    return false;
  }
  // left_upper_front_light
  if (!std_msgs__msg__Bool__init(&msg->left_upper_front_light)) {
    sdv_msgs__msg__PanelMsg__fini(msg);
    return false;
  }
  // right_down_front_light
  if (!std_msgs__msg__Bool__init(&msg->right_down_front_light)) {
    sdv_msgs__msg__PanelMsg__fini(msg);
    return false;
  }
  // left_down_front_light
  if (!std_msgs__msg__Bool__init(&msg->left_down_front_light)) {
    sdv_msgs__msg__PanelMsg__fini(msg);
    return false;
  }
  // back
  if (!std_msgs__msg__Bool__init(&msg->back)) {
    sdv_msgs__msg__PanelMsg__fini(msg);
    return false;
  }
  // xboxcontrol
  if (!std_msgs__msg__ByteMultiArray__init(&msg->xboxcontrol)) {
    sdv_msgs__msg__PanelMsg__fini(msg);
    return false;
  }
  return true;
}

void
sdv_msgs__msg__PanelMsg__fini(sdv_msgs__msg__PanelMsg * msg)
{
  if (!msg) {
    return;
  }
  // wiper
  std_msgs__msg__Bool__fini(&msg->wiper);
  // horn
  std_msgs__msg__Bool__fini(&msg->horn);
  // right_upper_front_light
  std_msgs__msg__Bool__fini(&msg->right_upper_front_light);
  // left_upper_front_light
  std_msgs__msg__Bool__fini(&msg->left_upper_front_light);
  // right_down_front_light
  std_msgs__msg__Bool__fini(&msg->right_down_front_light);
  // left_down_front_light
  std_msgs__msg__Bool__fini(&msg->left_down_front_light);
  // back
  std_msgs__msg__Bool__fini(&msg->back);
  // xboxcontrol
  std_msgs__msg__ByteMultiArray__fini(&msg->xboxcontrol);
}

bool
sdv_msgs__msg__PanelMsg__are_equal(const sdv_msgs__msg__PanelMsg * lhs, const sdv_msgs__msg__PanelMsg * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // wiper
  if (!std_msgs__msg__Bool__are_equal(
      &(lhs->wiper), &(rhs->wiper)))
  {
    return false;
  }
  // horn
  if (!std_msgs__msg__Bool__are_equal(
      &(lhs->horn), &(rhs->horn)))
  {
    return false;
  }
  // right_upper_front_light
  if (!std_msgs__msg__Bool__are_equal(
      &(lhs->right_upper_front_light), &(rhs->right_upper_front_light)))
  {
    return false;
  }
  // left_upper_front_light
  if (!std_msgs__msg__Bool__are_equal(
      &(lhs->left_upper_front_light), &(rhs->left_upper_front_light)))
  {
    return false;
  }
  // right_down_front_light
  if (!std_msgs__msg__Bool__are_equal(
      &(lhs->right_down_front_light), &(rhs->right_down_front_light)))
  {
    return false;
  }
  // left_down_front_light
  if (!std_msgs__msg__Bool__are_equal(
      &(lhs->left_down_front_light), &(rhs->left_down_front_light)))
  {
    return false;
  }
  // back
  if (!std_msgs__msg__Bool__are_equal(
      &(lhs->back), &(rhs->back)))
  {
    return false;
  }
  // xboxcontrol
  if (!std_msgs__msg__ByteMultiArray__are_equal(
      &(lhs->xboxcontrol), &(rhs->xboxcontrol)))
  {
    return false;
  }
  return true;
}

bool
sdv_msgs__msg__PanelMsg__copy(
  const sdv_msgs__msg__PanelMsg * input,
  sdv_msgs__msg__PanelMsg * output)
{
  if (!input || !output) {
    return false;
  }
  // wiper
  if (!std_msgs__msg__Bool__copy(
      &(input->wiper), &(output->wiper)))
  {
    return false;
  }
  // horn
  if (!std_msgs__msg__Bool__copy(
      &(input->horn), &(output->horn)))
  {
    return false;
  }
  // right_upper_front_light
  if (!std_msgs__msg__Bool__copy(
      &(input->right_upper_front_light), &(output->right_upper_front_light)))
  {
    return false;
  }
  // left_upper_front_light
  if (!std_msgs__msg__Bool__copy(
      &(input->left_upper_front_light), &(output->left_upper_front_light)))
  {
    return false;
  }
  // right_down_front_light
  if (!std_msgs__msg__Bool__copy(
      &(input->right_down_front_light), &(output->right_down_front_light)))
  {
    return false;
  }
  // left_down_front_light
  if (!std_msgs__msg__Bool__copy(
      &(input->left_down_front_light), &(output->left_down_front_light)))
  {
    return false;
  }
  // back
  if (!std_msgs__msg__Bool__copy(
      &(input->back), &(output->back)))
  {
    return false;
  }
  // xboxcontrol
  if (!std_msgs__msg__ByteMultiArray__copy(
      &(input->xboxcontrol), &(output->xboxcontrol)))
  {
    return false;
  }
  return true;
}

sdv_msgs__msg__PanelMsg *
sdv_msgs__msg__PanelMsg__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__PanelMsg * msg = (sdv_msgs__msg__PanelMsg *)allocator.allocate(sizeof(sdv_msgs__msg__PanelMsg), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sdv_msgs__msg__PanelMsg));
  bool success = sdv_msgs__msg__PanelMsg__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sdv_msgs__msg__PanelMsg__destroy(sdv_msgs__msg__PanelMsg * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sdv_msgs__msg__PanelMsg__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sdv_msgs__msg__PanelMsg__Sequence__init(sdv_msgs__msg__PanelMsg__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__PanelMsg * data = NULL;

  if (size) {
    data = (sdv_msgs__msg__PanelMsg *)allocator.zero_allocate(size, sizeof(sdv_msgs__msg__PanelMsg), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sdv_msgs__msg__PanelMsg__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sdv_msgs__msg__PanelMsg__fini(&data[i - 1]);
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
sdv_msgs__msg__PanelMsg__Sequence__fini(sdv_msgs__msg__PanelMsg__Sequence * array)
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
      sdv_msgs__msg__PanelMsg__fini(&array->data[i]);
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

sdv_msgs__msg__PanelMsg__Sequence *
sdv_msgs__msg__PanelMsg__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__PanelMsg__Sequence * array = (sdv_msgs__msg__PanelMsg__Sequence *)allocator.allocate(sizeof(sdv_msgs__msg__PanelMsg__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sdv_msgs__msg__PanelMsg__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sdv_msgs__msg__PanelMsg__Sequence__destroy(sdv_msgs__msg__PanelMsg__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sdv_msgs__msg__PanelMsg__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sdv_msgs__msg__PanelMsg__Sequence__are_equal(const sdv_msgs__msg__PanelMsg__Sequence * lhs, const sdv_msgs__msg__PanelMsg__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sdv_msgs__msg__PanelMsg__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sdv_msgs__msg__PanelMsg__Sequence__copy(
  const sdv_msgs__msg__PanelMsg__Sequence * input,
  sdv_msgs__msg__PanelMsg__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sdv_msgs__msg__PanelMsg);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sdv_msgs__msg__PanelMsg * data =
      (sdv_msgs__msg__PanelMsg *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sdv_msgs__msg__PanelMsg__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sdv_msgs__msg__PanelMsg__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sdv_msgs__msg__PanelMsg__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
