import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription, ExecuteProcess

def generate_launch_description():

    sdv_launch = get_package_share_directory('sdv_launch')

    velodyne_launch = IncludeLaunchDescription(
      PythonLaunchDescriptionSource([
            PathJoinSubstitution([
               sdv_launch,
               'launch',
               'sensors',
               'velodyne.launch.py'
            ])
      ])
   )

   vectornav_launch = IncludeLaunchDescription(
      PythonLaunchDescriptionSource([
            PathJoinSubstitution([
               sdv_launch,
               'launch',
               'sensors',
               'vectornav.launch.py'
            ])
      ])
   )

   rosbag_exec = ExecuteProcess(
    cmd=['ros2', 'bag', 'record', '-a'], output='screen'
   )
    
   ld = LaunchDescription()

   ld.add_action(velodyne_launch)
   ld.add_action(vectornav_launch)
   ld.add_action(rosbag_exec)

   return ld`
