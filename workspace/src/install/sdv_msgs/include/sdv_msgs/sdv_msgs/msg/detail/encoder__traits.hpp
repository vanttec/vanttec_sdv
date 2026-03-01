// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sdv_msgs:msg/Encoder.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__ENCODER__TRAITS_HPP_
#define SDV_MSGS__MSG__DETAIL__ENCODER__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sdv_msgs/msg/detail/encoder__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace sdv_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Encoder & msg,
  std::ostream & out)
{
  out << "{";
  // member: abs_angle
  {
    out << "abs_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.abs_angle, out);
    out << ", ";
  }

  // member: angle
  {
    out << "angle: ";
    rosidl_generator_traits::value_to_yaml(msg.angle, out);
    out << ", ";
  }

  // member: turn
  {
    out << "turn: ";
    rosidl_generator_traits::value_to_yaml(msg.turn, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Encoder & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: abs_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "abs_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.abs_angle, out);
    out << "\n";
  }

  // member: angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "angle: ";
    rosidl_generator_traits::value_to_yaml(msg.angle, out);
    out << "\n";
  }

  // member: turn
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "turn: ";
    rosidl_generator_traits::value_to_yaml(msg.turn, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Encoder & msg, bool use_flow_style = false)
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
  const sdv_msgs::msg::Encoder & msg,
  std::ostream & out, size_t indentation = 0)
{
  sdv_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sdv_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const sdv_msgs::msg::Encoder & msg)
{
  return sdv_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sdv_msgs::msg::Encoder>()
{
  return "sdv_msgs::msg::Encoder";
}

template<>
inline const char * name<sdv_msgs::msg::Encoder>()
{
  return "sdv_msgs/msg/Encoder";
}

template<>
struct has_fixed_size<sdv_msgs::msg::Encoder>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<sdv_msgs::msg::Encoder>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<sdv_msgs::msg::Encoder>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SDV_MSGS__MSG__DETAIL__ENCODER__TRAITS_HPP_
