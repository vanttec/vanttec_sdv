# LIDAR IMU Calibration Instructions

Mostly from https://autowarefoundation.github.io/autoware-documentation/release-v1.0_beta/how-to-guides/integrating-autoware/creating-vehicle-and-sensor-model/calibrating-sensors/lidar-imu-calibration/

1. Split ros2 bag into bag with only `/velodyne_points` and `/vectornav/imu` topics:
```
ros2 bag convert -i <YOUR-ROS2-BAG-FOLDER> -o out.yaml
```
2. Convert into ros1 bag with
```
rosbags-convert <YOUR-SPLITTED-ROS2-BAG-FOLDER> --dst <OUTPUT-BAG-FILE>.bag
```
3. Run `start_oalicalib.sh`, build OALiCalib
```
cd /root/catkin_oa_calib
catkin_make -DCATKIN_WHITELIST_PACKAGES=""
source /devel/setup.bash
```
4. Modify `OA-LICalib/config/simu.yaml`, check `start_time` and `end_time`
5. Run with `roslaunch oa_licalib li_calib.launch`
