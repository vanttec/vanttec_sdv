import os
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():

   frequency_arg = DeclareLaunchArgument(
      name='frequency',
      default_value='100',
      description='Frequency for nodes'
   )

   pid_gains = os.path.join(
      get_package_share_directory('sdv_control'),
      'config',
      'VTec_SDC1_PID_Gains.yaml'
   )

   car_control_node = Node(
      package='sdv_control',
      executable='sdc1_vel_control_node',
      output='screen',
      name='sdc1_vel_control_node',
      parameters=[{'frequency': LaunchConfiguration('frequency')},
                  pid_gains]
   )

   tf2_node = Node(
      package='sdv_control',
      executable='car_tf2_broadcast_node',
      namespace="",
      name='car_tf2_broadcast_node',
      parameters=[{'frequency': LaunchConfiguration('frequency')}]
   )

   rviz = Node(
      package='rviz2',
      executable='rviz2',
      name='rviz2',
      # arguments=['-d', rviz_config]
   )

   return LaunchDescription([
      frequency_arg,
      car_control_node,
      tf2_node,
      # rviz
   ])