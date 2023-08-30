import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import PathJoinSubstitution, LaunchConfiguration
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument
from launch.launch_description_sources import PythonLaunchDescriptionSource

from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

from launch.conditions import UnlessCondition

def generate_launch_description():

    is_simulation = DeclareLaunchArgument(
      'is_simulation',
      default_value = 'false',
      description = 'Defines if the application will run in simulation or in real life'
    )

    rviz_config = os.path.join(
        get_package_share_directory('sdv_localization'),
        'launch/rviz_cfg',

        # For real life tests
        # 'sdv_anniversary.rviz'
        # 'sdv_parking_lot_cetec2.rviz'
        'sdv_parking_lot_cetec.rviz'
    )

    # Vectornav, SBG and TF config
    sdv_loc_launch = IncludeLaunchDescription(
      PythonLaunchDescriptionSource([
            PathJoinSubstitution([
                FindPackageShare('sdv_localization'),
                'launch',
                'sdv_localization.launch.py'
            ])
      ]),
    )

    rviz = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        arguments=['-d', rviz_config]
    )

    ld = LaunchDescription()

    ld.add_action(is_simulation)
    ld.add_action(sdv_loc_launch)
    ld.add_action(rviz)
    return ld