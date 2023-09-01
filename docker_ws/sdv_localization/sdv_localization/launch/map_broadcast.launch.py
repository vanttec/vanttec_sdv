import os
from launch import LaunchDescription
from ament_index_python.packages import get_package_share_directory
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare



def generate_launch_description():
    sdv_localization = FindPackageShare(package='sdv_localization').find('sdv_localization')

    start_map_broadcaster =  Node(
            package='nav2_map_server', 
            executable='map_server',
            parameters=[
                {'yaml_filename': os.path.join(sdv_localization, 'maps', 'raw_map.yaml')},
                {'topic_name': 'amcl_map'},   # Change topic_name to map2
                {'frame_id': 'amcl_map'}      # Change frame_id to map2]
            ],
            name='map_server_raw_map',
            output='screen'
        )


    start_lifecycle_manager = Node(
            package='nav2_lifecycle_manager',
            executable='lifecycle_manager',
            name='lifecycle_manager_mapper',
            output='screen',
            parameters=[{'use_sim_time': False},
                        {'autostart': True},
                        {'node_names': ['map_server_raw_map']}]
        )



    ld = LaunchDescription()

    ld.add_action(start_map_broadcaster)
    ld.add_action(start_lifecycle_manager)
    return ld

