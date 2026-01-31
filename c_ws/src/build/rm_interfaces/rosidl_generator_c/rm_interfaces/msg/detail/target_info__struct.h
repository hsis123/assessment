// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rm_interfaces:msg/TargetInfo.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__TARGET_INFO__STRUCT_H_
#define RM_INTERFACES__MSG__DETAIL__TARGET_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/TargetInfo in the package rm_interfaces.
typedef struct rm_interfaces__msg__TargetInfo
{
  double x;
  double y;
  double z;
} rm_interfaces__msg__TargetInfo;

// Struct for a sequence of rm_interfaces__msg__TargetInfo.
typedef struct rm_interfaces__msg__TargetInfo__Sequence
{
  rm_interfaces__msg__TargetInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rm_interfaces__msg__TargetInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RM_INTERFACES__MSG__DETAIL__TARGET_INFO__STRUCT_H_
