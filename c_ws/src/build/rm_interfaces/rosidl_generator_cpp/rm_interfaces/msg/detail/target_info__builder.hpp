// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rm_interfaces:msg/TargetInfo.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__TARGET_INFO__BUILDER_HPP_
#define RM_INTERFACES__MSG__DETAIL__TARGET_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rm_interfaces/msg/detail/target_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rm_interfaces
{

namespace msg
{

namespace builder
{

class Init_TargetInfo_z
{
public:
  explicit Init_TargetInfo_z(::rm_interfaces::msg::TargetInfo & msg)
  : msg_(msg)
  {}
  ::rm_interfaces::msg::TargetInfo z(::rm_interfaces::msg::TargetInfo::_z_type arg)
  {
    msg_.z = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rm_interfaces::msg::TargetInfo msg_;
};

class Init_TargetInfo_y
{
public:
  explicit Init_TargetInfo_y(::rm_interfaces::msg::TargetInfo & msg)
  : msg_(msg)
  {}
  Init_TargetInfo_z y(::rm_interfaces::msg::TargetInfo::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_TargetInfo_z(msg_);
  }

private:
  ::rm_interfaces::msg::TargetInfo msg_;
};

class Init_TargetInfo_x
{
public:
  Init_TargetInfo_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TargetInfo_y x(::rm_interfaces::msg::TargetInfo::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_TargetInfo_y(msg_);
  }

private:
  ::rm_interfaces::msg::TargetInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rm_interfaces::msg::TargetInfo>()
{
  return rm_interfaces::msg::builder::Init_TargetInfo_x();
}

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__MSG__DETAIL__TARGET_INFO__BUILDER_HPP_
