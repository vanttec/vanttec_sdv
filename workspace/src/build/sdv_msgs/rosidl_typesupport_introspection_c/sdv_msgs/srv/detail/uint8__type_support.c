// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from sdv_msgs:srv/Uint8.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "sdv_msgs/srv/detail/uint8__rosidl_typesupport_introspection_c.h"
#include "sdv_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "sdv_msgs/srv/detail/uint8__functions.h"
#include "sdv_msgs/srv/detail/uint8__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void sdv_msgs__srv__Uint8_Request__rosidl_typesupport_introspection_c__Uint8_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  sdv_msgs__srv__Uint8_Request__init(message_memory);
}

void sdv_msgs__srv__Uint8_Request__rosidl_typesupport_introspection_c__Uint8_Request_fini_function(void * message_memory)
{
  sdv_msgs__srv__Uint8_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember sdv_msgs__srv__Uint8_Request__rosidl_typesupport_introspection_c__Uint8_Request_message_member_array[1] = {
  {
    "data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__srv__Uint8_Request, data),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers sdv_msgs__srv__Uint8_Request__rosidl_typesupport_introspection_c__Uint8_Request_message_members = {
  "sdv_msgs__srv",  // message namespace
  "Uint8_Request",  // message name
  1,  // number of fields
  sizeof(sdv_msgs__srv__Uint8_Request),
  sdv_msgs__srv__Uint8_Request__rosidl_typesupport_introspection_c__Uint8_Request_message_member_array,  // message members
  sdv_msgs__srv__Uint8_Request__rosidl_typesupport_introspection_c__Uint8_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  sdv_msgs__srv__Uint8_Request__rosidl_typesupport_introspection_c__Uint8_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t sdv_msgs__srv__Uint8_Request__rosidl_typesupport_introspection_c__Uint8_Request_message_type_support_handle = {
  0,
  &sdv_msgs__srv__Uint8_Request__rosidl_typesupport_introspection_c__Uint8_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_sdv_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sdv_msgs, srv, Uint8_Request)() {
  if (!sdv_msgs__srv__Uint8_Request__rosidl_typesupport_introspection_c__Uint8_Request_message_type_support_handle.typesupport_identifier) {
    sdv_msgs__srv__Uint8_Request__rosidl_typesupport_introspection_c__Uint8_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &sdv_msgs__srv__Uint8_Request__rosidl_typesupport_introspection_c__Uint8_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "sdv_msgs/srv/detail/uint8__rosidl_typesupport_introspection_c.h"
// already included above
// #include "sdv_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "sdv_msgs/srv/detail/uint8__functions.h"
// already included above
// #include "sdv_msgs/srv/detail/uint8__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void sdv_msgs__srv__Uint8_Response__rosidl_typesupport_introspection_c__Uint8_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  sdv_msgs__srv__Uint8_Response__init(message_memory);
}

void sdv_msgs__srv__Uint8_Response__rosidl_typesupport_introspection_c__Uint8_Response_fini_function(void * message_memory)
{
  sdv_msgs__srv__Uint8_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember sdv_msgs__srv__Uint8_Response__rosidl_typesupport_introspection_c__Uint8_Response_message_member_array[1] = {
  {
    "structure_needs_at_least_one_member",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sdv_msgs__srv__Uint8_Response, structure_needs_at_least_one_member),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers sdv_msgs__srv__Uint8_Response__rosidl_typesupport_introspection_c__Uint8_Response_message_members = {
  "sdv_msgs__srv",  // message namespace
  "Uint8_Response",  // message name
  1,  // number of fields
  sizeof(sdv_msgs__srv__Uint8_Response),
  sdv_msgs__srv__Uint8_Response__rosidl_typesupport_introspection_c__Uint8_Response_message_member_array,  // message members
  sdv_msgs__srv__Uint8_Response__rosidl_typesupport_introspection_c__Uint8_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  sdv_msgs__srv__Uint8_Response__rosidl_typesupport_introspection_c__Uint8_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t sdv_msgs__srv__Uint8_Response__rosidl_typesupport_introspection_c__Uint8_Response_message_type_support_handle = {
  0,
  &sdv_msgs__srv__Uint8_Response__rosidl_typesupport_introspection_c__Uint8_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_sdv_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sdv_msgs, srv, Uint8_Response)() {
  if (!sdv_msgs__srv__Uint8_Response__rosidl_typesupport_introspection_c__Uint8_Response_message_type_support_handle.typesupport_identifier) {
    sdv_msgs__srv__Uint8_Response__rosidl_typesupport_introspection_c__Uint8_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &sdv_msgs__srv__Uint8_Response__rosidl_typesupport_introspection_c__Uint8_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "sdv_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "sdv_msgs/srv/detail/uint8__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers sdv_msgs__srv__detail__uint8__rosidl_typesupport_introspection_c__Uint8_service_members = {
  "sdv_msgs__srv",  // service namespace
  "Uint8",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // sdv_msgs__srv__detail__uint8__rosidl_typesupport_introspection_c__Uint8_Request_message_type_support_handle,
  NULL  // response message
  // sdv_msgs__srv__detail__uint8__rosidl_typesupport_introspection_c__Uint8_Response_message_type_support_handle
};

static rosidl_service_type_support_t sdv_msgs__srv__detail__uint8__rosidl_typesupport_introspection_c__Uint8_service_type_support_handle = {
  0,
  &sdv_msgs__srv__detail__uint8__rosidl_typesupport_introspection_c__Uint8_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sdv_msgs, srv, Uint8_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sdv_msgs, srv, Uint8_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_sdv_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sdv_msgs, srv, Uint8)() {
  if (!sdv_msgs__srv__detail__uint8__rosidl_typesupport_introspection_c__Uint8_service_type_support_handle.typesupport_identifier) {
    sdv_msgs__srv__detail__uint8__rosidl_typesupport_introspection_c__Uint8_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)sdv_msgs__srv__detail__uint8__rosidl_typesupport_introspection_c__Uint8_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sdv_msgs, srv, Uint8_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sdv_msgs, srv, Uint8_Response)()->data;
  }

  return &sdv_msgs__srv__detail__uint8__rosidl_typesupport_introspection_c__Uint8_service_type_support_handle;
}
