// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sdv_msgs:msg/LaneInvasionEvent.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__LANE_INVASION_EVENT__STRUCT_HPP_
#define SDV_MSGS__MSG__DETAIL__LANE_INVASION_EVENT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__sdv_msgs__msg__LaneInvasionEvent __attribute__((deprecated))
#else
# define DEPRECATED__sdv_msgs__msg__LaneInvasionEvent __declspec(deprecated)
#endif

namespace sdv_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LaneInvasionEvent_
{
  using Type = LaneInvasionEvent_<ContainerAllocator>;

  explicit LaneInvasionEvent_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    (void)_init;
  }

  explicit LaneInvasionEvent_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _crossed_lane_markings_type =
    std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>>;
  _crossed_lane_markings_type crossed_lane_markings;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__crossed_lane_markings(
    const std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>> & _arg)
  {
    this->crossed_lane_markings = _arg;
    return *this;
  }

  // constant declarations
  static constexpr int32_t LANE_MARKING_OTHER =
    0;
  static constexpr int32_t LANE_MARKING_BROKEN =
    1;
  static constexpr int32_t LANE_MARKING_SOLID =
    2;

  // pointer types
  using RawPtr =
    sdv_msgs::msg::LaneInvasionEvent_<ContainerAllocator> *;
  using ConstRawPtr =
    const sdv_msgs::msg::LaneInvasionEvent_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sdv_msgs::msg::LaneInvasionEvent_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sdv_msgs::msg::LaneInvasionEvent_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sdv_msgs::msg::LaneInvasionEvent_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sdv_msgs::msg::LaneInvasionEvent_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sdv_msgs::msg::LaneInvasionEvent_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sdv_msgs::msg::LaneInvasionEvent_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sdv_msgs::msg::LaneInvasionEvent_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sdv_msgs::msg::LaneInvasionEvent_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sdv_msgs__msg__LaneInvasionEvent
    std::shared_ptr<sdv_msgs::msg::LaneInvasionEvent_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sdv_msgs__msg__LaneInvasionEvent
    std::shared_ptr<sdv_msgs::msg::LaneInvasionEvent_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LaneInvasionEvent_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->crossed_lane_markings != other.crossed_lane_markings) {
      return false;
    }
    return true;
  }
  bool operator!=(const LaneInvasionEvent_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LaneInvasionEvent_

// alias to use template instance with default allocator
using LaneInvasionEvent =
  sdv_msgs::msg::LaneInvasionEvent_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t LaneInvasionEvent_<ContainerAllocator>::LANE_MARKING_OTHER;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t LaneInvasionEvent_<ContainerAllocator>::LANE_MARKING_BROKEN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t LaneInvasionEvent_<ContainerAllocator>::LANE_MARKING_SOLID;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__LANE_INVASION_EVENT__STRUCT_HPP_
