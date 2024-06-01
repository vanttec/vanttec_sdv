// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sdv_msgs:msg/XboxMsg.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__XBOX_MSG__TRAITS_HPP_
#define SDV_MSGS__MSG__DETAIL__XBOX_MSG__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sdv_msgs/msg/detail/xbox_msg__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'connected'
#include "std_msgs/msg/detail/bool__traits.hpp"
// Member 'back'
// Member 'a'
// Member 'b'
// Member 'x'
// Member 'y'
// Member 'dpad_up'
// Member 'dpad_down'
// Member 'dpad_left'
// Member 'dpad_right'
#include "std_msgs/msg/detail/int16__traits.hpp"
// Member 'leftx'
// Member 'lefty'
// Member 'right_trigger'
#include "std_msgs/msg/detail/float64__traits.hpp"

namespace sdv_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const XboxMsg & msg,
  std::ostream & out)
{
  out << "{";
  // member: connected
  {
    out << "connected: ";
    to_flow_style_yaml(msg.connected, out);
    out << ", ";
  }

  // member: back
  {
    out << "back: ";
    to_flow_style_yaml(msg.back, out);
    out << ", ";
  }

  // member: leftx
  {
    out << "leftx: ";
    to_flow_style_yaml(msg.leftx, out);
    out << ", ";
  }

  // member: lefty
  {
    out << "lefty: ";
    to_flow_style_yaml(msg.lefty, out);
    out << ", ";
  }

  // member: right_trigger
  {
    out << "right_trigger: ";
    to_flow_style_yaml(msg.right_trigger, out);
    out << ", ";
  }

  // member: a
  {
    out << "a: ";
    to_flow_style_yaml(msg.a, out);
    out << ", ";
  }

  // member: b
  {
    out << "b: ";
    to_flow_style_yaml(msg.b, out);
    out << ", ";
  }

  // member: x
  {
    out << "x: ";
    to_flow_style_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    to_flow_style_yaml(msg.y, out);
    out << ", ";
  }

  // member: dpad_up
  {
    out << "dpad_up: ";
    to_flow_style_yaml(msg.dpad_up, out);
    out << ", ";
  }

  // member: dpad_down
  {
    out << "dpad_down: ";
    to_flow_style_yaml(msg.dpad_down, out);
    out << ", ";
  }

  // member: dpad_left
  {
    out << "dpad_left: ";
    to_flow_style_yaml(msg.dpad_left, out);
    out << ", ";
  }

  // member: dpad_right
  {
    out << "dpad_right: ";
    to_flow_style_yaml(msg.dpad_right, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const XboxMsg & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: connected
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "connected:\n";
    to_block_style_yaml(msg.connected, out, indentation + 2);
  }

  // member: back
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "back:\n";
    to_block_style_yaml(msg.back, out, indentation + 2);
  }

  // member: leftx
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "leftx:\n";
    to_block_style_yaml(msg.leftx, out, indentation + 2);
  }

  // member: lefty
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lefty:\n";
    to_block_style_yaml(msg.lefty, out, indentation + 2);
  }

  // member: right_trigger
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "right_trigger:\n";
    to_block_style_yaml(msg.right_trigger, out, indentation + 2);
  }

  // member: a
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "a:\n";
    to_block_style_yaml(msg.a, out, indentation + 2);
  }

  // member: b
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "b:\n";
    to_block_style_yaml(msg.b, out, indentation + 2);
  }

  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x:\n";
    to_block_style_yaml(msg.x, out, indentation + 2);
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y:\n";
    to_block_style_yaml(msg.y, out, indentation + 2);
  }

  // member: dpad_up
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dpad_up:\n";
    to_block_style_yaml(msg.dpad_up, out, indentation + 2);
  }

  // member: dpad_down
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dpad_down:\n";
    to_block_style_yaml(msg.dpad_down, out, indentation + 2);
  }

  // member: dpad_left
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dpad_left:\n";
    to_block_style_yaml(msg.dpad_left, out, indentation + 2);
  }

  // member: dpad_right
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dpad_right:\n";
    to_block_style_yaml(msg.dpad_right, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const XboxMsg & msg, bool use_flow_style = false)
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
  const sdv_msgs::msg::XboxMsg & msg,
  std::ostream & out, size_t indentation = 0)
{
  sdv_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sdv_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const sdv_msgs::msg::XboxMsg & msg)
{
  return sdv_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sdv_msgs::msg::XboxMsg>()
{
  return "sdv_msgs::msg::XboxMsg";
}

template<>
inline const char * name<sdv_msgs::msg::XboxMsg>()
{
  return "sdv_msgs/msg/XboxMsg";
}

template<>
struct has_fixed_size<sdv_msgs::msg::XboxMsg>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Bool>::value && has_fixed_size<std_msgs::msg::Float64>::value && has_fixed_size<std_msgs::msg::Int16>::value> {};

template<>
struct has_bounded_size<sdv_msgs::msg::XboxMsg>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Bool>::value && has_bounded_size<std_msgs::msg::Float64>::value && has_bounded_size<std_msgs::msg::Int16>::value> {};

template<>
struct is_message<sdv_msgs::msg::XboxMsg>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SDV_MSGS__MSG__DETAIL__XBOX_MSG__TRAITS_HPP_
