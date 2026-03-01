// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sdv_msgs:srv/Uint8.idl
// generated code does not contain a copyright notice
#include "sdv_msgs/srv/detail/uint8__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
sdv_msgs__srv__Uint8_Request__init(sdv_msgs__srv__Uint8_Request * msg)
{
  if (!msg) {
    return false;
  }
  // data
  return true;
}

void
sdv_msgs__srv__Uint8_Request__fini(sdv_msgs__srv__Uint8_Request * msg)
{
  if (!msg) {
    return;
  }
  // data
}

bool
sdv_msgs__srv__Uint8_Request__are_equal(const sdv_msgs__srv__Uint8_Request * lhs, const sdv_msgs__srv__Uint8_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // data
  if (lhs->data != rhs->data) {
    return false;
  }
  return true;
}

bool
sdv_msgs__srv__Uint8_Request__copy(
  const sdv_msgs__srv__Uint8_Request * input,
  sdv_msgs__srv__Uint8_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // data
  output->data = input->data;
  return true;
}

sdv_msgs__srv__Uint8_Request *
sdv_msgs__srv__Uint8_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__srv__Uint8_Request * msg = (sdv_msgs__srv__Uint8_Request *)allocator.allocate(sizeof(sdv_msgs__srv__Uint8_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sdv_msgs__srv__Uint8_Request));
  bool success = sdv_msgs__srv__Uint8_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sdv_msgs__srv__Uint8_Request__destroy(sdv_msgs__srv__Uint8_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sdv_msgs__srv__Uint8_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sdv_msgs__srv__Uint8_Request__Sequence__init(sdv_msgs__srv__Uint8_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__srv__Uint8_Request * data = NULL;

  if (size) {
    data = (sdv_msgs__srv__Uint8_Request *)allocator.zero_allocate(size, sizeof(sdv_msgs__srv__Uint8_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sdv_msgs__srv__Uint8_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sdv_msgs__srv__Uint8_Request__fini(&data[i - 1]);
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
sdv_msgs__srv__Uint8_Request__Sequence__fini(sdv_msgs__srv__Uint8_Request__Sequence * array)
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
      sdv_msgs__srv__Uint8_Request__fini(&array->data[i]);
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

sdv_msgs__srv__Uint8_Request__Sequence *
sdv_msgs__srv__Uint8_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__srv__Uint8_Request__Sequence * array = (sdv_msgs__srv__Uint8_Request__Sequence *)allocator.allocate(sizeof(sdv_msgs__srv__Uint8_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sdv_msgs__srv__Uint8_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sdv_msgs__srv__Uint8_Request__Sequence__destroy(sdv_msgs__srv__Uint8_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sdv_msgs__srv__Uint8_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sdv_msgs__srv__Uint8_Request__Sequence__are_equal(const sdv_msgs__srv__Uint8_Request__Sequence * lhs, const sdv_msgs__srv__Uint8_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sdv_msgs__srv__Uint8_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sdv_msgs__srv__Uint8_Request__Sequence__copy(
  const sdv_msgs__srv__Uint8_Request__Sequence * input,
  sdv_msgs__srv__Uint8_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sdv_msgs__srv__Uint8_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sdv_msgs__srv__Uint8_Request * data =
      (sdv_msgs__srv__Uint8_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sdv_msgs__srv__Uint8_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sdv_msgs__srv__Uint8_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sdv_msgs__srv__Uint8_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
sdv_msgs__srv__Uint8_Response__init(sdv_msgs__srv__Uint8_Response * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
sdv_msgs__srv__Uint8_Response__fini(sdv_msgs__srv__Uint8_Response * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
sdv_msgs__srv__Uint8_Response__are_equal(const sdv_msgs__srv__Uint8_Response * lhs, const sdv_msgs__srv__Uint8_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // structure_needs_at_least_one_member
  if (lhs->structure_needs_at_least_one_member != rhs->structure_needs_at_least_one_member) {
    return false;
  }
  return true;
}

bool
sdv_msgs__srv__Uint8_Response__copy(
  const sdv_msgs__srv__Uint8_Response * input,
  sdv_msgs__srv__Uint8_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

sdv_msgs__srv__Uint8_Response *
sdv_msgs__srv__Uint8_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__srv__Uint8_Response * msg = (sdv_msgs__srv__Uint8_Response *)allocator.allocate(sizeof(sdv_msgs__srv__Uint8_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sdv_msgs__srv__Uint8_Response));
  bool success = sdv_msgs__srv__Uint8_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sdv_msgs__srv__Uint8_Response__destroy(sdv_msgs__srv__Uint8_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sdv_msgs__srv__Uint8_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sdv_msgs__srv__Uint8_Response__Sequence__init(sdv_msgs__srv__Uint8_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__srv__Uint8_Response * data = NULL;

  if (size) {
    data = (sdv_msgs__srv__Uint8_Response *)allocator.zero_allocate(size, sizeof(sdv_msgs__srv__Uint8_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sdv_msgs__srv__Uint8_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sdv_msgs__srv__Uint8_Response__fini(&data[i - 1]);
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
sdv_msgs__srv__Uint8_Response__Sequence__fini(sdv_msgs__srv__Uint8_Response__Sequence * array)
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
      sdv_msgs__srv__Uint8_Response__fini(&array->data[i]);
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

sdv_msgs__srv__Uint8_Response__Sequence *
sdv_msgs__srv__Uint8_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__srv__Uint8_Response__Sequence * array = (sdv_msgs__srv__Uint8_Response__Sequence *)allocator.allocate(sizeof(sdv_msgs__srv__Uint8_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sdv_msgs__srv__Uint8_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sdv_msgs__srv__Uint8_Response__Sequence__destroy(sdv_msgs__srv__Uint8_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sdv_msgs__srv__Uint8_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sdv_msgs__srv__Uint8_Response__Sequence__are_equal(const sdv_msgs__srv__Uint8_Response__Sequence * lhs, const sdv_msgs__srv__Uint8_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sdv_msgs__srv__Uint8_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sdv_msgs__srv__Uint8_Response__Sequence__copy(
  const sdv_msgs__srv__Uint8_Response__Sequence * input,
  sdv_msgs__srv__Uint8_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sdv_msgs__srv__Uint8_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sdv_msgs__srv__Uint8_Response * data =
      (sdv_msgs__srv__Uint8_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sdv_msgs__srv__Uint8_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sdv_msgs__srv__Uint8_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sdv_msgs__srv__Uint8_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
