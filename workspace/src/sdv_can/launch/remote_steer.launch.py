#!/usr/bin/env python3

from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='sdv_can',
            executable='scripts/remote2can.py',
        ),
        Node(
            package='joy',
            executable='joy_node',
        )
    ])