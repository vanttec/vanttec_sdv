#ifndef SDV_CONTROL_ROS2__VISIBILITY_CONTROL_H_
#define SDV_CONTROL_ROS2__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define SDV_CONTROL_ROS2_EXPORT __attribute__ ((dllexport))
    #define SDV_CONTROL_ROS2_IMPORT __attribute__ ((dllimport))
  #else
    #define SDV_CONTROL_ROS2_EXPORT __declspec(dllexport)
    #define SDV_CONTROL_ROS2_IMPORT __declspec(dllimport)
  #endif
  #ifdef SDV_CONTROL_ROS2_BUILDING_LIBRARY
    #define SDV_CONTROL_ROS2_PUBLIC SDV_CONTROL_ROS2_EXPORT
  #else
    #define SDV_CONTROL_ROS2_PUBLIC SDV_CONTROL_ROS2_IMPORT
  #endif
  #define SDV_CONTROL_ROS2_PUBLIC_TYPE SDV_CONTROL_ROS2_PUBLIC
  #define SDV_CONTROL_ROS2_LOCAL
#else
  #define SDV_CONTROL_ROS2_EXPORT __attribute__ ((visibility("default")))
  #define SDV_CONTROL_ROS2_IMPORT
  #if __GNUC__ >= 4
    #define SDV_CONTROL_ROS2_PUBLIC __attribute__ ((visibility("default")))
    #define SDV_CONTROL_ROS2_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define SDV_CONTROL_ROS2_PUBLIC
    #define SDV_CONTROL_ROS2_LOCAL
  #endif
  #define SDV_CONTROL_ROS2_PUBLIC_TYPE
#endif

#endif  // SDV_CONTROL_ROS2__VISIBILITY_CONTROL_H_
