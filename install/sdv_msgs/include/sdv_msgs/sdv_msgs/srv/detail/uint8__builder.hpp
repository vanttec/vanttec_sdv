// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sdv_msgs:srv/Uint8.idl
// generated code does not contain a copyright notice

#ifndef SDV_MSGS__SRV__DETAIL__UINT8__BUILDER_HPP_
#define SDV_MSGS__SRV__DETAIL__UINT8__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sdv_msgs/srv/detail/uint8__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sdv_msgs
{

namespace srv
{

namespace builder
{

class Init_Uint8_Request_data
{
public:
  Init_Uint8_Request_data()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::sdv_msgs::srv::Uint8_Request data(::sdv_msgs::srv::Uint8_Request::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sdv_msgs::srv::Uint8_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::sdv_msgs::srv::Uint8_Request>()
{
  return sdv_msgs::srv::builder::Init_Uint8_Request_data();
}

}  // namespace sdv_msgs


namespace sdv_msgs
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::sdv_msgs::srv::Uint8_Response>()
{
  return ::sdv_msgs::srv::Uint8_Response(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace sdv_msgs

#endif  // SDV_MSGS__SRV__DETAIL__UINT8__BUILDER_HPP_
