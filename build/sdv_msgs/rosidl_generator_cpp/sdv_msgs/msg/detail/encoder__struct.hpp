// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sdv_msgs:msg/Encoder.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__ENCODER__STRUCT_HPP_
#define SDV_MSGS__MSG__DETAIL__ENCODER__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__sdv_msgs__msg__Encoder __attribute__((deprecated))
#else
# define DEPRECATED__sdv_msgs__msg__Encoder __declspec(deprecated)
#endif

namespace sdv_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Encoder_
{
  using Type = Encoder_<ContainerAllocator>;

  explicit Encoder_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->abs_angle = 0.0f;
      this->angle = 0.0f;
      this->turn = 0;
    }
  }

  explicit Encoder_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->abs_angle = 0.0f;
      this->angle = 0.0f;
      this->turn = 0;
    }
  }

  // field types and members
  using _abs_angle_type =
    float;
  _abs_angle_type abs_angle;
  using _angle_type =
    float;
  _angle_type angle;
  using _turn_type =
    int16_t;
  _turn_type turn;

  // setters for named parameter idiom
  Type & set__abs_angle(
    const float & _arg)
  {
    this->abs_angle = _arg;
    return *this;
  }
  Type & set__angle(
    const float & _arg)
  {
    this->angle = _arg;
    return *this;
  }
  Type & set__turn(
    const int16_t & _arg)
  {
    this->turn = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sdv_msgs::msg::Encoder_<ContainerAllocator> *;
  using ConstRawPtr =
    const sdv_msgs::msg::Encoder_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sdv_msgs::msg::Encoder_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sdv_msgs::msg::Encoder_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sdv_msgs::msg::Encoder_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sdv_msgs::msg::Encoder_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sdv_msgs::msg::Encoder_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sdv_msgs::msg::Encoder_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sdv_msgs::msg::Encoder_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sdv_msgs::msg::Encoder_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sdv_msgs__msg__Encoder
    std::shared_ptr<sdv_msgs::msg::Encoder_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sdv_msgs__msg__Encoder
    std::shared_ptr<sdv_msgs::msg::Encoder_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Encoder_ & other) const
  {
    if (this->abs_angle != other.abs_angle) {
      return false;
    }
    if (this->angle != other.angle) {
      return false;
    }
    if (this->turn != other.turn) {
      return false;
    }
    return true;
  }
  bool operator!=(const Encoder_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Encoder_

// alias to use template instance with default allocator
using Encoder =
  sdv_msgs::msg::Encoder_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__ENCODER__STRUCT_HPP_
