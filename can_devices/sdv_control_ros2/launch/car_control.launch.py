import os
import launch
from launch import LaunchDescription
from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument
from launch_ros.actions import Node
def generate_launch_description():

   # Create Launch Configuration Variables
   role_name = LaunchConfiguration('role_name')
   
   # Define Launch Arguments
   declare_role_name = DeclareLaunchArgument('role_name', default_value='vanttec_vehicle')

   # Define Actions
   start_sdv_control = Node(
      package='sdv_control_ros2',
      executable='car_control_node',
      name=['sdv_control_', role_name],
      output='screen',
      emulate_tty=True,
      parameters=[{'role_name': role_name}])
   start_car_simulation_node = Node(
      package='sdv_control_ros2',
      executable='car_simulation_node',
      namespace="",
      name='car_simulation_node_sdv',)
   start_car_tf2_broadcast_node_sdv = Node(
      package='sdv_control_ros2',
      executable='car_tf2_broadcast_node',
      namespace="",
      name='car_tf2_broadcast_node_sdv',)

   # Create launch description
   ld = launch.LaunchDescription()

   # Declare launch options
   ld.add_action(declare_role_name)

   # Add actions
   ld.add_action(start_sdv_control)
   ld.add_action(start_car_simulation_node)
   ld.add_action(start_car_tf2_broadcast_node_sdv)
   
   return ld  
