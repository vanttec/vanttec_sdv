import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, ExecuteProcess
from launch.substitutions import PathJoinSubstitution, LaunchConfiguration
from launch.launch_description_sources import PythonLaunchDescriptionSource

from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():

   car_params = os.path.join(
      get_package_share_directory('sdv_control'),
      'config',
      'car_guidance_control.yaml'
   )

   rviz_config = os.path.join(
      get_package_share_directory('sdv_control'),
      'launch/rviz_cfg',
      'nav.rviz'
   )

   vn_gps_params = os.path.join(
      get_package_share_directory('sdv_vectornav'),
      'config',
      'vn_gps_node_params.yaml'
   ) 

   frequency_arg = DeclareLaunchArgument(
      name='frequency',
      default_value='100',
      description='Frequency for nodes'
   )

   is_sim_arg = DeclareLaunchArgument(
      name='is_simulation',
      default_value='True'
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

    # Vectornav odometry and path
   start_odom_pub = Node(
      package='sdv_vectornav', 
      executable='vn_gps_pose',
      output='screen',
      parameters=[vn_gps_params]
   )

   car_control_node = Node(
      package='sdv_control',
      executable='sdc1_vel_pid_node',
      output='screen',
      name='sdc1_vel_pid_node',
      parameters=[{'frequency': LaunchConfiguration('frequency')},
                  car_params,
                  {'is_simulation': LaunchConfiguration('is_simulation')}
                  ]
   )

   car_guidance_node = Node(
      package='sdv_control',
      executable='stanley_controller_node',
      output='screen',
      name='stanley_controller_node',
      parameters=[{'frequency': LaunchConfiguration('frequency')},
                  car_params,
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
      arguments=['-d', rviz_config]
   )

   can_node = Node(
      package='sdv_control',
      executable='can_node.py',
      namespace="",
      output="screen",
      name='can_node',
      parameters=[{'channel': 'can0'},
                  {'bitrate': 125000}]
   )

   sdv_description_launch = IncludeLaunchDescription(
      PythonLaunchDescriptionSource([
            PathJoinSubstitution([
               FindPackageShare('sdv_description'),
               'launch',
               'rviz.launch.py'
            ])
      ])
   )

   return LaunchDescription([
      frequency_arg,
      is_sim_arg,
      # foxglove_launch,
      car_control_node,
      car_guidance_node,
      tf2_node,
      # can_node,
      # foxglove_studio,
      rviz,
      sdv_description_launch,
      start_odom_pub
   ])