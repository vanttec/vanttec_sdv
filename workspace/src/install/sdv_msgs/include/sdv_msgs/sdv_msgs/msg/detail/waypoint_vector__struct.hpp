// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sdv_msgs:msg/WaypointVector.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__WAYPOINT_VECTOR__STRUCT_HPP_
#define SDV_MSGS__MSG__DETAIL__WAYPOINT_VECTOR__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__sdv_msgs__msg__WaypointVector __attribute__((deprecated))
#else
# define DEPRECATED__sdv_msgs__msg__WaypointVector __declspec(deprecated)
#endif

namespace sdv_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct WaypointVector_
{
  using Type = WaypointVector_<ContainerAllocator>;

  explicit WaypointVector_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit WaypointVector_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _x_list_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _x_list_type x_list;
  using _y_list_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _y_list_type y_list;

  // setters for named parameter idiom
  Type & set__x_list(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->x_list = _arg;
    return *this;
  }
  Type & set__y_list(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->y_list = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sdv_msgs::msg::WaypointVector_<ContainerAllocator> *;
  using ConstRawPtr =
    const sdv_msgs::msg::WaypointVector_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sdv_msgs::msg::WaypointVector_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sdv_msgs::msg::WaypointVector_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sdv_msgs::msg::WaypointVector_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sdv_msgs::msg::WaypointVector_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sdv_msgs::msg::WaypointVector_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sdv_msgs::msg::WaypointVector_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sdv_msgs::msg::WaypointVector_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sdv_msgs::msg::WaypointVector_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sdv_msgs__msg__WaypointVector
    std::shared_ptr<sdv_msgs::msg::WaypointVector_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sdv_msgs__msg__WaypointVector
    std::shared_ptr<sdv_msgs::msg::WaypointVector_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const WaypointVector_ & other) const
  {
    if (this->x_list != other.x_list) {
      return false;
    }
    if (this->y_list != other.y_list) {
      return false;
    }
    return true;
  }
  bool operator!=(const WaypointVector_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct WaypointVector_

// alias to use template instance with default allocator
using WaypointVector =
  sdv_msgs::msg::WaypointVector_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__WAYPOINT_VECTOR__STRUCT_HPP_
