// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sdv_msgs:msg/GuidanceWaypoints.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__GUIDANCE_WAYPOINTS__STRUCT_HPP_
#define SDV_MSGS__MSG__DETAIL__GUIDANCE_WAYPOINTS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__sdv_msgs__msg__GuidanceWaypoints __attribute__((deprecated))
#else
# define DEPRECATED__sdv_msgs__msg__GuidanceWaypoints __declspec(deprecated)
#endif

namespace sdv_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct GuidanceWaypoints_
{
  using Type = GuidanceWaypoints_<ContainerAllocator>;

  explicit GuidanceWaypoints_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->guidance_law = 0;
      this->waypoint_list_length = 0;
      this->depth_setpoint = 0.0f;
      this->heading_setpoint = 0.0f;
    }
  }

  explicit GuidanceWaypoints_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->guidance_law = 0;
      this->waypoint_list_length = 0;
      this->depth_setpoint = 0.0f;
      this->heading_setpoint = 0.0f;
    }
  }

  // field types and members
  using _guidance_law_type =
    uint8_t;
  _guidance_law_type guidance_law;
  using _waypoint_list_length_type =
    uint8_t;
  _waypoint_list_length_type waypoint_list_length;
  using _waypoint_list_x_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _waypoint_list_x_type waypoint_list_x;
  using _waypoint_list_y_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _waypoint_list_y_type waypoint_list_y;
  using _waypoint_list_z_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _waypoint_list_z_type waypoint_list_z;
  using _depth_setpoint_type =
    float;
  _depth_setpoint_type depth_setpoint;
  using _heading_setpoint_type =
    float;
  _heading_setpoint_type heading_setpoint;

  // setters for named parameter idiom
  Type & set__guidance_law(
    const uint8_t & _arg)
  {
    this->guidance_law = _arg;
    return *this;
  }
  Type & set__waypoint_list_length(
    const uint8_t & _arg)
  {
    this->waypoint_list_length = _arg;
    return *this;
  }
  Type & set__waypoint_list_x(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->waypoint_list_x = _arg;
    return *this;
  }
  Type & set__waypoint_list_y(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->waypoint_list_y = _arg;
    return *this;
  }
  Type & set__waypoint_list_z(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->waypoint_list_z = _arg;
    return *this;
  }
  Type & set__depth_setpoint(
    const float & _arg)
  {
    this->depth_setpoint = _arg;
    return *this;
  }
  Type & set__heading_setpoint(
    const float & _arg)
  {
    this->heading_setpoint = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sdv_msgs::msg::GuidanceWaypoints_<ContainerAllocator> *;
  using ConstRawPtr =
    const sdv_msgs::msg::GuidanceWaypoints_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sdv_msgs::msg::GuidanceWaypoints_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sdv_msgs::msg::GuidanceWaypoints_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sdv_msgs::msg::GuidanceWaypoints_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sdv_msgs::msg::GuidanceWaypoints_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sdv_msgs::msg::GuidanceWaypoints_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sdv_msgs::msg::GuidanceWaypoints_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sdv_msgs::msg::GuidanceWaypoints_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sdv_msgs::msg::GuidanceWaypoints_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sdv_msgs__msg__GuidanceWaypoints
    std::shared_ptr<sdv_msgs::msg::GuidanceWaypoints_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sdv_msgs__msg__GuidanceWaypoints
    std::shared_ptr<sdv_msgs::msg::GuidanceWaypoints_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GuidanceWaypoints_ & other) const
  {
    if (this->guidance_law != other.guidance_law) {
      return false;
    }
    if (this->waypoint_list_length != other.waypoint_list_length) {
      return false;
    }
    if (this->waypoint_list_x != other.waypoint_list_x) {
      return false;
    }
    if (this->waypoint_list_y != other.waypoint_list_y) {
      return false;
    }
    if (this->waypoint_list_z != other.waypoint_list_z) {
      return false;
    }
    if (this->depth_setpoint != other.depth_setpoint) {
      return false;
    }
    if (this->heading_setpoint != other.heading_setpoint) {
      return false;
    }
    return true;
  }
  bool operator!=(const GuidanceWaypoints_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GuidanceWaypoints_

// alias to use template instance with default allocator
using GuidanceWaypoints =
  sdv_msgs::msg::GuidanceWaypoints_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__GUIDANCE_WAYPOINTS__STRUCT_HPP_
