// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sdv_msgs:msg/ThrottleMsg.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__THROTTLE_MSG__STRUCT_HPP_
#define SDV_MSGS__MSG__DETAIL__THROTTLE_MSG__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'maxvel'
// Member 'pot'
#include "std_msgs/msg/detail/float64__struct.hpp"
// Member 'increase_maxvel'
// Member 'decrease_maxvel'
// Member 'car_mode'
// Member 'pot_mode'
#include "std_msgs/msg/detail/int16__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__sdv_msgs__msg__ThrottleMsg __attribute__((deprecated))
#else
# define DEPRECATED__sdv_msgs__msg__ThrottleMsg __declspec(deprecated)
#endif

namespace sdv_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ThrottleMsg_
{
  using Type = ThrottleMsg_<ContainerAllocator>;

  explicit ThrottleMsg_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : maxvel(_init),
    pot(_init),
    increase_maxvel(_init),
    decrease_maxvel(_init),
    car_mode(_init),
    pot_mode(_init)
  {
    (void)_init;
  }

  explicit ThrottleMsg_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : maxvel(_alloc, _init),
    pot(_alloc, _init),
    increase_maxvel(_alloc, _init),
    decrease_maxvel(_alloc, _init),
    car_mode(_alloc, _init),
    pot_mode(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _maxvel_type =
    std_msgs::msg::Float64_<ContainerAllocator>;
  _maxvel_type maxvel;
  using _pot_type =
    std_msgs::msg::Float64_<ContainerAllocator>;
  _pot_type pot;
  using _increase_maxvel_type =
    std_msgs::msg::Int16_<ContainerAllocator>;
  _increase_maxvel_type increase_maxvel;
  using _decrease_maxvel_type =
    std_msgs::msg::Int16_<ContainerAllocator>;
  _decrease_maxvel_type decrease_maxvel;
  using _car_mode_type =
    std_msgs::msg::Int16_<ContainerAllocator>;
  _car_mode_type car_mode;
  using _pot_mode_type =
    std_msgs::msg::Int16_<ContainerAllocator>;
  _pot_mode_type pot_mode;

  // setters for named parameter idiom
  Type & set__maxvel(
    const std_msgs::msg::Float64_<ContainerAllocator> & _arg)
  {
    this->maxvel = _arg;
    return *this;
  }
  Type & set__pot(
    const std_msgs::msg::Float64_<ContainerAllocator> & _arg)
  {
    this->pot = _arg;
    return *this;
  }
  Type & set__increase_maxvel(
    const std_msgs::msg::Int16_<ContainerAllocator> & _arg)
  {
    this->increase_maxvel = _arg;
    return *this;
  }
  Type & set__decrease_maxvel(
    const std_msgs::msg::Int16_<ContainerAllocator> & _arg)
  {
    this->decrease_maxvel = _arg;
    return *this;
  }
  Type & set__car_mode(
    const std_msgs::msg::Int16_<ContainerAllocator> & _arg)
  {
    this->car_mode = _arg;
    return *this;
  }
  Type & set__pot_mode(
    const std_msgs::msg::Int16_<ContainerAllocator> & _arg)
  {
    this->pot_mode = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sdv_msgs::msg::ThrottleMsg_<ContainerAllocator> *;
  using ConstRawPtr =
    const sdv_msgs::msg::ThrottleMsg_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sdv_msgs::msg::ThrottleMsg_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sdv_msgs::msg::ThrottleMsg_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sdv_msgs::msg::ThrottleMsg_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sdv_msgs::msg::ThrottleMsg_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sdv_msgs::msg::ThrottleMsg_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sdv_msgs::msg::ThrottleMsg_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sdv_msgs::msg::ThrottleMsg_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sdv_msgs::msg::ThrottleMsg_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sdv_msgs__msg__ThrottleMsg
    std::shared_ptr<sdv_msgs::msg::ThrottleMsg_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sdv_msgs__msg__ThrottleMsg
    std::shared_ptr<sdv_msgs::msg::ThrottleMsg_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ThrottleMsg_ & other) const
  {
    if (this->maxvel != other.maxvel) {
      return false;
    }
    if (this->pot != other.pot) {
      return false;
    }
    if (this->increase_maxvel != other.increase_maxvel) {
      return false;
    }
    if (this->decrease_maxvel != other.decrease_maxvel) {
      return false;
    }
    if (this->car_mode != other.car_mode) {
      return false;
    }
    if (this->pot_mode != other.pot_mode) {
      return false;
    }
    return true;
  }
  bool operator!=(const ThrottleMsg_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ThrottleMsg_

// alias to use template instance with default allocator
using ThrottleMsg =
  sdv_msgs::msg::ThrottleMsg_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__THROTTLE_MSG__STRUCT_HPP_
