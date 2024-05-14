'''
    This file is used to launch the vision nodes for testing purposes.
    The nodes launched are: 
        - video_publisher (2 instances)
        - lane_detection
        - people_distance_detections
'''
from launch import LaunchDescription
from launch_ros.actions import Node
import os
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():

    pkg_dir = get_package_share_directory('sdv_vision')

    # Video Node - Lane Detection
    video_lane_node = Node(
            package='sdv_vision',
            namespace='vision',
            executable='video_publisher',
            name='video_lane',
            parameters=[{
                "video_output" : 'carril.mp4'
            }],
            remappings=[
                ('/video_frames', '/lane_video_frames'),
            ]
        )
    # Video Node - People Detection
    video_people_node = Node(
            package='sdv_vision',
            namespace='vision',
            executable='video_publisher',
            name='video_object',
            parameters=[{
                "video_output" : '3_personas.mp4',
            }],
            remappings=[
                ('/video_frames', '/people_video_frames'),
            ]
        )
    
    # LANE DETECTION NODE
    lane_node = Node(
            package='sdv_vision',
            namespace='vision',
            executable='lane_detection',
            name='lane_detection',
            parameters=[{
                "model_file" : 'best_feb2024_FINSA.pt', # Model file to use. For FINSA model, use 'best_feb2024_FINSA.pt', for Campus model, use 'best_CampusSeg.pt'
                "center_class" : 0, # Class to use for center detection. For FINSA model, use 0, for Campus model, use 1
                "error_threshold" : [9,13], # Error threshold for the center point detection. [caution, warning]
                "center_point" : [590, 500] # Center point of the image
            }],
        )
    
    # PEOPLE DETECTION NODE
    people_node = Node(
            package='sdv_vision',
            namespace='vision',
            executable='people_distance_detection',
            name='people_distance_detection',
            parameters=[{
                "detection_mode" : 'detection', # Detection mode (calibration or detection)
                "calibration_distance" : 2.0, # Distance of calibration in meters (person2camera)
                "calibration_person_width" : 0.38, # Distance of person width in meters (shoulder2shoulder)
                "model_file": 'yolov8n-pose.pt', # Model file to use
                "caution_distances" : [1.5,2.0] # Distance thresholds for the caution and warning zones. [danger, warning]
            }],
        )
    return LaunchDescription([
        lane_node,
        people_node,
        video_lane_node,
        video_people_node
    ])
