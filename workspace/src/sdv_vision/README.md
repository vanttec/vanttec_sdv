# sdv_vision - Perception Module 

This package, ```sdv_vision```, provides functionality for sdv assistance, including lane detection, people distance detection, and video publishing for testing purposes.

![vision_dashboard](https://github.com/vanttec/vanttec_sdv/blob/features/vision/workspace/src/sdv_vision/git_imgs/vision_dashboard.png)

## Installation

### Cloning the repo

To install this package, clone the ``` vanttec_sdv ``` repository (include the submodules), go to the vision branch and build it using colcon build:
Make sure that your Git-hub token have all the permissions to clone submodules.


```bash
git clone --recurse-submodules -b features/vision https://github.com/vanttec/vanttec_sdv.git 
cd vanttec_sdv/workspace
git checkout features/vision
colcon build --symlink-install
```
### Download Foxglove

Follow the newt Tutorial to install [Foxglove]: (https://foxglove.dev/download)

## Deployment

Requirements, to be located in ```vanttec_sdv/workspace``` and source every terminal.

```bash
source install/setup.bash
```

**Terminal 1** : Launch Foxglove

Open the Foxglove Studio, click ```Open connection```, then click  ```open```. Then launch Foxglove.


```bash
ros2 launch foxglove_bridge foxglove_bridge_launch.xml
```

For the next step, there are two ways to deploy the results.

### Testing with video frames

**Terminal 2** : Launch the ```vision_testing.launch.py```

```bash
ros2 launch sdv_vision vision_testing.launch.py
```

### Deploy with Multisense

**Terminal 2** : Camera setup

We use a bash script [multisense.sh](https://github.com/vanttec/vanttec_sdv/blob/features/vision/workspace/multisense.sh) that configures the network interface where the Multisense Ethernet is connected (Jetson, personal laptop, etc) with the IP address of the camera ```10.66.171.20```.

**Important!** The identifier (ID) of the network interface may vary depending on the specific device being used. You can determine the correct ID by using the `ifconfig` command, which provides information about network interfaces currently available on the system.

```bash
cd vanttec_sdv/workspace
sudo ./multisense.sh
```


**Terminal 3** : Launch the ```vision.launch.py``` (note: this launch is not finished yet)

```bash
ros2 launch sdv_vision vision.launch.py
```

## Usage

### Lane Detection

The `lane_detection` script implements an algorithm to determine the state of the vehicle on a lane, whether it's aligned, misaligned, or in emergency misalignment.

```bash
ros2 run autonomous_vehicle_assistance lane_detection
```

### People Distance Detection

The `people_distance_detection` script utilizes YOLOv8 pose detection model to detect people and determine their distance from the vehicle. It also assesses whether the distance is dangerous or requires caution.

```bash
ros2 run autonomous_vehicle_assistance people_distance_detection
```

### Video Publisher

The `video_pub` script publishes video frames for testing purposes.

```bash
ros2 run autonomous_vehicle_assistance video_pub
```

## Architecture

![rqt_graph](https://github.com/vanttec/vanttec_sdv/blob/features/vision/workspace/src/sdv_vision/git_imgs/rqt_graph_vision.png)


## Nodes

| Name             | Description                                                                |
| ----------------- | ------------------------------------------------------------------ |
| [_lane_detection_](https://github.com/vanttec/vanttec_sdv/blob/features/vision/workspace/src/sdv_vision/yolov8_lane_detection/lane_detection.py) | Determines the vehicle's lane state. |
| [_people_distance_detection_](https://github.com/vanttec/vanttec_sdv/blob/features/vision/workspace/src/sdv_vision/yolov8_object_detection/people_distance_detection.py) | Detects people and assesses their distance from the vehicle. |
| [_video_pub_](https://github.com/vanttec/vanttec_sdv/blob/features/vision/workspace/src/sdv_vision/yolov8_lane_detection/video_pub.py) | Publishes video frames for testing. |


## Parameters

### Lane Detection
| Name | Datatype | Default Value | Description |
| ---- | -------- | ----------- | ----------- |
| _model_file_ | string_value | best_feb2024_FINSA.pt | Specifies the file name of the YOLOv8 model used for lane detection. The file must be in the ``Ỳolov8/weights``` directory. |
| _center_class_ | integer_value | 0 | Determines the class index used for center lane path within the YOLOv8 model. |
| _error_threshold_ | integer_array_value | [9,13] | Defines the threshold range for the error in center point detection. It is a list of integers representing minimum and maximum thresholds. If the error exceeds the maximum threshold, a collision risk is detected, and if it falls within the range, a caution warning is issued. |
| _center_point_ | integer_array_value | [590,500] | Specifies the reference center point for comparison with the detected lane center points. It is a list of integers representing the (x, y) coordinates of the reference point. Default values are [590, 500]. The node compares the detected lane center points with this reference point to determine the error. |


### People Distance Detection
| Name | Datatype | Default Value | Description |
| ---- | -------- | ------------- | ----------- |
| _model_file_ | string_value | yolov8n-pose.pt | Specifies the file name of the YOLOv8 model used for people detection. |
| _detection_mode_ | string_value | detection | Determines the mode of operation for the node, either "calibration" or "detection". When set to "calibration", the node calibrates the focal length of the camera, and when set to "detection", it performs distance detection based on the calibrated parameters. |
| _calibration_distance_ | double_value | 2.0 | Specifies the known distance used for calibration in meters, representing the distance between the person and the camera during calibration. |
| _calibration_person_width_ | double_value | 0.38 | Specifies the width of the person used for calibration in meters, representing the shoulder-to-shoulder width of the person. |
| _caution_distances_ | double_array_value | [1.5, 3.0] | Defines the distance thresholds for the caution and warning zones. It is a list of double values representing the minimum and maximum distances for these zones. The first value represents the danger zone, and the second value represents the warning zone. |

### Video Publisher
| Name | Datatype | Default Value | Description |
| ---- | -------- | ------------- | ----------- |
| _video_output_ | string_value | carril.mp4 | Specifies the file name of the video file to be published. The file must be located in the package's `data/test_videos` directory. |


## Topics

### Lane Detection 
| Topic | Message Type | Description | Publisher/Subscriber |
| ----- | ------------ | ----------- | -------------------- |
| `/lane_video_frames` | `sensor_msgs/Image` | Frames from the multisense camera/ or a video used for lane detection. | Subscriber |
| `/processed_video_frames` | `sensor_msgs/Image` | Processed frames with detected lanes. | Publisher |
| `/lane_detection_video` | `sensor_msgs/Image` | Frames with lane detection overlay. | Publisher |
| `/lane_detection_flag` | `std_msgs/Int32` | Flag indicating the detection status (collision risk, caution, or aligned). | Publisher |
| `/lane_detection_error` | `std_msgs/Int32` | Error value indicating the deviation from the center point of the lane. | Publisher |

### People Distance Detection 
| Topic | Message Type | Description | Publisher/Subscriber |
| ----- | ------------ | ----------- | -------------------- |
| `/people_video_frames` | `sensor_msgs/Image` | Frames from the multisense camera used for people detection. | Subscriber |
| `/people_distance_detection_video` | `sensor_msgs/Image` | Frames with people detection and distance information overlay. | Publisher |
| `/people_distance_detections_flag` | `std_msgs/Int32` | Flag indicating the detection status (danger, warning, or safe). | Publisher |


### Video Publisher 
| Topic | Message Type | Description | Publisher/Subscriber |
| ----- | ------------ | ----------- | -------------------- |
| `/video_frames` | `sensor_msgs/Image` | Frames from the video stream to be published. | Publisher |

## Launch Files
### [vision_testing.launch.py](https://github.com/vanttec/vanttec_sdv/blob/features/vision/workspace/src/sdv_vision/launch/vision_testing.launch.py)
This file is used to launch the vision nodes for testing purposes. The nodes launched are:
- video_publisher (2 instances)
- lane_detection
- people_distance_detections

### [vision.launch.py](https://github.com/vanttec/vanttec_sdv/blob/features/vision/workspace/src/sdv_vision/launch/vision.launch.py) (note: this launch is not finished yet)
This launch file is designed to initiate the vision-related nodes for real-time execution in the system, assuming an incoming image stream from the Multisense camera. The nodes launched are:
- lane_detection
- people_distance_detections

## Dependencies

- OpenCV
- ROS2 (Humble)
- Foxglove Studio (for dashboard visualization)

## Contact

For inquiries, issues, or suggestions, please contact [Frida Cano](fcanof.16@gmail.com).
