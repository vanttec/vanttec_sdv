// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sdv_msgs:msg/SystemDynamics.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__SYSTEM_DYNAMICS__STRUCT_HPP_
#define SDV_MSGS__MSG__DETAIL__SYSTEM_DYNAMICS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'g'
#include "std_msgs/msg/detail/float32_multi_array__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__sdv_msgs__msg__SystemDynamics __attribute__((deprecated))
#else
# define DEPRECATED__sdv_msgs__msg__SystemDynamics __declspec(deprecated)
#endif

namespace sdv_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SystemDynamics_
{
  using Type = SystemDynamics_<ContainerAllocator>;

  explicit SystemDynamics_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : g(_init)
  {
    (void)_init;
  }

  explicit SystemDynamics_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : g(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _g_type =
    std_msgs::msg::Float32MultiArray_<ContainerAllocator>;
  _g_type g;
  using _f_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _f_type f;

  // setters for named parameter idiom
  Type & set__g(
    const std_msgs::msg::Float32MultiArray_<ContainerAllocator> & _arg)
  {
    this->g = _arg;
    return *this;
  }
  Type & set__f(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->f = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sdv_msgs::msg::SystemDynamics_<ContainerAllocator> *;
  using ConstRawPtr =
    const sdv_msgs::msg::SystemDynamics_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sdv_msgs::msg::SystemDynamics_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sdv_msgs::msg::SystemDynamics_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sdv_msgs::msg::SystemDynamics_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sdv_msgs::msg::SystemDynamics_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sdv_msgs::msg::SystemDynamics_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sdv_msgs::msg::SystemDynamics_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sdv_msgs::msg::SystemDynamics_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sdv_msgs::msg::SystemDynamics_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sdv_msgs__msg__SystemDynamics
    std::shared_ptr<sdv_msgs::msg::SystemDynamics_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sdv_msgs__msg__SystemDynamics
    std::shared_ptr<sdv_msgs::msg::SystemDynamics_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SystemDynamics_ & other) const
  {
    if (this->g != other.g) {
      return false;
    }
    if (this->f != other.f) {
      return false;
    }
    return true;
  }
  bool operator!=(const SystemDynamics_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SystemDynamics_

// alias to use template instance with default allocator
using SystemDynamics =
  sdv_msgs::msg::SystemDynamics_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__SYSTEM_DYNAMICS__STRUCT_HPP_
