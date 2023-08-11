cmake_minimum_required(VERSION 3.5)
project(sdv_control)


if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_ros REQUIRED)
find_package(sdv_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2 REQUIRED)
find_package(pluginlib REQUIRED)

# Add include directories
include_directories(
    vanttec_controllers/
    vanttec_controllers/dynamic_models/ground_vehicles/car_like/
    vanttec_controllers/controllers/feedback_linearization/PID_based/first_order/
    vanttec_controllers/controllers/guidance_laws/
    ${ament_INCLUDE_DIRS}
)

# set(dependencies
#     sdv_msgs
#     std_msgs
#     rclcpp
#     geometry_msgs
#     nav_msgs
#     tf2_ros
#     tf2
#     pluginlib
# )

# set(libraries
#     dynamic_model
#     car_simulation_node
#     car_tf2_broadcast_node
#     # car_control_node
# )

#Add cpp library files
# add_library(dynamic_model SHARED
#                 libs/vanttec_controllers/dynamic_models/ground_vehicles/car_like/vehicles/vtec_sdc1.cpp
#                 libs/vanttec_controllers/dynamic_models/ground_vehicles/car_like/base/car_3dof_dynamic_model.cpp
#                 libs/vanttec_controllers/simulation/tf2_6dof_broadcaster_ros2.hpp
#                 libs/vanttec_controllers/controllers/control_laws/PID/first_order/pid.cpp
#                 libs/vanttec_controllers/controllers/guidance_laws/stanley_controller.cpp
#                 src/vanttec_controllers/controllers/controllers_merge.cpp)
# target_include_directories(dynamic_model PUBLIC
# $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
# $<INSTALL_INTERFACE:include>
# )

#target_compile_definitions(sdv_control PRIVATE "sdv_control_BUILDING_LIBRARY")
#Add executables
add_executable(car_simulation_node 
              src/model/car_simulation_node.cpp
              libs/vanttec_controllers/dynamic_models/ground_vehicles/car_like/vehicles/vtec_sdc1.cpp
              libs/vanttec_controllers/dynamic_models/ground_vehicles/car_like/base/car_3dof_dynamic_model.cpp
              )
ament_target_dependencies(car_simulation_node rclcpp std_msgs)

# target_link_libraries(car_simulation_node dynamic_model)
# target_include_directories(car_simulation_node PUBLIC
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#   $<INSTALL_INTERFACE:include>)
# target_compile_features(car_simulation_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17


# add_executable(car_tf2_broadcast_node src/model/car_tf2_broadcast_node.cpp)
# target_link_libraries(car_tf2_broadcast_node dynamic_model)
# target_include_directories(car_tf2_broadcast_node PUBLIC
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#   $<INSTALL_INTERFACE:include>)
# target_compile_features(car_tf2_broadcast_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

# add_executable(car_control_node src/model/car_control_node.cpp)
# target_link_libraries(car_control_node dynamic_model)
# target_include_directories(car_control_node PUBLIC
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#   $<INSTALL_INTERFACE:include>)
# target_compile_features(car_control_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

# ament_target_dependencies(dynamic_model
#   ${dependencies}
# )

#### Install
install(TARGETS #${libraries}
  car_simulation_node
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/
  DESTINATION include
)

install(DIRECTORY launch 
  DESTINATION share/${PROJECT_NAME}
)
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# ament_export_include_directories(include)
# ament_export_libraries(${libraries})
# ament_export_dependencies(${dependencies})
ament_package()
