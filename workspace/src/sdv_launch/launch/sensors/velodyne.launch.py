import os
import yaml

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import PathJoinSubstitution, LaunchConfiguration, PythonExpression
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.conditions import IfCondition, UnlessCondition, LaunchConfigurationEquals, LaunchConfigurationNotEquals

import launch_ros
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    simulation = DeclareLaunchArgument(
       'simulation',
       default_value = 'false',
       description = 'Defines if the application will run in simulation'
    )

    tf_base_link_velodyne = Node(
       package='tf2_ros',
       executable='static_transform_publisher',
       name="tf_base_link_to_velodyne",
       arguments = ['0', '0', '1.8', '-0.174533', '0.0', '0.0', 'base_link', 'velodyne'],  #-0.05 y
       condition=UnlessCondition(LaunchConfiguration('simulation'))
    )

    sdv_launch_dir = get_package_share_directory('sdv_launch')
    velodyne_config_dir = os.path.join(sdv_launch_dir, 'config', 'velodyne')

    velodyne_driver_params_file = os.path.join(velodyne_config_dir, 'VLP32C-velodyne_driver_node-params.yaml')
    velodyne_driver_node = launch_ros.actions.Node(package='velodyne_driver',
                                                   executable='velodyne_driver_node',
                                                   output='both',
                                                   parameters=[velodyne_driver_params_file])

    transform_node_params_file = os.path.join(velodyne_config_dir, 'VLP32C-velodyne_transform_node-params.yaml')
    with open(transform_node_params_file, 'r') as f:
        transform_node_params = yaml.safe_load(f)['velodyne_transform_node']['ros__parameters']
    transform_node_params['calibration'] = os.path.join(velodyne_config_dir, '32db.yaml')
    velodyne_transform_node = launch_ros.actions.Node(package='velodyne_pointcloud',
                                                      executable='velodyne_transform_node',
                                                      output='both',
                                                      parameters=[transform_node_params])

    laserscan_params_file = os.path.join(velodyne_config_dir, 'default-velodyne_laserscan_node-params.yaml')
    velodyne_laserscan_node = launch_ros.actions.Node(package='velodyne_laserscan',
                                                    executable='velodyne_laserscan_node',
                                                    output='both',
                                                    parameters=[laserscan_params_file])

    ld = LaunchDescription()
    ld.add_action(simulation)
    ld.add_action(tf_base_link_velodyne)
    ld.add_action(velodyne_driver_node)
    ld.add_action(velodyne_transform_node)
    ld.add_action(velodyne_laserscan_node)
    return ld
