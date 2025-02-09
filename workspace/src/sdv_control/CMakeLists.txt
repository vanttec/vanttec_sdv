cmake_minimum_required(VERSION 3.8)
project(sdv_control)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(vectornav_msgs REQUIRED)
find_package(nav_msgs)
find_package(sensor_msgs)
find_package(Eigen3 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(sdv_msgs REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(tf2 REQUIRED)
find_package(diagnostic_msgs REQUIRED)
find_package(rclpy REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(ament_cmake_python REQUIRED)

set(DEPENDENCIES
    sdv_msgs
    std_msgs
    rclcpp
    geometry_msgs
    nav_msgs
    tf2_ros
    tf2
    Eigen3
    diagnostic_msgs
    vectornav_msgs
    tf2_geometry_msgs
)

add_subdirectory(libs/vanttec_controllers)
ament_python_install_package(scripts)

add_library(tf2_lib SHARED 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/simulation/sdc1_broadcaster.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/simulation/tf2_6dof_broadcaster_ros2.cpp
)
ament_target_dependencies(tf2_lib ${DEPENDENCIES})

install(TARGETS tf2_lib
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
)

add_executable(sdc1_vel_pid_node src/control/regulators/first_order/sdc1_vel_pid_node.cpp)
target_include_directories(sdc1_vel_pid_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include> libs/vanttec_controllers)
target_compile_features(sdc1_vel_pid_node PUBLIC c_std_99 cxx_std_17)
ament_target_dependencies(sdc1_vel_pid_node ${DEPENDENCIES})
target_link_libraries(sdc1_vel_pid_node vanttec_controllers)

add_executable(stanley_controller_node src/control/guidance_laws/stanley_controller_node.cpp)
target_include_directories(stanley_controller_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include> libs/vanttec_controllers)
target_compile_features(stanley_controller_node PUBLIC c_std_99 cxx_std_17)
ament_target_dependencies(stanley_controller_node ${DEPENDENCIES})
target_link_libraries(stanley_controller_node vanttec_controllers)

add_executable(sdc1_dynamic_model_node src/model/sdc1_dynamic_model_node.cpp)
target_include_directories(sdc1_dynamic_model_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include> libs/vanttec_controllers)
target_compile_features(sdc1_dynamic_model_node PUBLIC c_std_99 cxx_std_17)
ament_target_dependencies(sdc1_dynamic_model_node ${DEPENDENCIES})
target_link_libraries(sdc1_dynamic_model_node vanttec_controllers)

# add_executable(sdv_kinematic_sim src/model/sdv_kinematic_sim_node.cpp)
# target_include_directories(sdv_kinematic_sim PUBLIC
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#   $<INSTALL_INTERFACE:include> libs/vanttec_controllers)
# target_compile_features(sdv_kinematic_sim PUBLIC c_std_99 cxx_std_17)
# ament_target_dependencies(sdv_kinematic_sim ${DEPENDENCIES})
# target_link_libraries(sdv_kinematic_sim vanttec_controllers)

# add_executable(velocity_regulator_node src/control/regulators/first_order/velocity_regulator_node.cpp)
# target_include_directories(velocity_regulator_node PUBLIC
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#   $<INSTALL_INTERFACE:include> libs/vanttec_controllers)
# target_compile_features(velocity_regulator_node PUBLIC c_std_99 cxx_std_17)
# ament_target_dependencies(velocity_regulator_node ${DEPENDENCIES})
# target_link_libraries(velocity_regulator_node vanttec_controllers)

add_executable(car_tf2_broadcast_node src/model/car_tf2_broadcast_node.cpp)
# Include directories for project headers and other package headers
target_include_directories(car_tf2_broadcast_node
            PUBLIC
            # $<BUILD_INTERFACE:${VANTTEC_CONTROLLER_PATHS}>
            $<BUILD_INTERFACE:${sdv_msgs_INCLUDE_DIRS}>
            $<INSTALL_INTERFACE:include>
)
target_compile_features(car_tf2_broadcast_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(car_tf2_broadcast_node ${DEPENDENCIES})
target_link_libraries(car_tf2_broadcast_node vanttec_controllers tf2_lib)
set_target_properties(car_tf2_broadcast_node PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

add_executable(sdc1_hybrid_model_node src/model/sdc1_hybrid_model_node.cpp)
target_include_directories(sdc1_hybrid_model_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include> libs/vanttec_controllers)
target_compile_features(sdc1_hybrid_model_node PUBLIC c_std_99 cxx_std_17)
ament_target_dependencies(sdc1_hybrid_model_node ${DEPENDENCIES})
target_link_libraries(sdc1_hybrid_model_node vanttec_controllers)

install(TARGETS 
  # sdc1_vel_pid_node
  # stanley_controller_node
  # sdv_kinematic_sim
  # velocity_regulator_node
  car_tf2_broadcast_node
  sdc1_hybrid_model_node
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY 
  config 
  launch
  rviz
  DESTINATION share/${PROJECT_NAME})

# Install Python executables
install(PROGRAMS
  scripts/path_publisher_node.py
  scripts/path_planner_node.py
  DESTINATION lib/${PROJECT_NAME}
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

ament_package()