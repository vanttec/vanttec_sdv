// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sdv_msgs:msg/WaypointVector.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__WAYPOINT_VECTOR__TRAITS_HPP_
#define SDV_MSGS__MSG__DETAIL__WAYPOINT_VECTOR__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sdv_msgs/msg/detail/waypoint_vector__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace sdv_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const WaypointVector & msg,
  std::ostream & out)
{
  out << "{";
  // member: x_list
  {
    if (msg.x_list.size() == 0) {
      out << "x_list: []";
    } else {
      out << "x_list: [";
      size_t pending_items = msg.x_list.size();
      for (auto item : msg.x_list) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: y_list
  {
    if (msg.y_list.size() == 0) {
      out << "y_list: []";
    } else {
      out << "y_list: [";
      size_t pending_items = msg.y_list.size();
      for (auto item : msg.y_list) {
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
  const WaypointVector & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: x_list
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.x_list.size() == 0) {
      out << "x_list: []\n";
    } else {
      out << "x_list:\n";
      for (auto item : msg.x_list) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: y_list
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.y_list.size() == 0) {
      out << "y_list: []\n";
    } else {
      out << "y_list:\n";
      for (auto item : msg.y_list) {
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

inline std::string to_yaml(const WaypointVector & msg, bool use_flow_style = false)
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
  const sdv_msgs::msg::WaypointVector & msg,
  std::ostream & out, size_t indentation = 0)
{
  sdv_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sdv_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const sdv_msgs::msg::WaypointVector & msg)
{
  return sdv_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sdv_msgs::msg::WaypointVector>()
{
  return "sdv_msgs::msg::WaypointVector";
}

template<>
inline const char * name<sdv_msgs::msg::WaypointVector>()
{
  return "sdv_msgs/msg/WaypointVector";
}

template<>
struct has_fixed_size<sdv_msgs::msg::WaypointVector>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<sdv_msgs::msg::WaypointVector>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<sdv_msgs::msg::WaypointVector>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SDV_MSGS__MSG__DETAIL__WAYPOINT_VECTOR__TRAITS_HPP_
