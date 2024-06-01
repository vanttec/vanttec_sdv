// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sdv_msgs:msg/SystemDynamics.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__SYSTEM_DYNAMICS__TRAITS_HPP_
#define SDV_MSGS__MSG__DETAIL__SYSTEM_DYNAMICS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sdv_msgs/msg/detail/system_dynamics__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'g'
#include "std_msgs/msg/detail/float32_multi_array__traits.hpp"

namespace sdv_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const SystemDynamics & msg,
  std::ostream & out)
{
  out << "{";
  // member: g
  {
    out << "g: ";
    to_flow_style_yaml(msg.g, out);
    out << ", ";
  }

  // member: f
  {
    if (msg.f.size() == 0) {
      out << "f: []";
    } else {
      out << "f: [";
      size_t pending_items = msg.f.size();
      for (auto item : msg.f) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SystemDynamics & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: g
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "g:\n";
    to_block_style_yaml(msg.g, out, indentation + 2);
  }

  // member: f
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.f.size() == 0) {
      out << "f: []\n";
    } else {
      out << "f:\n";
      for (auto item : msg.f) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SystemDynamics & msg, bool use_flow_style = false)
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
  const sdv_msgs::msg::SystemDynamics & msg,
  std::ostream & out, size_t indentation = 0)
{
  sdv_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sdv_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const sdv_msgs::msg::SystemDynamics & msg)
{
  return sdv_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sdv_msgs::msg::SystemDynamics>()
{
  return "sdv_msgs::msg::SystemDynamics";
}

template<>
inline const char * name<sdv_msgs::msg::SystemDynamics>()
{
  return "sdv_msgs/msg/SystemDynamics";
}

template<>
struct has_fixed_size<sdv_msgs::msg::SystemDynamics>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<sdv_msgs::msg::SystemDynamics>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<sdv_msgs::msg::SystemDynamics>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SDV_MSGS__MSG__DETAIL__SYSTEM_DYNAMICS__TRAITS_HPP_
