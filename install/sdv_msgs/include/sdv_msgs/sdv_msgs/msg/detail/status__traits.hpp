// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sdv_msgs:msg/Status.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__STATUS__TRAITS_HPP_
#define SDV_MSGS__MSG__DETAIL__STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sdv_msgs/msg/detail/status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace sdv_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Status & msg,
  std::ostream & out)
{
  out << "{";
  // member: frame
  {
    out << "frame: ";
    rosidl_generator_traits::value_to_yaml(msg.frame, out);
    out << ", ";
  }

  // member: fixed_delta_seconds
  {
    out << "fixed_delta_seconds: ";
    rosidl_generator_traits::value_to_yaml(msg.fixed_delta_seconds, out);
    out << ", ";
  }

  // member: synchronous_mode
  {
    out << "synchronous_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.synchronous_mode, out);
    out << ", ";
  }

  // member: synchronous_mode_running
  {
    out << "synchronous_mode_running: ";
    rosidl_generator_traits::value_to_yaml(msg.synchronous_mode_running, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Status & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: frame
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "frame: ";
    rosidl_generator_traits::value_to_yaml(msg.frame, out);
    out << "\n";
  }

  // member: fixed_delta_seconds
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fixed_delta_seconds: ";
    rosidl_generator_traits::value_to_yaml(msg.fixed_delta_seconds, out);
    out << "\n";
  }

  // member: synchronous_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "synchronous_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.synchronous_mode, out);
    out << "\n";
  }

  // member: synchronous_mode_running
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "synchronous_mode_running: ";
    rosidl_generator_traits::value_to_yaml(msg.synchronous_mode_running, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Status & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace sdv_msgs

namespace rosidl_generator_traits
{

[[deprecated("use sdv_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const sdv_msgs::msg::Status & msg,
  std::ostream & out, size_t indentation = 0)
{
  sdv_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sdv_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const sdv_msgs::msg::Status & msg)
{
  return sdv_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sdv_msgs::msg::Status>()
{
  return "sdv_msgs::msg::Status";
}

template<>
inline const char * name<sdv_msgs::msg::Status>()
{
  return "sdv_msgs/msg/Status";
}

template<>
struct has_fixed_size<sdv_msgs::msg::Status>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<sdv_msgs::msg::Status>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<sdv_msgs::msg::Status>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SDV_MSGS__MSG__DETAIL__STATUS__TRAITS_HPP_
