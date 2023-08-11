import os
from launch import LaunchDescription
from launch.substitutions import Command, LaunchConfiguration
import launch_ros
import launch
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from launch_ros.descriptions import ParameterValue 
def generate_launch_description():

   return LaunchDescription([
      launch.actions.DeclareLaunchArgument(
                  name='role_name',
                  default_value='vanttec_vehicle'
            ),
       launch_ros.actions.Node(
            package='sdv_manual_control',
            executable='sdv_manual_control',
            name=['sdv_manual_control_', launch.substitutions.LaunchConfiguration('role_name')],
            output='screen',
            emulate_tty=True,
            parameters=[
                {
                    'role_name': launch.substitutions.LaunchConfiguration('role_name')
                }
            ]
        ),
      Node(
         package='sdv_control',
         executable='car_simulation_node',
         namespace="",
         name='car_simulation_node_sdv',
      ),
      Node(
         package='sdv_control',
         executable='car_tf2_broadcast_node',
         namespace="",
         name='car_tf2_broadcast_node_sdv',
      )
   ])

    