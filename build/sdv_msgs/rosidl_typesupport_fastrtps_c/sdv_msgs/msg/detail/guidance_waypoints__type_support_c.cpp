// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from sdv_msgs:msg/GuidanceWaypoints.idl
// generated code does not contain a copyright notice
#include "sdv_msgs/msg/detail/guidance_waypoints__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "sdv_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "sdv_msgs/msg/detail/guidance_waypoints__struct.h"
#include "sdv_msgs/msg/detail/guidance_waypoints__functions.h"
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

#include "rosidl_runtime_c/primitives_sequence.h"  // waypoint_list_x, waypoint_list_y, waypoint_list_z
#include "rosidl_runtime_c/primitives_sequence_functions.h"  // waypoint_list_x, waypoint_list_y, waypoint_list_z

// forward declare type support functions


using _GuidanceWaypoints__ros_msg_type = sdv_msgs__msg__GuidanceWaypoints;

static bool _GuidanceWaypoints__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _GuidanceWaypoints__ros_msg_type * ros_message = static_cast<const _GuidanceWaypoints__ros_msg_type *>(untyped_ros_message);
  // Field name: guidance_law
  {
    cdr << ros_message->guidance_law;
  }

  // Field name: waypoint_list_length
  {
    cdr << ros_message->waypoint_list_length;
  }

  // Field name: waypoint_list_x
  {
    size_t size = ros_message->waypoint_list_x.size;
    auto array_ptr = ros_message->waypoint_list_x.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: waypoint_list_y
  {
    size_t size = ros_message->waypoint_list_y.size;
    auto array_ptr = ros_message->waypoint_list_y.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: waypoint_list_z
  {
    size_t size = ros_message->waypoint_list_z.size;
    auto array_ptr = ros_message->waypoint_list_z.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: depth_setpoint
  {
    cdr << ros_message->depth_setpoint;
  }

  // Field name: heading_setpoint
  {
    cdr << ros_message->heading_setpoint;
  }

  return true;
}

static bool _GuidanceWaypoints__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _GuidanceWaypoints__ros_msg_type * ros_message = static_cast<_GuidanceWaypoints__ros_msg_type *>(untyped_ros_message);
  // Field name: guidance_law
  {
    cdr >> ros_message->guidance_law;
  }

  // Field name: waypoint_list_length
  {
    cdr >> ros_message->waypoint_list_length;
  }

  // Field name: waypoint_list_x
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->waypoint_list_x.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->waypoint_list_x);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->waypoint_list_x, size)) {
      fprintf(stderr, "failed to create array for field 'waypoint_list_x'");
      return false;
    }
    auto array_ptr = ros_message->waypoint_list_x.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: waypoint_list_y
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->waypoint_list_y.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->waypoint_list_y);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->waypoint_list_y, size)) {
      fprintf(stderr, "failed to create array for field 'waypoint_list_y'");
      return false;
    }
    auto array_ptr = ros_message->waypoint_list_y.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: waypoint_list_z
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->waypoint_list_z.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->waypoint_list_z);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->waypoint_list_z, size)) {
      fprintf(stderr, "failed to create array for field 'waypoint_list_z'");
      return false;
    }
    auto array_ptr = ros_message->waypoint_list_z.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: depth_setpoint
  {
    cdr >> ros_message->depth_setpoint;
  }

  // Field name: heading_setpoint
  {
    cdr >> ros_message->heading_setpoint;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_sdv_msgs
size_t get_serialized_size_sdv_msgs__msg__GuidanceWaypoints(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _GuidanceWaypoints__ros_msg_type * ros_message = static_cast<const _GuidanceWaypoints__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name guidance_law
  {
    size_t item_size = sizeof(ros_message->guidance_law);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name waypoint_list_length
  {
    size_t item_size = sizeof(ros_message->waypoint_list_length);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name waypoint_list_x
  {
    size_t array_size = ros_message->waypoint_list_x.size;
    auto array_ptr = ros_message->waypoint_list_x.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name waypoint_list_y
  {
    size_t array_size = ros_message->waypoint_list_y.size;
    auto array_ptr = ros_message->waypoint_list_y.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name waypoint_list_z
  {
    size_t array_size = ros_message->waypoint_list_z.size;
    auto array_ptr = ros_message->waypoint_list_z.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name depth_setpoint
  {
    size_t item_size = sizeof(ros_message->depth_setpoint);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name heading_setpoint
  {
    size_t item_size = sizeof(ros_message->heading_setpoint);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _GuidanceWaypoints__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_sdv_msgs__msg__GuidanceWaypoints(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_sdv_msgs
size_t max_serialized_size_sdv_msgs__msg__GuidanceWaypoints(
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

  // member: guidance_law
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: waypoint_list_length
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: waypoint_list_x
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: waypoint_list_y
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: waypoint_list_z
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: depth_setpoint
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: heading_setpoint
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
    using DataType = sdv_msgs__msg__GuidanceWaypoints;
    is_plain =
      (
      offsetof(DataType, heading_setpoint) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _GuidanceWaypoints__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_sdv_msgs__msg__GuidanceWaypoints(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_GuidanceWaypoints = {
  "sdv_msgs::msg",
  "GuidanceWaypoints",
  _GuidanceWaypoints__cdr_serialize,
  _GuidanceWaypoints__cdr_deserialize,
  _GuidanceWaypoints__get_serialized_size,
  _GuidanceWaypoints__max_serialized_size
};

static rosidl_message_type_support_t _GuidanceWaypoints__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_GuidanceWaypoints,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, sdv_msgs, msg, GuidanceWaypoints)() {
  return &_GuidanceWaypoints__type_support;
}

#if defined(__cplusplus)
}
#endif
