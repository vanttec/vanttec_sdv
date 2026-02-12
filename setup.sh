#!/bin/bash

git clone https://github.com/armando-genis/navpilot-framework.git
cd navpilot-framework/workspace/navpilot_ws/src

# Clone sensors stack
cd sensor_stack
if [ ! -d "velodyne" ]; then
    git clone https://github.com/ros-drivers/velodyne.git
fi
if [ ! -d "vectornav" ]; then
    git clone https://github.com/dawonn/vectornav.git -b ros2
fi
cd ..

# Clone mapping modules
cd mapping_modules
if [ ! -d "LIO-SAM" ]; then
    git clone https://github.com/TixiaoShan/LIO-SAM.git -b ros2
fi
cd ..

# Clone localization modules
cd localization_modules
if [ ! -d "ndt_omp_ros2" ]; then
    git clone https://github.com/rsasaki0109/ndt_omp_ros2
fi
if [ ! -d "lidar_localization_ros2" ]; then
    git clone https://github.com/rsasaki0109/lidar_localization_ros2.git
fi
cd ..

if [ ! -d "mrt_cmake_modules" ]; then
    git clone https://github.com/KIT-MRT/mrt_cmake_modules.git
fi

cd ../../../../

# Copy all to workspace/src
if [ ! -d "workspace/src/mrt_cmake_modules" ]; then
    cp -r navpilot-framework/workspace/navpilot_ws/src/* workspace/src/
fi

# Install TinySpline
if [ ! -d "tinyspline" ]; then
    git clone https://github.com/msteinbeck/tinyspline.git
    cd tinyspline
    mkdir build
    cd build
    cmake ..
    cmake --build .
    sudo cmake --install .
    cd ../..
fi

#Fundamental libraries
sudo apt update
sudo apt install tmuxsudo apt-get install libeigen3-dev
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

# Colcon build packages
cd workspace
colcon build --packages-select pointcloud_rotation
colcon build --packages-select lidar_imu_sync
colcon build --packages-select robot_description
colcon build --packages-select vectornav_msgs
colcon build --packages-select vectornav
colcon build --packages-select velodyne_msgs
colcon build --packages-select velodyne_driver
colcon build --packages-select velodyne_laserscan
colcon build --packages-select velodyne_pointcloud
colcon build --packages-select velodyne
colcon build --packages-select lio_sam
colcon build --packages-select ndt_omp_ros2
colcon build --packages-select lidar_localization_ros2
colcon build --packages-select sensors_launch
colcon build --packages-select sdv_msgs
colcon build --packages-select sdv_velocity
source install/setup.bash
colcon build --packages-select sdv_control
colcon build --packages-select sdv_can
colcon build --packages-select mrt_cmake_modules
colcon build --packages-select polygon_msgs
colcon build --packages-select polygon_rviz_plugins
colcon build --packages-select polygon_utils
colcon build --packages-select obstacles_information_msgs
colcon build --packages-select traffic_information_msgs
source install/setup.bash
colcon build --packages-select pointcloud_clustering
colcon build --packages-select lanelet2_core
source install/setup.bash
colcon build --packages-select lanelet2_maps
colcon build --packages-select lanelet2_projection
colcon build --packages-select lanelet2_traffic_rules
source install/setup.bash
colcon build --packages-select lanelet2_routing
colcon build --packages-select lanelet2_io
colcon build --packages-select lanelet2_projection
colcon build --packages-select lanelet2_validation
source install/setup.bash
colcon build --packages-select waypoints_routing
colcon build --packages-select path_planning_dynamic
source install/setup.bash