// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from sdv_msgs:msg/ThrustControl.idl
// generated code does not contain a copyright notice
#include "sdv_msgs/msg/detail/thrust_control__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "sdv_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "sdv_msgs/msg/detail/thrust_control__struct.h"
#include "sdv_msgs/msg/detail/thrust_control__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _ThrustControl__ros_msg_type = sdv_msgs__msg__ThrustControl;

static bool _ThrustControl__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _ThrustControl__ros_msg_type * ros_message = static_cast<const _ThrustControl__ros_msg_type *>(untyped_ros_message);
  // Field name: tau_x
  {
    cdr << ros_message->tau_x;
  }

  // Field name: tau_y
  {
    cdr << ros_message->tau_y;
  }

  // Field name: tau_z
  {
    cdr << ros_message->tau_z;
  }

  // Field name: tau_phi
  {
    cdr << ros_message->tau_phi;
  }

  // Field name: tau_theta
  {
    cdr << ros_message->tau_theta;
  }

  // Field name: tau_psi
  {
    cdr << ros_message->tau_psi;
  }

  return true;
}

static bool _ThrustControl__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _ThrustControl__ros_msg_type * ros_message = static_cast<_ThrustControl__ros_msg_type *>(untyped_ros_message);
  // Field name: tau_x
  {
    cdr >> ros_message->tau_x;
  }

  // Field name: tau_y
  {
    cdr >> ros_message->tau_y;
  }

  // Field name: tau_z
  {
    cdr >> ros_message->tau_z;
  }

  // Field name: tau_phi
  {
    cdr >> ros_message->tau_phi;
  }

  // Field name: tau_theta
  {
    cdr >> ros_message->tau_theta;
  }

  // Field name: tau_psi
  {
    cdr >> ros_message->tau_psi;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_sdv_msgs
size_t get_serialized_size_sdv_msgs__msg__ThrustControl(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _ThrustControl__ros_msg_type * ros_message = static_cast<const _ThrustControl__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name tau_x
  {
    size_t item_size = sizeof(ros_message->tau_x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name tau_y
  {
    size_t item_size = sizeof(ros_message->tau_y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name tau_z
  {
    size_t item_size = sizeof(ros_message->tau_z);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name tau_phi
  {
    size_t item_size = sizeof(ros_message->tau_phi);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name tau_theta
  {
    size_t item_size = sizeof(ros_message->tau_theta);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name tau_psi
  {
    size_t item_size = sizeof(ros_message->tau_psi);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _ThrustControl__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_sdv_msgs__msg__ThrustControl(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_sdv_msgs
size_t max_serialized_size_sdv_msgs__msg__ThrustControl(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: tau_x
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: tau_y
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: tau_z
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: tau_phi
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: tau_theta
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: tau_psi
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = sdv_msgs__msg__ThrustControl;
    is_plain =
      (
      offsetof(DataType, tau_psi) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _ThrustControl__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_sdv_msgs__msg__ThrustControl(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_ThrustControl = {
  "sdv_msgs::msg",
  "ThrustControl",
  _ThrustControl__cdr_serialize,
  _ThrustControl__cdr_deserialize,
  _ThrustControl__get_serialized_size,
  _ThrustControl__max_serialized_size
};

static rosidl_message_type_support_t _ThrustControl__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_ThrustControl,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, sdv_msgs, msg, ThrustControl)() {
  return &_ThrustControl__type_support;
}

#if defined(__cplusplus)
}
#endif
