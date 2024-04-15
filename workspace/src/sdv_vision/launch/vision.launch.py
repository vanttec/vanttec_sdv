from launch import LaunchDescription
from launch_ros.actions import Node
import os
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    pkg_dir = get_package_share_directory('sdv_vision')
    
    lane_detection_params_path = os.path.join(pkg_dir, 'config', 'lane_detection_params.yaml')
    person_detection_params_path = os.path.join(pkg_dir, 'config', 'person_distance_detection_params.yaml')
    
    return LaunchDescription([
        Node(
            package='sdv_vision',
            namespace='vision',
            executable='lane_detection',
            name='lane_detection',
            parameters=[lane_detection_params_path]
        ),
        Node(
            package='sdv_vision',
            namespace='vision',
            executable='object_detection',
            name='object_detection',
            parameters=[person_detection_params_path]
        )
    ])
