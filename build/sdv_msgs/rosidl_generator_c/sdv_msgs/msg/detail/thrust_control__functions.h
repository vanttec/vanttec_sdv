// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from sdv_msgs:msg/ThrustControl.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__THRUST_CONTROL__FUNCTIONS_H_
#define SDV_MSGS__MSG__DETAIL__THRUST_CONTROL__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "sdv_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "sdv_msgs/msg/detail/thrust_control__struct.h"

/// Initialize msg/ThrustControl message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * sdv_msgs__msg__ThrustControl
 * )) before or use
 * sdv_msgs__msg__ThrustControl__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_sdv_msgs
bool
sdv_msgs__msg__ThrustControl__init(sdv_msgs__msg__ThrustControl * msg);

/// Finalize msg/ThrustControl message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sdv_msgs
void
sdv_msgs__msg__ThrustControl__fini(sdv_msgs__msg__ThrustControl * msg);

/// Create msg/ThrustControl message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * sdv_msgs__msg__ThrustControl__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_sdv_msgs
sdv_msgs__msg__ThrustControl *
sdv_msgs__msg__ThrustControl__create();

/// Destroy msg/ThrustControl message.
/**
 * It calls
 * sdv_msgs__msg__ThrustControl__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sdv_msgs
void
sdv_msgs__msg__ThrustControl__destroy(sdv_msgs__msg__ThrustControl * msg);

/// Check for msg/ThrustControl message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_sdv_msgs
bool
sdv_msgs__msg__ThrustControl__are_equal(const sdv_msgs__msg__ThrustControl * lhs, const sdv_msgs__msg__ThrustControl * rhs);

/// Copy a msg/ThrustControl message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_sdv_msgs
bool
sdv_msgs__msg__ThrustControl__copy(
  const sdv_msgs__msg__ThrustControl * input,
  sdv_msgs__msg__ThrustControl * output);

/// Initialize array of msg/ThrustControl messages.
/**
 * It allocates the memory for the number of elements and calls
 * sdv_msgs__msg__ThrustControl__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_sdv_msgs
bool
sdv_msgs__msg__ThrustControl__Sequence__init(sdv_msgs__msg__ThrustControl__Sequence * array, size_t size);

/// Finalize array of msg/ThrustControl messages.
/**
 * It calls
 * sdv_msgs__msg__ThrustControl__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sdv_msgs
void
sdv_msgs__msg__ThrustControl__Sequence__fini(sdv_msgs__msg__ThrustControl__Sequence * array);

/// Create array of msg/ThrustControl messages.
/**
 * It allocates the memory for the array and calls
 * sdv_msgs__msg__ThrustControl__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_sdv_msgs
sdv_msgs__msg__ThrustControl__Sequence *
sdv_msgs__msg__ThrustControl__Sequence__create(size_t size);

/// Destroy array of msg/ThrustControl messages.
/**
 * It calls
 * sdv_msgs__msg__ThrustControl__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sdv_msgs
void
sdv_msgs__msg__ThrustControl__Sequence__destroy(sdv_msgs__msg__ThrustControl__Sequence * array);

/// Check for msg/ThrustControl message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_sdv_msgs
bool
sdv_msgs__msg__ThrustControl__Sequence__are_equal(const sdv_msgs__msg__ThrustControl__Sequence * lhs, const sdv_msgs__msg__ThrustControl__Sequence * rhs);

/// Copy an array of msg/ThrustControl messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_sdv_msgs
bool
sdv_msgs__msg__ThrustControl__Sequence__copy(
  const sdv_msgs__msg__ThrustControl__Sequence * input,
  sdv_msgs__msg__ThrustControl__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // SDV_MSGS__MSG__DETAIL__THRUST_CONTROL__FUNCTIONS_H_
