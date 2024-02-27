cmake_minimum_required(VERSION 3.8)
project(sdv_can)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sdv_msgs REQUIRED)
find_package(vectornav_msgs REQUIRED)

add_executable(can_node src/can_node.cpp src/CANTxNode.cpp src/CANRxNode.cpp libs/vanttec_CANLib/platform_specific/vanttec_canlib_linux/CANHandler.cpp)
target_include_directories(can_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libs/vanttec_CANLib>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libs/vanttec_CANLib/platform_specific/vanttec_canlib_linux>
  $<INSTALL_INTERFACE:include>)
target_compile_features(can_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(can_node rclcpp std_msgs geometry_msgs)
add_subdirectory(libs/vanttec_CANLib)
target_link_libraries(can_node Vanttec_CANLibLIB)
# include_directories(libs/vanttec_CANLib/platform_specific/vanttec_canlib_linux)

install(DIRECTORY launch 
  DESTINATION share/${PROJECT_NAME}
)

install(DIRECTORY
  config
  DESTINATION share/${PROJECT_NAME}
)

install(
  TARGETS
  can_node
  DESTINATION lib/${PROJECT_NAME}/
)

install(PROGRAMS
  scripts/can_node.py
  scripts/encoder_rm8004.py
  scripts/encoder_briter.py
  scripts/xbox_driver.py
  scripts/xbox_node.py
  scripts/speech.py
  scripts/panel_modulev2.py
  scripts/heartbeat_node.py
  scripts/velocitydata.py
  scripts/direcciondata.py
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
