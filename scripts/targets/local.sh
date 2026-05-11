#!/bin/bash

REPO_DIR="$1"
SYNC="${2:-false}"  
DEPS_DIR="$REPO_DIR"

source "$REPO_DIR/scripts/lib/clone_deps.sh"
source "$REPO_DIR/scripts/lib/install_tinyspline.sh"
source "$REPO_DIR/scripts/lib/build_workspace.sh"

echo "=== Setup: Local ==="


echo "[apt] Installing dependencies of system..."
#Fundamental libraries
sudo apt update
sudo apt install tmux
sudo apt-get install libeigen3-dev
sudo apt install libpcl-dev
sudo apt-get install libpcap-dev
sudo apt install can-utils
sudo apt-get install libqt5serialport5-dev
sudo apt-get install libpugixml-dev
sudo apt-get install libgeographic-dev geographiclib-tools
sudo apt-get install libeigen3-dev
sudo apt install libpcl-dev
sudo apt-get install libpcap-dev
sudo apt install libopencv-dev

echo "[apt] Installing ROS2 packages..."
# Install ROS2 packages 
source /opt/ros/humble/setup.bash
sudo apt-get update
sudo apt-get install \
    ros-${ROS_DISTRO}-color-util \
    ros-${ROS_DISTRO}-diagnostic-updater \
    ros-${ROS_DISTRO}-foxglove-bridge \
    ros-${ROS_DISTRO}-image-common \
    ros-${ROS_DISTRO}-image-transport-plugins \
    ros-${ROS_DISTRO}-joint-state-publisher \
    ros-${ROS_DISTRO}-joint-state-publisher-gui \
    ros-${ROS_DISTRO}-pcl-msgs \
    ros-${ROS_DISTRO}-pcl-ros \
    ros-${ROS_DISTRO}-perception-pcl \
    ros-${ROS_DISTRO}-rmw-cyclonedds-cpp \
    ros-${ROS_DISTRO}-rviz2 \
    ros-${ROS_DISTRO}-tracetools-launch \
    ros-${ROS_DISTRO}-velodyne-msgs \
    ros-${ROS_DISTRO}-vision-msgs \
    ros-${ROS_DISTRO}-vision-opencv \
    ros-${ROS_DISTRO}-xacro \
    ros-${ROS_DISTRO}-cv-bridge \
    ros-${ROS_DISTRO}-grid-map-ros\
    ros-${ROS_DISTRO}-cv-bridge

clone_deps         "$DEPS_DIR" "$REPO_DIR" "$SYNC"
install_tinyspline "$REPO_DIR" "sudo"
build_workspace "$REPO_DIR/workspace" "$SHELL_TYPE"