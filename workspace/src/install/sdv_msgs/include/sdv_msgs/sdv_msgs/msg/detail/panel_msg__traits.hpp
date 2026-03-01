// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sdv_msgs:msg/PanelMsg.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__PANEL_MSG__TRAITS_HPP_
#define SDV_MSGS__MSG__DETAIL__PANEL_MSG__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sdv_msgs/msg/detail/panel_msg__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'wiper'
// Member 'horn'
// Member 'right_upper_front_light'
// Member 'left_upper_front_light'
// Member 'right_down_front_light'
// Member 'left_down_front_light'
// Member 'back'
#include "std_msgs/msg/detail/bool__traits.hpp"
// Member 'xboxcontrol'
#include "std_msgs/msg/detail/byte_multi_array__traits.hpp"

namespace sdv_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const PanelMsg & msg,
  std::ostream & out)
{
  out << "{";
  // member: wiper
  {
    out << "wiper: ";
    to_flow_style_yaml(msg.wiper, out);
    out << ", ";
  }

  // member: horn
  {
    out << "horn: ";
    to_flow_style_yaml(msg.horn, out);
    out << ", ";
  }

  // member: right_upper_front_light
  {
    out << "right_upper_front_light: ";
    to_flow_style_yaml(msg.right_upper_front_light, out);
    out << ", ";
  }

  // member: left_upper_front_light
  {
    out << "left_upper_front_light: ";
    to_flow_style_yaml(msg.left_upper_front_light, out);
    out << ", ";
  }

  // member: right_down_front_light
  {
    out << "right_down_front_light: ";
    to_flow_style_yaml(msg.right_down_front_light, out);
    out << ", ";
  }

  // member: left_down_front_light
  {
    out << "left_down_front_light: ";
    to_flow_style_yaml(msg.left_down_front_light, out);
    out << ", ";
  }

  // member: back
  {
    out << "back: ";
    to_flow_style_yaml(msg.back, out);
    out << ", ";
  }

  // member: xboxcontrol
  {
    out << "xboxcontrol: ";
    to_flow_style_yaml(msg.xboxcontrol, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PanelMsg & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: wiper
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "wiper:\n";
    to_block_style_yaml(msg.wiper, out, indentation + 2);
  }

  // member: horn
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "horn:\n";
    to_block_style_yaml(msg.horn, out, indentation + 2);
  }

  // member: right_upper_front_light
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "right_upper_front_light:\n";
    to_block_style_yaml(msg.right_upper_front_light, out, indentation + 2);
  }

  // member: left_upper_front_light
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "left_upper_front_light:\n";
    to_block_style_yaml(msg.left_upper_front_light, out, indentation + 2);
  }

  // member: right_down_front_light
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "right_down_front_light:\n";
    to_block_style_yaml(msg.right_down_front_light, out, indentation + 2);
  }

  // member: left_down_front_light
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "left_down_front_light:\n";
    to_block_style_yaml(msg.left_down_front_light, out, indentation + 2);
  }

  // member: back
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "back:\n";
    to_block_style_yaml(msg.back, out, indentation + 2);
  }

  // member: xboxcontrol
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "xboxcontrol:\n";
    to_block_style_yaml(msg.xboxcontrol, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PanelMsg & msg, bool use_flow_style = false)
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
  const sdv_msgs::msg::PanelMsg & msg,
  std::ostream & out, size_t indentation = 0)
{
  sdv_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sdv_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const sdv_msgs::msg::PanelMsg & msg)
{
  return sdv_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sdv_msgs::msg::PanelMsg>()
{
  return "sdv_msgs::msg::PanelMsg";
}

template<>
inline const char * name<sdv_msgs::msg::PanelMsg>()
{
  return "sdv_msgs/msg/PanelMsg";
}

template<>
struct has_fixed_size<sdv_msgs::msg::PanelMsg>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Bool>::value && has_fixed_size<std_msgs::msg::ByteMultiArray>::value> {};

template<>
struct has_bounded_size<sdv_msgs::msg::PanelMsg>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Bool>::value && has_bounded_size<std_msgs::msg::ByteMultiArray>::value> {};

template<>
struct is_message<sdv_msgs::msg::PanelMsg>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SDV_MSGS__MSG__DETAIL__PANEL_MSG__TRAITS_HPP_
