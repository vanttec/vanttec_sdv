// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sdv_msgs:msg/VehicleInfo.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__MSG__DETAIL__VEHICLE_INFO__BUILDER_HPP_
#define SDV_MSGS__MSG__DETAIL__VEHICLE_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sdv_msgs/msg/detail/vehicle_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sdv_msgs
{

namespace msg
{

namespace builder
{

class Init_VehicleInfo_center_of_mass
{
public:
  explicit Init_VehicleInfo_center_of_mass(::sdv_msgs::msg::VehicleInfo & msg)
  : msg_(msg)
  {}
  ::sdv_msgs::msg::VehicleInfo center_of_mass(::sdv_msgs::msg::VehicleInfo::_center_of_mass_type arg)
  {
    msg_.center_of_mass = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleInfo msg_;
};

class Init_VehicleInfo_drag_coefficient
{
public:
  explicit Init_VehicleInfo_drag_coefficient(::sdv_msgs::msg::VehicleInfo & msg)
  : msg_(msg)
  {}
  Init_VehicleInfo_center_of_mass drag_coefficient(::sdv_msgs::msg::VehicleInfo::_drag_coefficient_type arg)
  {
    msg_.drag_coefficient = std::move(arg);
    return Init_VehicleInfo_center_of_mass(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleInfo msg_;
};

class Init_VehicleInfo_mass
{
public:
  explicit Init_VehicleInfo_mass(::sdv_msgs::msg::VehicleInfo & msg)
  : msg_(msg)
  {}
  Init_VehicleInfo_drag_coefficient mass(::sdv_msgs::msg::VehicleInfo::_mass_type arg)
  {
    msg_.mass = std::move(arg);
    return Init_VehicleInfo_drag_coefficient(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleInfo msg_;
};

class Init_VehicleInfo_clutch_strength
{
public:
  explicit Init_VehicleInfo_clutch_strength(::sdv_msgs::msg::VehicleInfo & msg)
  : msg_(msg)
  {}
  Init_VehicleInfo_mass clutch_strength(::sdv_msgs::msg::VehicleInfo::_clutch_strength_type arg)
  {
    msg_.clutch_strength = std::move(arg);
    return Init_VehicleInfo_mass(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleInfo msg_;
};

class Init_VehicleInfo_gear_switch_time
{
public:
  explicit Init_VehicleInfo_gear_switch_time(::sdv_msgs::msg::VehicleInfo & msg)
  : msg_(msg)
  {}
  Init_VehicleInfo_clutch_strength gear_switch_time(::sdv_msgs::msg::VehicleInfo::_gear_switch_time_type arg)
  {
    msg_.gear_switch_time = std::move(arg);
    return Init_VehicleInfo_clutch_strength(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleInfo msg_;
};

class Init_VehicleInfo_use_gear_autobox
{
public:
  explicit Init_VehicleInfo_use_gear_autobox(::sdv_msgs::msg::VehicleInfo & msg)
  : msg_(msg)
  {}
  Init_VehicleInfo_gear_switch_time use_gear_autobox(::sdv_msgs::msg::VehicleInfo::_use_gear_autobox_type arg)
  {
    msg_.use_gear_autobox = std::move(arg);
    return Init_VehicleInfo_gear_switch_time(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleInfo msg_;
};

class Init_VehicleInfo_damping_rate_zero_throttle_clutch_disengaged
{
public:
  explicit Init_VehicleInfo_damping_rate_zero_throttle_clutch_disengaged(::sdv_msgs::msg::VehicleInfo & msg)
  : msg_(msg)
  {}
  Init_VehicleInfo_use_gear_autobox damping_rate_zero_throttle_clutch_disengaged(::sdv_msgs::msg::VehicleInfo::_damping_rate_zero_throttle_clutch_disengaged_type arg)
  {
    msg_.damping_rate_zero_throttle_clutch_disengaged = std::move(arg);
    return Init_VehicleInfo_use_gear_autobox(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleInfo msg_;
};

class Init_VehicleInfo_damping_rate_zero_throttle_clutch_engaged
{
public:
  explicit Init_VehicleInfo_damping_rate_zero_throttle_clutch_engaged(::sdv_msgs::msg::VehicleInfo & msg)
  : msg_(msg)
  {}
  Init_VehicleInfo_damping_rate_zero_throttle_clutch_disengaged damping_rate_zero_throttle_clutch_engaged(::sdv_msgs::msg::VehicleInfo::_damping_rate_zero_throttle_clutch_engaged_type arg)
  {
    msg_.damping_rate_zero_throttle_clutch_engaged = std::move(arg);
    return Init_VehicleInfo_damping_rate_zero_throttle_clutch_disengaged(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleInfo msg_;
};

class Init_VehicleInfo_damping_rate_full_throttle
{
public:
  explicit Init_VehicleInfo_damping_rate_full_throttle(::sdv_msgs::msg::VehicleInfo & msg)
  : msg_(msg)
  {}
  Init_VehicleInfo_damping_rate_zero_throttle_clutch_engaged damping_rate_full_throttle(::sdv_msgs::msg::VehicleInfo::_damping_rate_full_throttle_type arg)
  {
    msg_.damping_rate_full_throttle = std::move(arg);
    return Init_VehicleInfo_damping_rate_zero_throttle_clutch_engaged(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleInfo msg_;
};

class Init_VehicleInfo_moi
{
public:
  explicit Init_VehicleInfo_moi(::sdv_msgs::msg::VehicleInfo & msg)
  : msg_(msg)
  {}
  Init_VehicleInfo_damping_rate_full_throttle moi(::sdv_msgs::msg::VehicleInfo::_moi_type arg)
  {
    msg_.moi = std::move(arg);
    return Init_VehicleInfo_damping_rate_full_throttle(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleInfo msg_;
};

class Init_VehicleInfo_max_rpm
{
public:
  explicit Init_VehicleInfo_max_rpm(::sdv_msgs::msg::VehicleInfo & msg)
  : msg_(msg)
  {}
  Init_VehicleInfo_moi max_rpm(::sdv_msgs::msg::VehicleInfo::_max_rpm_type arg)
  {
    msg_.max_rpm = std::move(arg);
    return Init_VehicleInfo_moi(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleInfo msg_;
};

class Init_VehicleInfo_wheels
{
public:
  explicit Init_VehicleInfo_wheels(::sdv_msgs::msg::VehicleInfo & msg)
  : msg_(msg)
  {}
  Init_VehicleInfo_max_rpm wheels(::sdv_msgs::msg::VehicleInfo::_wheels_type arg)
  {
    msg_.wheels = std::move(arg);
    return Init_VehicleInfo_max_rpm(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleInfo msg_;
};

class Init_VehicleInfo_rolename
{
public:
  explicit Init_VehicleInfo_rolename(::sdv_msgs::msg::VehicleInfo & msg)
  : msg_(msg)
  {}
  Init_VehicleInfo_wheels rolename(::sdv_msgs::msg::VehicleInfo::_rolename_type arg)
  {
    msg_.rolename = std::move(arg);
    return Init_VehicleInfo_wheels(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleInfo msg_;
};

class Init_VehicleInfo_type
{
public:
  explicit Init_VehicleInfo_type(::sdv_msgs::msg::VehicleInfo & msg)
  : msg_(msg)
  {}
  Init_VehicleInfo_rolename type(::sdv_msgs::msg::VehicleInfo::_type_type arg)
  {
    msg_.type = std::move(arg);
    return Init_VehicleInfo_rolename(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleInfo msg_;
};

class Init_VehicleInfo_id
{
public:
  Init_VehicleInfo_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VehicleInfo_type id(::sdv_msgs::msg::VehicleInfo::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_VehicleInfo_type(msg_);
  }

private:
  ::sdv_msgs::msg::VehicleInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sdv_msgs::msg::VehicleInfo>()
{
  return sdv_msgs::msg::builder::Init_VehicleInfo_id();
}

}  // namespace sdv_msgs

#endif  // SDV_MSGS__MSG__DETAIL__VEHICLE_INFO__BUILDER_HPP_
