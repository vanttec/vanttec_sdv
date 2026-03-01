// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sdv_msgs:msg/ThrustControl.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__THRUST_CONTROL__TRAITS_HPP_
#define SDV_MSGS__MSG__DETAIL__THRUST_CONTROL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sdv_msgs/msg/detail/thrust_control__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace sdv_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const ThrustControl & msg,
  std::ostream & out)
{
  out << "{";
  // member: tau_x
  {
    out << "tau_x: ";
    rosidl_generator_traits::value_to_yaml(msg.tau_x, out);
    out << ", ";
  }

  // member: tau_y
  {
    out << "tau_y: ";
    rosidl_generator_traits::value_to_yaml(msg.tau_y, out);
    out << ", ";
  }

  // member: tau_z
  {
    out << "tau_z: ";
    rosidl_generator_traits::value_to_yaml(msg.tau_z, out);
    out << ", ";
  }

  // member: tau_phi
  {
    out << "tau_phi: ";
    rosidl_generator_traits::value_to_yaml(msg.tau_phi, out);
    out << ", ";
  }

  // member: tau_theta
  {
    out << "tau_theta: ";
    rosidl_generator_traits::value_to_yaml(msg.tau_theta, out);
    out << ", ";
  }

  // member: tau_psi
  {
    out << "tau_psi: ";
    rosidl_generator_traits::value_to_yaml(msg.tau_psi, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ThrustControl & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: tau_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tau_x: ";
    rosidl_generator_traits::value_to_yaml(msg.tau_x, out);
    out << "\n";
  }

  // member: tau_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tau_y: ";
    rosidl_generator_traits::value_to_yaml(msg.tau_y, out);
    out << "\n";
  }

  // member: tau_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tau_z: ";
    rosidl_generator_traits::value_to_yaml(msg.tau_z, out);
    out << "\n";
  }

  // member: tau_phi
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tau_phi: ";
    rosidl_generator_traits::value_to_yaml(msg.tau_phi, out);
    out << "\n";
  }

  // member: tau_theta
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tau_theta: ";
    rosidl_generator_traits::value_to_yaml(msg.tau_theta, out);
    out << "\n";
  }

  // member: tau_psi
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tau_psi: ";
    rosidl_generator_traits::value_to_yaml(msg.tau_psi, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ThrustControl & msg, bool use_flow_style = false)
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
  const sdv_msgs::msg::ThrustControl & msg,
  std::ostream & out, size_t indentation = 0)
{
  sdv_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sdv_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const sdv_msgs::msg::ThrustControl & msg)
{
  return sdv_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sdv_msgs::msg::ThrustControl>()
{
  return "sdv_msgs::msg::ThrustControl";
}

template<>
inline const char * name<sdv_msgs::msg::ThrustControl>()
{
  return "sdv_msgs/msg/ThrustControl";
}

template<>
struct has_fixed_size<sdv_msgs::msg::ThrustControl>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<sdv_msgs::msg::ThrustControl>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<sdv_msgs::msg::ThrustControl>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SDV_MSGS__MSG__DETAIL__THRUST_CONTROL__TRAITS_HPP_
