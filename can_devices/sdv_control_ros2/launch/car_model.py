import os
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
           package='sdv_control_ros2',
           executable='car_simulation_node',
           namespace="",
           name='car_simulation_node_sdv',
        )
    ])