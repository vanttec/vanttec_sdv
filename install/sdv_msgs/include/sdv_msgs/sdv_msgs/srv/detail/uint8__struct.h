// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sdv_msgs:srv/Uint8.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__SRV__DETAIL__UINT8__STRUCT_H_
#define SDV_MSGS__SRV__DETAIL__UINT8__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/Uint8 in the package sdv_msgs.
typedef struct sdv_msgs__srv__Uint8_Request
{
  uint8_t data;
} sdv_msgs__srv__Uint8_Request;

// Struct for a sequence of sdv_msgs__srv__Uint8_Request.
typedef struct sdv_msgs__srv__Uint8_Request__Sequence
{
  sdv_msgs__srv__Uint8_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sdv_msgs__srv__Uint8_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/Uint8 in the package sdv_msgs.
typedef struct sdv_msgs__srv__Uint8_Response
{
  uint8_t structure_needs_at_least_one_member;
} sdv_msgs__srv__Uint8_Response;

// Struct for a sequence of sdv_msgs__srv__Uint8_Response.
typedef struct sdv_msgs__srv__Uint8_Response__Sequence
{
  sdv_msgs__srv__Uint8_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sdv_msgs__srv__Uint8_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SDV_MSGS__SRV__DETAIL__UINT8__STRUCT_H_
