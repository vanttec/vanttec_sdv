#!/bin/bash

build_workspace() {
  local WS="$1"
  local SHELL_TYPE="${2:-bash}" # default bash, override para zsh

  local ROS_SETUP="/opt/ros/humble/setup.$SHELL_TYPE"
  local WS_SETUP="install/setup.$SHELL_TYPE"

  cd "$WS"

  source "$ROS_SETUP"

  _build() { colcon build --packages-select "$@"; }
  _source() { source "$WS_SETUP"; }

  _build pointcloud_rotation
  _build lidar_imu_sync
  _build robot_description
  _build vectornav_msgs vectornav
  _build velodyne_msgs velodyne_driver velodyne_laserscan velodyne_pointcloud velodyne
  _build lio_sam
  _build ndt_omp_ros2 lidar_localization_ros2
  _build sensors_launch sdv_msgs

  _source

  _build sdv_control sdv_can sdv_velocity
  _build mrt_cmake_modules polygon_utils

  _source

  _build polygon_msgs polygon_rviz_plugins
  _build obstacles_information_msgs traffic_information_msgs

  _source

  _build pointcloud_clustering pointcloud_clustering_KDTree
  _build lanelet2_core lanelet2_io

  _source

  _build lanelet2_maps lanelet2_projection lanelet2_traffic_rules

  _source

  _build lanelet2_routing lanelet2_validation

  _source

  _build waypoints_routing path_planning_dynamic

  _source

  echo "[build] Build complete."
}