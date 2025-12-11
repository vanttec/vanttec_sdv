<!-- markdownlint-configure-file {
  "MD013": { "code_blocks": false, "tables": false },
  "MD033": false,
  "MD041": false
} -->

<div align="center">

# 🚗 SDV_ROS2  
**Official ROS2 software stack for the VANTTEC Self-Driving Vehicle (SDV)**

This repository contains all modules required to operate the VANTTEC autonomous vehicle,  
including acceleration, steering, braking, lighting, LiDAR processing, IMU fusion,  
localization, mapping, and path planning.

---

### 📘 Quick Navigation  
[Getting Started](#getting-started) •  
[Setup](#-setup) •  
[Launching the System](#how-to-launch) •  
[Sensors](#sensor-stack) •  
[Mapping](#mapping-launchers) •  
[Localization](#localization-launchers) •  
[Path Planning](#path-planning-launchers) •  
[SDV Control](#sdv-control) •  
[CAN Communication](#can-communication) •  
[Recording Bags](#recording-bags) 

</div>

---

## Getting Started

![Tutorial][tutorial]

### **Requirements**
- Linux distribution (Ubuntu 22.04 recommended)
- ROS 2 Humble Hawksbill
- At least **8 GB RAM** recommended for full SLAM + planning stack


## 🔧 Setup
Run the environment setup script:

```sh
source setup.sh
```
### Building Packages of ROS2
If you need to compile everything from zero:

```sh
colcon build --packages-select pointcloud_rotation
colcon build --packages-select lidar_imu_sync
colcon build --packages-select robot_description
colcon build --packages-select vectornav_msgs vectornav
colcon build --packages-select velodyne_msgs velodyne_driver velodyne_laserscan velodyne_pointcloud velodyne
colcon build --packages-select lio_sam
colcon build --packages-select ndt_omp_ros2
colcon build --packages-select lidar_localization_ros2
colcon build --packages-select sensors_launch
colcon build --packages-select sdv_msgs
source install/setup.bash
colcon build --packages-select sdv_control sdv_can
colcon build --packages-select mrt_cmake_modules
colcon build --packages-select polygon_msgs polygon_rviz_plugins polygon_utils
colcon build --packages-select obstacles_information_msgs traffic_information_msgs
source install/setup.bash
colcon build --packages-select pointcloud_clustering lanelet2_core
source install/setup.bash
colcon build --packages-select lanelet2_maps lanelet2_projection lanelet2_traffic_rules
source install/setup.bash
colcon build --packages-select lanelet2_routing lanelet2_io lanelet2_validation
source install/setup.bash
colcon build --packages-select waypoints_routing
colcon build --packages-select path_planning_dynamic
source install/setup.bash
```
## 📌 Related Framework

This repository implement many software of this another repository:

🔗 NavPilot Framework (Armando Genis, vanttec member)
https://github.com/armando-genis/navpilot-framework

## How to Launch

Start the full SDV stack:
```sh
source launch.sh
```

This script launches multiple modules via tmux, so each subsystem runs in its own terminal panel.

Some extras commands

## Sensor stack
### → 🛰️ LiDAR + IMU Launch
```sh
ros2 launch sensors_launch lidar_imu.launch.py
```
## Mapping Launchers

Initialize mapping processes:
```sh
ros2 launch /workspace/src/mapping_modules/launcher/mapping.launch.py
```
## Localization Launchers

Run localization modules:
```sh
ros2 launch /workspace/src/localization_modules/launch/localization.launch.py
```
## Path Planning Launchers
```sh
ros2 launch navpilot-framework/src/path_planning/launch/planning_obstacles.launch.py
```
## SDV Control

Launch the control node:
```sh
ros2 launch sdv_control control_launch.py
```
## CAN Communication

Start the CAN node:

```sh
ros2 run sdv_can sdv_can_node
```
Steering Services (provided by CAN)

Set steering control mode:
```sh
ros2 service call /sdv/steering/set_mode sdv_msgs/srv/Uint8 "{data: 1}"
```
Reset the steering encoder:
```sh
ros2 service call /sdv/steering/reset_encoder std_srvs/srv/Empty "{}"
```
## Recording Bags
Record Rosbag (MCAP format)
```sh
ros2 bag record --storage mcap --all --output vanttec_sdv_localization_20250623
```
Play Rosbag
```sh
rviz2 -d /workspace/src/localization_modules/launch/localization.rviz

ros2 bag play vanttec_sdv_localization_20250623 -s mcap
```

Read more about the official documentation [here][vanttec-documentation].


[vanttec-documentation]: https://vanttec-documentation.readthedocs.io/
[tutorial]: docs/perrito-carro.webp