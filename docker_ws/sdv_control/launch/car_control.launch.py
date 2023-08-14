import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, ExecuteProcess
from launch.substitutions import PathJoinSubstitution, LaunchConfiguration
from launch.launch_description_sources import PythonLaunchDescriptionSource

from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():

   pid_gains = os.path.join(
      get_package_share_directory('sdv_control'),
      'config',
      'VTec_SDC1_PID_Gains.yaml'
   )

   frequency_arg = DeclareLaunchArgument(
      name='frequency',
      default_value='100',
      description='Frequency for nodes'
   )

   is_sim_arg = DeclareLaunchArgument(
      name='is_simulation',
      default_value='False'
   )

   # foxglove_launch = IncludeLaunchDescription(
   #    PythonLaunchDescriptionSource([
   #       PathJoinSubstitution([
   #          FindPackageShare('foxglove_bridge'),
   #          'launch/foxglove_bridge_launch.xml'
   #       ])
   #    ]),
   #    launch_arguments = {
   #       'send_buffer_limit': '50000000',
   #       'num_threads': '4'
   #    }.items()
   # )

   # foxglove_studio = ExecuteProcess(cmd=["foxglove-studio"])

   car_control_node = Node(
      package='sdv_control',
      executable='sdc1_vel_control_node',
      output='screen',
      name='sdc1_vel_control_node',
      parameters=[{'frequency': LaunchConfiguration('frequency')},
                  pid_gains,
                  # {'is_simulation': True}
                  {'is_simulation': LaunchConfiguration('is_simulation')}
                  ]
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
      is_sim_arg,
      # foxglove_launch,
      car_control_node,
      tf2_node,
      # foxglove_studio
      # rviz
   ])