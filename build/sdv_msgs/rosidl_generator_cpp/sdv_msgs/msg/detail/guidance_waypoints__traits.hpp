// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sdv_msgs:msg/GuidanceWaypoints.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__GUIDANCE_WAYPOINTS__TRAITS_HPP_
#define SDV_MSGS__MSG__DETAIL__GUIDANCE_WAYPOINTS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sdv_msgs/msg/detail/guidance_waypoints__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace sdv_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const GuidanceWaypoints & msg,
  std::ostream & out)
{
  out << "{";
  // member: guidance_law
  {
    out << "guidance_law: ";
    rosidl_generator_traits::value_to_yaml(msg.guidance_law, out);
    out << ", ";
  }

  // member: waypoint_list_length
  {
    out << "waypoint_list_length: ";
    rosidl_generator_traits::value_to_yaml(msg.waypoint_list_length, out);
    out << ", ";
  }

  // member: waypoint_list_x
  {
    if (msg.waypoint_list_x.size() == 0) {
      out << "waypoint_list_x: []";
    } else {
      out << "waypoint_list_x: [";
      size_t pending_items = msg.waypoint_list_x.size();
      for (auto item : msg.waypoint_list_x) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: waypoint_list_y
  {
    if (msg.waypoint_list_y.size() == 0) {
      out << "waypoint_list_y: []";
    } else {
      out << "waypoint_list_y: [";
      size_t pending_items = msg.waypoint_list_y.size();
      for (auto item : msg.waypoint_list_y) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: waypoint_list_z
  {
    if (msg.waypoint_list_z.size() == 0) {
      out << "waypoint_list_z: []";
    } else {
      out << "waypoint_list_z: [";
      size_t pending_items = msg.waypoint_list_z.size();
      for (auto item : msg.waypoint_list_z) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: depth_setpoint
  {
    out << "depth_setpoint: ";
    rosidl_generator_traits::value_to_yaml(msg.depth_setpoint, out);
    out << ", ";
  }

  // member: heading_setpoint
  {
    out << "heading_setpoint: ";
    rosidl_generator_traits::value_to_yaml(msg.heading_setpoint, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GuidanceWaypoints & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: guidance_law
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "guidance_law: ";
    rosidl_generator_traits::value_to_yaml(msg.guidance_law, out);
    out << "\n";
  }

  // member: waypoint_list_length
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "waypoint_list_length: ";
    rosidl_generator_traits::value_to_yaml(msg.waypoint_list_length, out);
    out << "\n";
  }

  // member: waypoint_list_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.waypoint_list_x.size() == 0) {
      out << "waypoint_list_x: []\n";
    } else {
      out << "waypoint_list_x:\n";
      for (auto item : msg.waypoint_list_x) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: waypoint_list_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.waypoint_list_y.size() == 0) {
      out << "waypoint_list_y: []\n";
    } else {
      out << "waypoint_list_y:\n";
      for (auto item : msg.waypoint_list_y) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: waypoint_list_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.waypoint_list_z.size() == 0) {
      out << "waypoint_list_z: []\n";
    } else {
      out << "waypoint_list_z:\n";
      for (auto item : msg.waypoint_list_z) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: depth_setpoint
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "depth_setpoint: ";
    rosidl_generator_traits::value_to_yaml(msg.depth_setpoint, out);
    out << "\n";
  }

  // member: heading_setpoint
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "heading_setpoint: ";
    rosidl_generator_traits::value_to_yaml(msg.heading_setpoint, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GuidanceWaypoints & msg, bool use_flow_style = false)
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
  const sdv_msgs::msg::GuidanceWaypoints & msg,
  std::ostream & out, size_t indentation = 0)
{
  sdv_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sdv_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const sdv_msgs::msg::GuidanceWaypoints & msg)
{
  return sdv_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sdv_msgs::msg::GuidanceWaypoints>()
{
  return "sdv_msgs::msg::GuidanceWaypoints";
}

template<>
inline const char * name<sdv_msgs::msg::GuidanceWaypoints>()
{
  return "sdv_msgs/msg/GuidanceWaypoints";
}

template<>
struct has_fixed_size<sdv_msgs::msg::GuidanceWaypoints>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<sdv_msgs::msg::GuidanceWaypoints>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<sdv_msgs::msg::GuidanceWaypoints>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SDV_MSGS__MSG__DETAIL__GUIDANCE_WAYPOINTS__TRAITS_HPP_
