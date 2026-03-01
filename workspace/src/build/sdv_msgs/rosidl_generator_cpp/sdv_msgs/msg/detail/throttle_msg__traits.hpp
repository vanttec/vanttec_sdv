// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sdv_msgs:msg/ThrottleMsg.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__THROTTLE_MSG__TRAITS_HPP_
#define SDV_MSGS__MSG__DETAIL__THROTTLE_MSG__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sdv_msgs/msg/detail/throttle_msg__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'maxvel'
// Member 'pot'
#include "std_msgs/msg/detail/float64__traits.hpp"
// Member 'increase_maxvel'
// Member 'decrease_maxvel'
// Member 'car_mode'
// Member 'pot_mode'
#include "std_msgs/msg/detail/int16__traits.hpp"

namespace sdv_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const ThrottleMsg & msg,
  std::ostream & out)
{
  out << "{";
  // member: maxvel
  {
    out << "maxvel: ";
    to_flow_style_yaml(msg.maxvel, out);
    out << ", ";
  }

  // member: pot
  {
    out << "pot: ";
    to_flow_style_yaml(msg.pot, out);
    out << ", ";
  }

  // member: increase_maxvel
  {
    out << "increase_maxvel: ";
    to_flow_style_yaml(msg.increase_maxvel, out);
    out << ", ";
  }

  // member: decrease_maxvel
  {
    out << "decrease_maxvel: ";
    to_flow_style_yaml(msg.decrease_maxvel, out);
    out << ", ";
  }

  // member: car_mode
  {
    out << "car_mode: ";
    to_flow_style_yaml(msg.car_mode, out);
    out << ", ";
  }

  // member: pot_mode
  {
    out << "pot_mode: ";
    to_flow_style_yaml(msg.pot_mode, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ThrottleMsg & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: maxvel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "maxvel:\n";
    to_block_style_yaml(msg.maxvel, out, indentation + 2);
  }

  // member: pot
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pot:\n";
    to_block_style_yaml(msg.pot, out, indentation + 2);
  }

  // member: increase_maxvel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "increase_maxvel:\n";
    to_block_style_yaml(msg.increase_maxvel, out, indentation + 2);
  }

  // member: decrease_maxvel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "decrease_maxvel:\n";
    to_block_style_yaml(msg.decrease_maxvel, out, indentation + 2);
  }

  // member: car_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "car_mode:\n";
    to_block_style_yaml(msg.car_mode, out, indentation + 2);
  }

  // member: pot_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pot_mode:\n";
    to_block_style_yaml(msg.pot_mode, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ThrottleMsg & msg, bool use_flow_style = false)
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
  const sdv_msgs::msg::ThrottleMsg & msg,
  std::ostream & out, size_t indentation = 0)
{
  sdv_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sdv_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const sdv_msgs::msg::ThrottleMsg & msg)
{
  return sdv_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sdv_msgs::msg::ThrottleMsg>()
{
  return "sdv_msgs::msg::ThrottleMsg";
}

template<>
inline const char * name<sdv_msgs::msg::ThrottleMsg>()
{
  return "sdv_msgs/msg/ThrottleMsg";
}

template<>
struct has_fixed_size<sdv_msgs::msg::ThrottleMsg>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Float64>::value && has_fixed_size<std_msgs::msg::Int16>::value> {};

template<>
struct has_bounded_size<sdv_msgs::msg::ThrottleMsg>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Float64>::value && has_bounded_size<std_msgs::msg::Int16>::value> {};

template<>
struct is_message<sdv_msgs::msg::ThrottleMsg>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SDV_MSGS__MSG__DETAIL__THROTTLE_MSG__TRAITS_HPP_
