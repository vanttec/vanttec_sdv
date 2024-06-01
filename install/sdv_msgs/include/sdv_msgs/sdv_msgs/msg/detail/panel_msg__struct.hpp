// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sdv_msgs:msg/PanelMsg.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__PANEL_MSG__STRUCT_HPP_
#define SDV_MSGS__MSG__DETAIL__PANEL_MSG__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'wiper'
// Member 'horn'
// Member 'right_upper_front_light'
// Member 'left_upper_front_light'
// Member 'right_down_front_light'
// Member 'left_down_front_light'
// Member 'back'
#include "std_msgs/msg/detail/bool__struct.hpp"
// Member 'xboxcontrol'
#include "std_msgs/msg/detail/byte_multi_array__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__sdv_msgs__msg__PanelMsg __attribute__((deprecated))
#else
# define DEPRECATED__sdv_msgs__msg__PanelMsg __declspec(deprecated)
#endif

namespace sdv_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PanelMsg_
{
  using Type = PanelMsg_<ContainerAllocator>;

  explicit PanelMsg_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : wiper(_init),
    horn(_init),
    right_upper_front_light(_init),
    left_upper_front_light(_init),
    right_down_front_light(_init),
    left_down_front_light(_init),
    back(_init),
    xboxcontrol(_init)
  {
    (void)_init;
  }

  explicit PanelMsg_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : wiper(_alloc, _init),
    horn(_alloc, _init),
    right_upper_front_light(_alloc, _init),
    left_upper_front_light(_alloc, _init),
    right_down_front_light(_alloc, _init),
    left_down_front_light(_alloc, _init),
    back(_alloc, _init),
    xboxcontrol(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _wiper_type =
    std_msgs::msg::Bool_<ContainerAllocator>;
  _wiper_type wiper;
  using _horn_type =
    std_msgs::msg::Bool_<ContainerAllocator>;
  _horn_type horn;
  using _right_upper_front_light_type =
    std_msgs::msg::Bool_<ContainerAllocator>;
  _right_upper_front_light_type right_upper_front_light;
  using _left_upper_front_light_type =
    std_msgs::msg::Bool_<ContainerAllocator>;
  _left_upper_front_light_type left_upper_front_light;
  using _right_down_front_light_type =
    std_msgs::msg::Bool_<ContainerAllocator>;
  _right_down_front_light_type right_down_front_light;
  using _left_down_front_light_type =
    std_msgs::msg::Bool_<ContainerAllocator>;
  _left_down_front_light_type left_down_front_light;
  using _back_type =
    std_msgs::msg::Bool_<ContainerAllocator>;
  _back_type back;
  using _xboxcontrol_type =
    std_msgs::msg::ByteMultiArray_<ContainerAllocator>;
  _xboxcontrol_type xboxcontrol;

  // setters for named parameter idiom
  Type & set__wiper(
    const std_msgs::msg::Bool_<ContainerAllocator> & _arg)
  {
    this->wiper = _arg;
    return *this;
  }
  Type & set__horn(
    const std_msgs::msg::Bool_<ContainerAllocator> & _arg)
  {
    this->horn = _arg;
    return *this;
  }
  Type & set__right_upper_front_light(
    const std_msgs::msg::Bool_<ContainerAllocator> & _arg)
  {
    this->right_upper_front_light = _arg;
    return *this;
  }
  Type & set__left_upper_front_light(
    const std_msgs::msg::Bool_<ContainerAllocator> & _arg)
  {
    this->left_upper_front_light = _arg;
    return *this;
  }
  Type & set__right_down_front_light(
    const std_msgs::msg::Bool_<ContainerAllocator> & _arg)
  {
    this->right_down_front_light = _arg;
    return *this;
  }
  Type & set__left_down_front_light(
    const std_msgs::msg::Bool_<ContainerAllocator> & _arg)
  {
    this->left_down_front_light = _arg;
    return *this;
  }
  Type & set__back(
    const std_msgs::msg::Bool_<ContainerAllocator> & _arg)
  {
    this->back = _arg;
    return *this;
  }
  Type & set__xboxcontrol(
    const std_msgs::msg::ByteMultiArray_<ContainerAllocator> & _arg)
  {
    this->xboxcontrol = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sdv_msgs::msg::PanelMsg_<ContainerAllocator> *;
  using ConstRawPtr =
    const sdv_msgs::msg::PanelMsg_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sdv_msgs::msg::PanelMsg_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sdv_msgs::msg::PanelMsg_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sdv_msgs::msg::PanelMsg_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sdv_msgs::msg::PanelMsg_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sdv_msgs::msg::PanelMsg_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sdv_msgs::msg::PanelMsg_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sdv_msgs::msg::PanelMsg_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sdv_msgs::msg::PanelMsg_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sdv_msgs__msg__PanelMsg
    std::shared_ptr<sdv_msgs::msg::PanelMsg_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sdv_msgs__msg__PanelMsg
    std::shared_ptr<sdv_msgs::msg::PanelMsg_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PanelMsg_ & other) const
  {
    if (this->wiper != other.wiper) {
      return false;
    }
    if (this->horn != other.horn) {
      return false;
    }
    if (this->right_upper_front_light != other.right_upper_front_light) {
      return false;
    }
    if (this->left_upper_front_light != other.left_upper_front_light) {
      return false;
    }
    if (this->right_down_front_light != other.right_down_front_light) {
      return false;
    }
    if (this->left_down_front_light != other.left_down_front_light) {
      return false;
    }
    if (this->back != other.back) {
      return false;
    }
    if (this->xboxcontrol != other.xboxcontrol) {
      return false;
    }
    return true;
  }
  bool operator!=(const PanelMsg_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PanelMsg_

// alias to use template instance with default allocator
using PanelMsg =
  sdv_msgs::msg::PanelMsg_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__PANEL_MSG__STRUCT_HPP_
