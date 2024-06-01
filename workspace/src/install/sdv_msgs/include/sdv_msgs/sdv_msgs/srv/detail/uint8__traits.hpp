// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sdv_msgs:srv/Uint8.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__SRV__DETAIL__UINT8__TRAITS_HPP_
#define SDV_MSGS__SRV__DETAIL__UINT8__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sdv_msgs/srv/detail/uint8__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace sdv_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const Uint8_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: data
  {
    out << "data: ";
    rosidl_generator_traits::value_to_yaml(msg.data, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Uint8_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "data: ";
    rosidl_generator_traits::value_to_yaml(msg.data, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Uint8_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace sdv_msgs

namespace rosidl_generator_traits
{

[[deprecated("use sdv_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const sdv_msgs::srv::Uint8_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  sdv_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sdv_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const sdv_msgs::srv::Uint8_Request & msg)
{
  return sdv_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<sdv_msgs::srv::Uint8_Request>()
{
  return "sdv_msgs::srv::Uint8_Request";
}

template<>
inline const char * name<sdv_msgs::srv::Uint8_Request>()
{
  return "sdv_msgs/srv/Uint8_Request";
}

template<>
struct has_fixed_size<sdv_msgs::srv::Uint8_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<sdv_msgs::srv::Uint8_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<sdv_msgs::srv::Uint8_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace sdv_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const Uint8_Response & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Uint8_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Uint8_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace sdv_msgs

namespace rosidl_generator_traits
{

[[deprecated("use sdv_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const sdv_msgs::srv::Uint8_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  sdv_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sdv_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const sdv_msgs::srv::Uint8_Response & msg)
{
  return sdv_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<sdv_msgs::srv::Uint8_Response>()
{
  return "sdv_msgs::srv::Uint8_Response";
}

template<>
inline const char * name<sdv_msgs::srv::Uint8_Response>()
{
  return "sdv_msgs/srv/Uint8_Response";
}

template<>
struct has_fixed_size<sdv_msgs::srv::Uint8_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<sdv_msgs::srv::Uint8_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<sdv_msgs::srv::Uint8_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<sdv_msgs::srv::Uint8>()
{
  return "sdv_msgs::srv::Uint8";
}

template<>
inline const char * name<sdv_msgs::srv::Uint8>()
{
  return "sdv_msgs/srv/Uint8";
}

template<>
struct has_fixed_size<sdv_msgs::srv::Uint8>
  : std::integral_constant<
    bool,
    has_fixed_size<sdv_msgs::srv::Uint8_Request>::value &&
    has_fixed_size<sdv_msgs::srv::Uint8_Response>::value
  >
{
};

template<>
struct has_bounded_size<sdv_msgs::srv::Uint8>
  : std::integral_constant<
    bool,
    has_bounded_size<sdv_msgs::srv::Uint8_Request>::value &&
    has_bounded_size<sdv_msgs::srv::Uint8_Response>::value
  >
{
};

template<>
struct is_service<sdv_msgs::srv::Uint8>
  : std::true_type
{
};

template<>
struct is_service_request<sdv_msgs::srv::Uint8_Request>
  : std::true_type
{
};

template<>
struct is_service_response<sdv_msgs::srv::Uint8_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // SDV_MSGS__SRV__DETAIL__UINT8__TRAITS_HPP_
