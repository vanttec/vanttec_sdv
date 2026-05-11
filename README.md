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
- ROS 2 Humble
- At least **8 GB RAM**  with 12GB of swap recommended

## 🔧 Setup
Run the environment setup script:
```sh
source setup.sh --target local --sync
```
### With Docker (recommend)
Inisde of docker directory.

#### Step 1: Build the Docker Image

```bash
sudo docker compose build
```

#### Step 2: Start the Container

The `-d` flag ensures the container runs in detached mode (in the background).

```bash
sudo docker compose up -d
```

**Common error**:  *invalid subinterface vlan name* or similar, Just comment out all the lines inside Docker Compose, lidar_net: and its content, just apply on personal computers if you won't use the LiDAR.

#### Step 3: Access the Container

Use `zsh` to start a shell inside the container.

```bash
docker exec -it sdv_container zsh
```
#### Step 4: 📦 Install GitHub repositories & dependencies (colcon build)

The repository is mounted inside the container at **`/workspace`**.

If you are not already in `/workspace`, run:

```bash
cd /workspace
```

Run the setup/build script:

```bash
chmod +x setup.sh
source setup.sh --target docker --shell zsh --sync
```
 **Note:** The argument sync is for update the repositories of navpilot (do git pull).


### Building Packages of ROS2
If you need to compile everything from zero, list of all packages:

```sh
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
colcon build --packages-select sdv_control
colcon build --packages-select sdv_can
colcon build --packages-select sdv_velocity
colcon build --packages-select mrt_cmake_modules
colcon build --packages-select polygon_msgs 
colcon build --packages-selectp olygon_rviz_plugins 
colcon build --packages-select polygon_utils
colcon build --packages-select obstacles_information_msgs
colcon build --packages-select traffic_information_msgs
colcon build --packages-select pointcloud_clustering 
colcon build --packages-select lanelet2_core
colcon build --packages-select lanelet2_io
colcon build --packages-select lanelet2_maps 
colcon build --packages-select lanelet2_projection
colcon build --packages-select lanelet2_traffic_rules
colcon build --packages-select lanelet2_routing 
colcon build --packages-select lanelet2_validation
colcon build --packages-select waypoints_routing
colcon build --packages-select path_planning_dynamic
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
Inside of docker
```sh
source launch.sh --shell zsh
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
