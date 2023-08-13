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
find_package(diagnostic_msgs REQUIRED)

set(DEPENDENCIES
    sdv_msgs
    std_msgs
    rclcpp
    geometry_msgs
    nav_msgs
    tf2_ros
    tf2
    diagnostic_msgs
)

set(LIBRARIES
    VANTTEC_CONTROLLERS
    # sdc1_simulation_node
    # car_tf2_broadcast_node
    # car_control_node
)

set(VANTTEC_CONTROLLER_SOURCES
    # ${CMAKE_CURRENT_SOURCE_DIR}/libs/vanttec_controllers/dynamic_models/ground_vehicles/car_like/vehicles/vtec_sdc1.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/vanttec_controllers/dynamic_models/ground_vehicles/car_like/base/car_3dof_dynamic_model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/vanttec_controllers/utils/utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/vanttec_controllers/simulation/tf2_6dof_broadcaster_ros2.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/libs/vanttec_controllers/controllers/control_laws/PID/first_order/pid.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/libs/vanttec_controllers/controllers/guidance_laws/stanley_controller.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/src/vanttec_controllers/controllers/controllers_merge.cpp
)

set(VANTTEC_CONTROLLER_PATHS
    # ${CMAKE_CURRENT_SOURCE_DIR}/libs/vanttec_controllers/dynamic_models/ground_vehicles/car_like/
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/vanttec_controllers/simulation/
    # ${CMAKE_CURRENT_SOURCE_DIR}/libs/vanttec_controllers/controllers/control_laws/PID/first_order/
    # ${CMAKE_CURRENT_SOURCE_DIR}/libs/vanttec_controllers/controllers/guidance_laws/
    # ${CMAKE_CURRENT_SOURCE_DIR}/libs/vanttec_controllers/controllers/
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/vanttec_controllers/
)

#Add cpp library files
add_library(VANTTEC_CONTROLLERS SHARED ${VANTTEC_CONTROLLER_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/vanttec_controllers/dynamic_models/ground_vehicles/car_like/vehicles/vtec_sdc1.cpp
)

# Specify the include directories for the libraries
target_include_directories(VANTTEC_CONTROLLERS
  PUBLIC
  $<BUILD_INTERFACE:${VANTTEC_CONTROLLER_PATHS}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libs/vanttec_controllers/dynamic_models/ground_vehicles/car_like/>
  $<INSTALL_INTERFACE:include>
)

ament_target_dependencies(VANTTEC_CONTROLLERS ${DEPENDENCIES})

#target_compile_definitions(sdv_control PRIVATE "sdv_control_BUILDING_LIBRARY")

#   ********************** SDC1 SIMULATION NODE
#Add executables
add_executable(sdc1_simulation_node 
              src/model/sdc1_simulation_node.cpp)
# Link against required libraries
target_link_libraries(sdc1_simulation_node
    VANTTEC_CONTROLLERS
    # ${rclcpp_LIBRARIES}
    # ${std_msgs_LIBRARIES}
    # ${sdv_msgs_LIBRARIES}
    # ${diagnostic_msgs_LIBRARIES}
)
# Include directories for project headers and other package headers
target_include_directories(sdc1_simulation_node
            PUBLIC
            # $<BUILD_INTERFACE:${VANTTEC_CONTROLLER_PATHS}>
            $<BUILD_INTERFACE:${sdv_msgs_INCLUDE_DIRS}>
            $<INSTALL_INTERFACE:include>
)
target_compile_features(sdc1_simulation_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

#   ********************** TF2 BROADCAST NODE
#Add executables
add_executable(car_tf2_broadcast_node 
              src/model/car_tf2_broadcast_node.cpp)
# Link against required libraries
target_link_libraries(car_tf2_broadcast_node
    VANTTEC_CONTROLLERS
    # ${rclcpp_LIBRARIES}
    # ${geometry_msgs_LIBRARIES}
    # ${nav_msgs_LIBRARIES}
    # ${sdv_msgs_LIBRARIES}
)
# Include directories for project headers and other package headers
target_include_directories(car_tf2_broadcast_node
            PUBLIC
            # $<BUILD_INTERFACE:${VANTTEC_CONTROLLER_PATHS}>
            $<BUILD_INTERFACE:${sdv_msgs_INCLUDE_DIRS}>
            $<INSTALL_INTERFACE:include>
)
target_compile_features(car_tf2_broadcast_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17




# target_link_libraries(sdc1_simulation_node dynamic_model)
# target_include_directories(sdc1_simulation_node PUBLIC
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#   $<INSTALL_INTERFACE:include>)
# target_compile_features(sdc1_simulation_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17


# add_executable(car_control_node src/model/car_control_node.cpp)
# target_link_libraries(car_control_node dynamic_model)
# target_include_directories(car_control_node PUBLIC
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#   $<INSTALL_INTERFACE:include>)
# target_compile_features(car_control_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17


#### Install
install(TARGETS 
  ${LIBRARIES}
  sdc1_simulation_node
  car_tf2_broadcast_node
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME}
)

# Install header files
install(DIRECTORY ${VANTTEC_CONTROLLER_PATHS}
  DESTINATION include/${PROJECT_NAME}
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

ament_export_include_directories(include)
ament_export_dependencies(${DEPENDENCIES})
ament_package()