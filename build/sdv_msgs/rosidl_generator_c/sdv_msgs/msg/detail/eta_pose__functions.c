// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sdv_msgs:msg/EtaPose.idl
// generated code does not contain a copyright notice
#include "sdv_msgs/msg/detail/eta_pose__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
sdv_msgs__msg__EtaPose__init(sdv_msgs__msg__EtaPose * msg)
{
  if (!msg) {
    return false;
  }
  // x
  // y
  // z
  // phi
  // theta
  // psi
  return true;
}

void
sdv_msgs__msg__EtaPose__fini(sdv_msgs__msg__EtaPose * msg)
{
  if (!msg) {
    return;
  }
  // x
  // y
  // z
  // phi
  // theta
  // psi
}

bool
sdv_msgs__msg__EtaPose__are_equal(const sdv_msgs__msg__EtaPose * lhs, const sdv_msgs__msg__EtaPose * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  // z
  if (lhs->z != rhs->z) {
    return false;
  }
  // phi
  if (lhs->phi != rhs->phi) {
    return false;
  }
  // theta
  if (lhs->theta != rhs->theta) {
    return false;
  }
  // psi
  if (lhs->psi != rhs->psi) {
    return false;
  }
  return true;
}

bool
sdv_msgs__msg__EtaPose__copy(
  const sdv_msgs__msg__EtaPose * input,
  sdv_msgs__msg__EtaPose * output)
{
  if (!input || !output) {
    return false;
  }
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  // z
  output->z = input->z;
  // phi
  output->phi = input->phi;
  // theta
  output->theta = input->theta;
  // psi
  output->psi = input->psi;
  return true;
}

sdv_msgs__msg__EtaPose *
sdv_msgs__msg__EtaPose__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__EtaPose * msg = (sdv_msgs__msg__EtaPose *)allocator.allocate(sizeof(sdv_msgs__msg__EtaPose), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sdv_msgs__msg__EtaPose));
  bool success = sdv_msgs__msg__EtaPose__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sdv_msgs__msg__EtaPose__destroy(sdv_msgs__msg__EtaPose * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sdv_msgs__msg__EtaPose__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sdv_msgs__msg__EtaPose__Sequence__init(sdv_msgs__msg__EtaPose__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__EtaPose * data = NULL;

  if (size) {
    data = (sdv_msgs__msg__EtaPose *)allocator.zero_allocate(size, sizeof(sdv_msgs__msg__EtaPose), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sdv_msgs__msg__EtaPose__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sdv_msgs__msg__EtaPose__fini(&data[i - 1]);
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
sdv_msgs__msg__EtaPose__Sequence__fini(sdv_msgs__msg__EtaPose__Sequence * array)
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
      sdv_msgs__msg__EtaPose__fini(&array->data[i]);
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

sdv_msgs__msg__EtaPose__Sequence *
sdv_msgs__msg__EtaPose__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__EtaPose__Sequence * array = (sdv_msgs__msg__EtaPose__Sequence *)allocator.allocate(sizeof(sdv_msgs__msg__EtaPose__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sdv_msgs__msg__EtaPose__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sdv_msgs__msg__EtaPose__Sequence__destroy(sdv_msgs__msg__EtaPose__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sdv_msgs__msg__EtaPose__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sdv_msgs__msg__EtaPose__Sequence__are_equal(const sdv_msgs__msg__EtaPose__Sequence * lhs, const sdv_msgs__msg__EtaPose__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sdv_msgs__msg__EtaPose__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sdv_msgs__msg__EtaPose__Sequence__copy(
  const sdv_msgs__msg__EtaPose__Sequence * input,
  sdv_msgs__msg__EtaPose__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sdv_msgs__msg__EtaPose);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sdv_msgs__msg__EtaPose * data =
      (sdv_msgs__msg__EtaPose *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sdv_msgs__msg__EtaPose__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sdv_msgs__msg__EtaPose__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sdv_msgs__msg__EtaPose__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
