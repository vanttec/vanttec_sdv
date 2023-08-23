import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch.launch_description_sources import PythonLaunchDescriptionSource

from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():

   car_params = os.path.join(
      get_package_share_directory('sdv_control'),
      'config',
      'car_params.yaml'
   )

   rviz_config = os.path.join(
      get_package_share_directory('sdv_control'),
      'launch/rviz_cfg',
      # 'nav.rviz'
      # 'sdv_parking_wpnts.rviz'
      'sdv_sim_wpnts.rviz'
   )

   vn_gps_params = os.path.join(
      get_package_share_directory('sdv_vectornav'),
      'config',
      'vn_gps_node_params.yaml'
   )

   # 'send_buffer_limit': '50000000',
   # 'num_threads': '4'

    # Vectornav odometry and path
   # start_odom_pub = Node(
   #    package='sdv_vectornav', 
   #    executable='vn_gps_pose',
   #    output='screen',
   #    parameters=[vn_gps_params]
   # )

   car_control_node = Node(
      package='sdv_control',
      executable='sdc1_vel_pid_node',
      output='screen',
      name='sdc1_vel_pid_node',
      parameters=[
                  # {'frequency': LaunchConfiguration('frequency')},
                  # {'is_simulation': LaunchConfiguration('is_simulation')},
                  car_params
                  ]
   )

   car_guidance_node = Node(
      package='sdv_control',
      executable='stanley_controller_node',
      output='screen',
      name='stanley_controller_node',
      parameters=[
                  # {'frequency': LaunchConfiguration('frequency')},
                  # {'is_simulation': LaunchConfiguration('is_simulation')},
                  car_params
                  ]
   )

   tf2_node = Node(
      package='sdv_control',
      executable='car_tf2_broadcast_node',
      namespace="",
      name='car_tf2_broadcast_node',
      parameters=[
                  # {'frequency': LaunchConfiguration('frequency')},
                  car_params
                  ]
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

   waypoint_handler = Node(
      package='sdv_control',
      executable='waypoint_handler.py',
      namespace="",
      output="screen",
      name='waypoint_handler',
      parameters=[
                  car_params
                  ]
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

   sdv_loc_launch = IncludeLaunchDescription(
      PythonLaunchDescriptionSource([
            PathJoinSubstitution([
               FindPackageShare('sdv_vectornav'),
               'launch',
               'sdv_tf.launch.py'
            ])
      ])
   )

   return LaunchDescription([
      waypoint_handler,
      car_control_node,
      car_guidance_node,
      tf2_node,
      # can_node,
      rviz,
      sdv_description_launch,
      sdv_loc_launch
   ])