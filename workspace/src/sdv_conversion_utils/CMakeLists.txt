cmake_minimum_required(VERSION 3.8)
project(sdv_conversion_utils)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(vectornav_msgs REQUIRED)

add_executable(vectornav_to_imu src/vectornav_to_imu.cpp)
ament_target_dependencies(vectornav_to_imu rclcpp std_msgs sensor_msgs vectornav_msgs)

install(TARGETS
  vectornav_to_imu
  DESTINATION lib/${PROJECT_NAME})

ament_package()
