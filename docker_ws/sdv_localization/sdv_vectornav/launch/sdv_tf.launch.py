import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

from launch_ros.actions import Node

def generate_launch_description():

    this_dir = get_package_share_directory('sdv_vectornav')
    
    # Vectornav odometry and path
    start_odom_pub = Node(
        package='sdv_vectornav', 
        executable='vn_gps_pose',
        output='screen',
        parameters=[os.path.join(this_dir, 'config', 'vn_gps_node_params.yaml')])
    

    #ODOM is in NED frame since vn measurements are in that configuration, so the rotation from NED to ENU for MAP is necessary
    start_transform_odom_base_link = Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name="tf_map_to_odom",
            arguments = ['0', '0', '0', '0', '0', '-3.14159', 'map', 'odom']) #x, y, z, yaw, pitch, roll 

    # Create the launch description and populate
    ld = LaunchDescription()

    ld.add_action(start_odom_pub)
    ld.add_action(start_transform_odom_base_link)
    return ld