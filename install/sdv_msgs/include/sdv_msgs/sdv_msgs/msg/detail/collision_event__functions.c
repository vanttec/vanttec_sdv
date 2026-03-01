// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sdv_msgs:msg/CollisionEvent.idl
// generated code does not contain a copyright notice
#include "sdv_msgs/msg/detail/collision_event__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `normal_impulse`
#include "geometry_msgs/msg/detail/vector3__functions.h"

bool
sdv_msgs__msg__CollisionEvent__init(sdv_msgs__msg__CollisionEvent * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    sdv_msgs__msg__CollisionEvent__fini(msg);
    return false;
  }
  // other_actor_id
  // normal_impulse
  if (!geometry_msgs__msg__Vector3__init(&msg->normal_impulse)) {
    sdv_msgs__msg__CollisionEvent__fini(msg);
    return false;
  }
  return true;
}

void
sdv_msgs__msg__CollisionEvent__fini(sdv_msgs__msg__CollisionEvent * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // other_actor_id
  // normal_impulse
  geometry_msgs__msg__Vector3__fini(&msg->normal_impulse);
}

bool
sdv_msgs__msg__CollisionEvent__are_equal(const sdv_msgs__msg__CollisionEvent * lhs, const sdv_msgs__msg__CollisionEvent * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // other_actor_id
  if (lhs->other_actor_id != rhs->other_actor_id) {
    return false;
  }
  // normal_impulse
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->normal_impulse), &(rhs->normal_impulse)))
  {
    return false;
  }
  return true;
}

bool
sdv_msgs__msg__CollisionEvent__copy(
  const sdv_msgs__msg__CollisionEvent * input,
  sdv_msgs__msg__CollisionEvent * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // other_actor_id
  output->other_actor_id = input->other_actor_id;
  // normal_impulse
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->normal_impulse), &(output->normal_impulse)))
  {
    return false;
  }
  return true;
}

sdv_msgs__msg__CollisionEvent *
sdv_msgs__msg__CollisionEvent__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__CollisionEvent * msg = (sdv_msgs__msg__CollisionEvent *)allocator.allocate(sizeof(sdv_msgs__msg__CollisionEvent), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sdv_msgs__msg__CollisionEvent));
  bool success = sdv_msgs__msg__CollisionEvent__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sdv_msgs__msg__CollisionEvent__destroy(sdv_msgs__msg__CollisionEvent * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sdv_msgs__msg__CollisionEvent__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sdv_msgs__msg__CollisionEvent__Sequence__init(sdv_msgs__msg__CollisionEvent__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__CollisionEvent * data = NULL;

  if (size) {
    data = (sdv_msgs__msg__CollisionEvent *)allocator.zero_allocate(size, sizeof(sdv_msgs__msg__CollisionEvent), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sdv_msgs__msg__CollisionEvent__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sdv_msgs__msg__CollisionEvent__fini(&data[i - 1]);
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
sdv_msgs__msg__CollisionEvent__Sequence__fini(sdv_msgs__msg__CollisionEvent__Sequence * array)
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
      sdv_msgs__msg__CollisionEvent__fini(&array->data[i]);
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

sdv_msgs__msg__CollisionEvent__Sequence *
sdv_msgs__msg__CollisionEvent__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sdv_msgs__msg__CollisionEvent__Sequence * array = (sdv_msgs__msg__CollisionEvent__Sequence *)allocator.allocate(sizeof(sdv_msgs__msg__CollisionEvent__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sdv_msgs__msg__CollisionEvent__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sdv_msgs__msg__CollisionEvent__Sequence__destroy(sdv_msgs__msg__CollisionEvent__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sdv_msgs__msg__CollisionEvent__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sdv_msgs__msg__CollisionEvent__Sequence__are_equal(const sdv_msgs__msg__CollisionEvent__Sequence * lhs, const sdv_msgs__msg__CollisionEvent__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sdv_msgs__msg__CollisionEvent__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sdv_msgs__msg__CollisionEvent__Sequence__copy(
  const sdv_msgs__msg__CollisionEvent__Sequence * input,
  sdv_msgs__msg__CollisionEvent__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sdv_msgs__msg__CollisionEvent);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sdv_msgs__msg__CollisionEvent * data =
      (sdv_msgs__msg__CollisionEvent *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sdv_msgs__msg__CollisionEvent__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sdv_msgs__msg__CollisionEvent__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sdv_msgs__msg__CollisionEvent__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
