## 1. Installation

### Prerequisites (Ubuntu/Debian/ros)

```bash
sudo apt install ros-$ROS_DISTRO-joint-state-publisher-gui
sudo apt install ros-$ROS_DISTRO-xacro
sudo apt-get install ros-$ROS_DISTRO-pcl-ros
sudo apt install ros-$ROS_DISTRO-vision-msgs
sudo apt install ros-$ROS_DISTRO-perception-pcl
sudo apt install ros-$ROS_DISTRO-pcl-msgs
sudo apt install ros-$ROS_DISTRO-vision-opencv
sudo apt install ros-$ROS_DISTRO-xacro
sudo apt install ros-$ROS_DISTRO-velodyne-msgs
sudo apt install ros-$ROS_DISTRO-diagnostic-updater
#sudo apt install ros-$ROS_DISTRO-lanelet2 (no longer required because in the repo is a custom repo)
sudo apt install ros-$ROS_DISTRO-color-util
sudo apt-get install -y libpcap-dev
```

Install required GStreamer packages:

```bash
sudo apt update
sudo apt install -y \
  gstreamer1.0-tools \
  gstreamer1.0-libav \
  gstreamer1.0-plugins-base \
  gstreamer1.0-plugins-good \
  gstreamer1.0-plugins-bad \
  gstreamer1.0-plugins-ugly
```

Install V4L2 utilities:

```bash
sudo apt update
sudo apt install -y v4l-utils
```

Install OpenCV (system package):

```bash
pip3 uninstall -y opencv-python opencv-contrib-python opencv-python-headless
sudo apt update
sudo apt install -y python3-opencv

sudo apt-get update
sudo apt-get install -y pkg-config libturbojpeg0-dev
```

## Using the LiDAR
1 - First you need to go to setting on your laptop, then Network > cable umpluged > ipV4 > Manual:

- Addresses: 192.168.17.251

- Netmask: 255.255.255.0

Then run this bash script:

```bash
sudo ip addr add 192.168.1.100/24 dev enp2s0
sudo ip link set enp2s0 up
```

>(You can change the "esp2s0" to other like "esp3s0" check with ifconfig the port of your internet)

### Example:
```bash
enp3s0: flags=4099<UP,BROADCAST,MULTICAST>  mtu 1500
        inet 192.168.1.100  netmask 255.255.255.0  broadcast 0.0.0.0
        ether 50:eb:f6:49:45:7e  txqueuelen 1000  (Ethernet)
        RX packets 1974079  bytes 2328331084 (2.3 GB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 1645  bytes 547882 (547.8 KB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
```


## Device Detection

List available video devices:

```bash
find /dev -maxdepth 1 -name "video*"
```

## Disable Autofocus and Set Manual Focus

```bash
# 1) Turn OFF continuous autofocus
v4l2-ctl -d /dev/video0 -c focus_automatic_continuous=0
v4l2-ctl -d /dev/video2 -c focus_automatic_continuous=0
v4l2-ctl -d /dev/video4 -c focus_automatic_continuous=0
v4l2-ctl -d /dev/video6 -c focus_automatic_continuous=0
v4l2-ctl -d /dev/video8 -c focus_automatic_continuous=0


# 2) Set a fixed manual focus value (range: 0-100)
v4l2-ctl -d /dev/video0 -c focus_absolute=10
v4l2-ctl -d /dev/video2 -c focus_absolute=10
v4l2-ctl -d /dev/video4 -c focus_absolute=10
v4l2-ctl -d /dev/video6 -c focus_absolute=10
v4l2-ctl -d /dev/video8 -c focus_absolute=10

```

## → run the cameras:

```
ros2 launch obsbot_multicamera.launch.py
```

## → Sensor Launchers

Launch individual or combined sensor configurations as needed:

- For LiDAR only:

```bash
ros2 launch sensors_launch velodyne-VLP32C-launch.py
```

- For LiDAR and IMU combined:

```bash
ros2 launch sensors_launch lidar_imu.launch.py
```

## record rosbag mcap

```bash
ros2 bag record --storage mcap --all --output vanttec_sdv_localization_20250623
```

## play a ros bag

```bash
rviz2 -d /workspace/navpilot_ws/src/localization_modules/launch/localization.rviz

ros2 bag play vanttec_sdv_localization_20250623 -s mcap



```
