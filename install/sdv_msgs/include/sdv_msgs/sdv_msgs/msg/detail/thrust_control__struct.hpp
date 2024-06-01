// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sdv_msgs:msg/ThrustControl.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__THRUST_CONTROL__STRUCT_HPP_
#define SDV_MSGS__MSG__DETAIL__THRUST_CONTROL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__sdv_msgs__msg__ThrustControl __attribute__((deprecated))
#else
# define DEPRECATED__sdv_msgs__msg__ThrustControl __declspec(deprecated)
#endif

namespace sdv_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ThrustControl_
{
  using Type = ThrustControl_<ContainerAllocator>;

  explicit ThrustControl_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tau_x = 0.0f;
      this->tau_y = 0.0f;
      this->tau_z = 0.0f;
      this->tau_phi = 0.0f;
      this->tau_theta = 0.0f;
      this->tau_psi = 0.0f;
    }
  }

  explicit ThrustControl_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tau_x = 0.0f;
      this->tau_y = 0.0f;
      this->tau_z = 0.0f;
      this->tau_phi = 0.0f;
      this->tau_theta = 0.0f;
      this->tau_psi = 0.0f;
    }
  }

  // field types and members
  using _tau_x_type =
    float;
  _tau_x_type tau_x;
  using _tau_y_type =
    float;
  _tau_y_type tau_y;
  using _tau_z_type =
    float;
  _tau_z_type tau_z;
  using _tau_phi_type =
    float;
  _tau_phi_type tau_phi;
  using _tau_theta_type =
    float;
  _tau_theta_type tau_theta;
  using _tau_psi_type =
    float;
  _tau_psi_type tau_psi;

  // setters for named parameter idiom
  Type & set__tau_x(
    const float & _arg)
  {
    this->tau_x = _arg;
    return *this;
  }
  Type & set__tau_y(
    const float & _arg)
  {
    this->tau_y = _arg;
    return *this;
  }
  Type & set__tau_z(
    const float & _arg)
  {
    this->tau_z = _arg;
    return *this;
  }
  Type & set__tau_phi(
    const float & _arg)
  {
    this->tau_phi = _arg;
    return *this;
  }
  Type & set__tau_theta(
    const float & _arg)
  {
    this->tau_theta = _arg;
    return *this;
  }
  Type & set__tau_psi(
    const float & _arg)
  {
    this->tau_psi = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sdv_msgs::msg::ThrustControl_<ContainerAllocator> *;
  using ConstRawPtr =
    const sdv_msgs::msg::ThrustControl_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sdv_msgs::msg::ThrustControl_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sdv_msgs::msg::ThrustControl_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sdv_msgs::msg::ThrustControl_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sdv_msgs::msg::ThrustControl_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sdv_msgs::msg::ThrustControl_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sdv_msgs::msg::ThrustControl_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sdv_msgs::msg::ThrustControl_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sdv_msgs::msg::ThrustControl_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sdv_msgs__msg__ThrustControl
    std::shared_ptr<sdv_msgs::msg::ThrustControl_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sdv_msgs__msg__ThrustControl
    std::shared_ptr<sdv_msgs::msg::ThrustControl_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ThrustControl_ & other) const
  {
    if (this->tau_x != other.tau_x) {
      return false;
    }
    if (this->tau_y != other.tau_y) {
      return false;
    }
    if (this->tau_z != other.tau_z) {
      return false;
    }
    if (this->tau_phi != other.tau_phi) {
      return false;
    }
    if (this->tau_theta != other.tau_theta) {
      return false;
    }
    if (this->tau_psi != other.tau_psi) {
      return false;
    }
    return true;
  }
  bool operator!=(const ThrustControl_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ThrustControl_

// alias to use template instance with default allocator
using ThrustControl =
  sdv_msgs::msg::ThrustControl_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__THRUST_CONTROL__STRUCT_HPP_
