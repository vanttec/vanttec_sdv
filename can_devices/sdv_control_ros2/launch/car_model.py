import os
from launch import LaunchDescription
from launch.substitutions import Command, LaunchConfiguration
import launch_ros
import launch
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from launch_ros.descriptions import ParameterValue 
def generate_launch_description():
   pkg_share = launch_ros.substitutions.FindPackageShare(package='sdv_control_ros2').find('sdv_control_ros2')
   default_model_path = os.path.join(pkg_share, 'models/el_rasho.urdf')
   default_rviz_config_path = os.path.join(pkg_share, 'launch/rviz_cfg/sdv.rviz')
   robot_desc_path = os.path.join(get_package_share_directory("sdv_control_ros2"), "models", "el_rasho.urdf")
   
   robot_state_publisher_node = launch_ros.actions.Node(
      package='robot_state_publisher',
      executable='robot_state_publisher',
      parameters=[{'robot_description': ParameterValue(Command(['xacro ', robot_desc_path]), value_type=str)}]
   )
   joint_state_publisher_node = launch_ros.actions.Node(
      package='joint_state_publisher',
      executable='joint_state_publisher',
      name='joint_state_publisher',
      condition=launch.conditions.UnlessCondition(LaunchConfiguration('gui'))
   )
   joint_state_publisher_gui_node = launch_ros.actions.Node(
      package='joint_state_publisher_gui',
      executable='joint_state_publisher_gui',
      name='joint_state_publisher_gui',
      condition=launch.conditions.IfCondition(LaunchConfiguration('gui'))
   )
   rviz_node = launch_ros.actions.Node(
      package='rviz2',
      executable='rviz2',
      name='rviz2',
      output='screen',
      arguments=['-d', LaunchConfiguration('rvizconfig')],
   )
   return LaunchDescription([
      launch.actions.DeclareLaunchArgument(name='gui', default_value='True',
                                          description='Flag to enable joint_state_publisher_gui'),
      launch.actions.DeclareLaunchArgument(name='model', default_value=default_model_path,
                                          description='Absolute path to robot urdf file'),
      launch.actions.DeclareLaunchArgument(name='rvizconfig', default_value=default_rviz_config_path,
                                          description='Absolute path to rviz config file'),
      joint_state_publisher_node,
      joint_state_publisher_gui_node,
      robot_state_publisher_node,
      #rviz_node,
      Node(
         package='sdv_control_ros2',
         executable='car_simulation_node',
         namespace="",
         name='car_simulation_node_sdv',
      ),
      Node(
         package='sdv_control_ros2',
         executable='car_tf2_broadcast_node',
         namespace="",
         name='car_tf2_broadcast_node_sdv',
      )
   ])

    