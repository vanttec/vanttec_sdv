// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sdv_msgs:msg/XboxMsg.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__XBOX_MSG__STRUCT_HPP_
#define SDV_MSGS__MSG__DETAIL__XBOX_MSG__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'connected'
#include "std_msgs/msg/detail/bool__struct.hpp"
// Member 'back'
// Member 'a'
// Member 'b'
// Member 'x'
// Member 'y'
// Member 'dpad_up'
// Member 'dpad_down'
// Member 'dpad_left'
// Member 'dpad_right'
#include "std_msgs/msg/detail/int16__struct.hpp"
// Member 'leftx'
// Member 'lefty'
// Member 'right_trigger'
#include "std_msgs/msg/detail/float64__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__sdv_msgs__msg__XboxMsg __attribute__((deprecated))
#else
# define DEPRECATED__sdv_msgs__msg__XboxMsg __declspec(deprecated)
#endif

namespace sdv_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct XboxMsg_
{
  using Type = XboxMsg_<ContainerAllocator>;

  explicit XboxMsg_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : connected(_init),
    back(_init),
    leftx(_init),
    lefty(_init),
    right_trigger(_init),
    a(_init),
    b(_init),
    x(_init),
    y(_init),
    dpad_up(_init),
    dpad_down(_init),
    dpad_left(_init),
    dpad_right(_init)
  {
    (void)_init;
  }

  explicit XboxMsg_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : connected(_alloc, _init),
    back(_alloc, _init),
    leftx(_alloc, _init),
    lefty(_alloc, _init),
    right_trigger(_alloc, _init),
    a(_alloc, _init),
    b(_alloc, _init),
    x(_alloc, _init),
    y(_alloc, _init),
    dpad_up(_alloc, _init),
    dpad_down(_alloc, _init),
    dpad_left(_alloc, _init),
    dpad_right(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _connected_type =
    std_msgs::msg::Bool_<ContainerAllocator>;
  _connected_type connected;
  using _back_type =
    std_msgs::msg::Int16_<ContainerAllocator>;
  _back_type back;
  using _leftx_type =
    std_msgs::msg::Float64_<ContainerAllocator>;
  _leftx_type leftx;
  using _lefty_type =
    std_msgs::msg::Float64_<ContainerAllocator>;
  _lefty_type lefty;
  using _right_trigger_type =
    std_msgs::msg::Float64_<ContainerAllocator>;
  _right_trigger_type right_trigger;
  using _a_type =
    std_msgs::msg::Int16_<ContainerAllocator>;
  _a_type a;
  using _b_type =
    std_msgs::msg::Int16_<ContainerAllocator>;
  _b_type b;
  using _x_type =
    std_msgs::msg::Int16_<ContainerAllocator>;
  _x_type x;
  using _y_type =
    std_msgs::msg::Int16_<ContainerAllocator>;
  _y_type y;
  using _dpad_up_type =
    std_msgs::msg::Int16_<ContainerAllocator>;
  _dpad_up_type dpad_up;
  using _dpad_down_type =
    std_msgs::msg::Int16_<ContainerAllocator>;
  _dpad_down_type dpad_down;
  using _dpad_left_type =
    std_msgs::msg::Int16_<ContainerAllocator>;
  _dpad_left_type dpad_left;
  using _dpad_right_type =
    std_msgs::msg::Int16_<ContainerAllocator>;
  _dpad_right_type dpad_right;

  // setters for named parameter idiom
  Type & set__connected(
    const std_msgs::msg::Bool_<ContainerAllocator> & _arg)
  {
    this->connected = _arg;
    return *this;
  }
  Type & set__back(
    const std_msgs::msg::Int16_<ContainerAllocator> & _arg)
  {
    this->back = _arg;
    return *this;
  }
  Type & set__leftx(
    const std_msgs::msg::Float64_<ContainerAllocator> & _arg)
  {
    this->leftx = _arg;
    return *this;
  }
  Type & set__lefty(
    const std_msgs::msg::Float64_<ContainerAllocator> & _arg)
  {
    this->lefty = _arg;
    return *this;
  }
  Type & set__right_trigger(
    const std_msgs::msg::Float64_<ContainerAllocator> & _arg)
  {
    this->right_trigger = _arg;
    return *this;
  }
  Type & set__a(
    const std_msgs::msg::Int16_<ContainerAllocator> & _arg)
  {
    this->a = _arg;
    return *this;
  }
  Type & set__b(
    const std_msgs::msg::Int16_<ContainerAllocator> & _arg)
  {
    this->b = _arg;
    return *this;
  }
  Type & set__x(
    const std_msgs::msg::Int16_<ContainerAllocator> & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const std_msgs::msg::Int16_<ContainerAllocator> & _arg)
  {
    this->y = _arg;
    return *this;
  }
  Type & set__dpad_up(
    const std_msgs::msg::Int16_<ContainerAllocator> & _arg)
  {
    this->dpad_up = _arg;
    return *this;
  }
  Type & set__dpad_down(
    const std_msgs::msg::Int16_<ContainerAllocator> & _arg)
  {
    this->dpad_down = _arg;
    return *this;
  }
  Type & set__dpad_left(
    const std_msgs::msg::Int16_<ContainerAllocator> & _arg)
  {
    this->dpad_left = _arg;
    return *this;
  }
  Type & set__dpad_right(
    const std_msgs::msg::Int16_<ContainerAllocator> & _arg)
  {
    this->dpad_right = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sdv_msgs::msg::XboxMsg_<ContainerAllocator> *;
  using ConstRawPtr =
    const sdv_msgs::msg::XboxMsg_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sdv_msgs::msg::XboxMsg_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sdv_msgs::msg::XboxMsg_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sdv_msgs::msg::XboxMsg_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sdv_msgs::msg::XboxMsg_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sdv_msgs::msg::XboxMsg_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sdv_msgs::msg::XboxMsg_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sdv_msgs::msg::XboxMsg_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sdv_msgs::msg::XboxMsg_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sdv_msgs__msg__XboxMsg
    std::shared_ptr<sdv_msgs::msg::XboxMsg_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sdv_msgs__msg__XboxMsg
    std::shared_ptr<sdv_msgs::msg::XboxMsg_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const XboxMsg_ & other) const
  {
    if (this->connected != other.connected) {
      return false;
    }
    if (this->back != other.back) {
      return false;
    }
    if (this->leftx != other.leftx) {
      return false;
    }
    if (this->lefty != other.lefty) {
      return false;
    }
    if (this->right_trigger != other.right_trigger) {
      return false;
    }
    if (this->a != other.a) {
      return false;
    }
    if (this->b != other.b) {
      return false;
    }
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->dpad_up != other.dpad_up) {
      return false;
    }
    if (this->dpad_down != other.dpad_down) {
      return false;
    }
    if (this->dpad_left != other.dpad_left) {
      return false;
    }
    if (this->dpad_right != other.dpad_right) {
      return false;
    }
    return true;
  }
  bool operator!=(const XboxMsg_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct XboxMsg_

// alias to use template instance with default allocator
using XboxMsg =
  sdv_msgs::msg::XboxMsg_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__XBOX_MSG__STRUCT_HPP_
