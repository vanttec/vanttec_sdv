import os
import launch
import launch
import launch.actions
import launch.events

import launch_ros
import launch_ros.actions
import launch_ros.events

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, Command
from launch_ros.actions import Node
from launch_ros.actions import LifecycleNode
import lifecycle_msgs.msg

def generate_launch_description():

    launch_dir = get_package_share_directory('sdv_launch')
    description_dir = get_package_share_directory('sdv_robot_description')
    parameter_file = LaunchConfiguration('params_file')
    xacro_path = os.path.join(description_dir, 'urdf', 'robot.urdf')

    params_declare = DeclareLaunchArgument(
        'params_file',
        default_value=os.path.join(
            launch_dir, 'config', 'lio_sam', 'params.yaml'),
        description='FPath to the ROS2 parameters file to use.')

    print("parameter file: {}".format(parameter_file))
    print("urdf_file_name : {}".format(xacro_path))

    robot_description = Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name='robot_state_publisher',
            output='screen',
            parameters=[{
                'robot_description': Command(['xacro', ' ', xacro_path])
            }]
        )
    
    localization_param_dir = launch.substitutions.LaunchConfiguration(
        'localization_param_dir',
        default=os.path.join(
            get_package_share_directory('sdv_launch'),
            'config',
            'localization.yaml'))
    
    lidar_localization = launch_ros.actions.LifecycleNode(
        name='lidar_localization',
        namespace='',
        package='lidar_localization_ros2',
        executable='lidar_localization_node',
        parameters=[localization_param_dir],
        remappings=[('/cloud','/velodyne_points'), ('/imu', '/vectornav/imu')],
        output='screen')
    
    to_inactive = launch.actions.EmitEvent(
        event=launch_ros.events.lifecycle.ChangeState(
            lifecycle_node_matcher=launch.events.matches_action(lidar_localization),
            transition_id=lifecycle_msgs.msg.Transition.TRANSITION_CONFIGURE,
        )
    )

    from_unconfigured_to_inactive = launch.actions.RegisterEventHandler(
        launch_ros.event_handlers.OnStateTransition(
            target_lifecycle_node=lidar_localization,
            goal_state='unconfigured',
            entities=[
                launch.actions.LogInfo(msg="-- Unconfigured --"),
                launch.actions.EmitEvent(event=launch_ros.events.lifecycle.ChangeState(
                    lifecycle_node_matcher=launch.events.matches_action(lidar_localization),
                    transition_id=lifecycle_msgs.msg.Transition.TRANSITION_CONFIGURE,
                )),
            ],
        )
    )

    from_inactive_to_active = launch.actions.RegisterEventHandler(
        launch_ros.event_handlers.OnStateTransition(
            target_lifecycle_node=lidar_localization,
            start_state = 'configuring',
            goal_state='inactive',
            entities=[
                launch.actions.LogInfo(msg="-- Inactive --"),
                launch.actions.EmitEvent(event=launch_ros.events.lifecycle.ChangeState(
                    lifecycle_node_matcher=launch.events.matches_action(lidar_localization),
                    transition_id=lifecycle_msgs.msg.Transition.TRANSITION_ACTIVATE,
                )),
            ],
        )
    )

    return LaunchDescription([
        params_declare,
        robot_description,
        from_unconfigured_to_inactive,
        from_inactive_to_active,
        lidar_localization,
        to_inactive,
        Node(
            package='lidar_imu_sync',
            executable='lidar_imu_fusion_node',
            name='lidar_imu_fusion_node',
            output='screen',
        )
    ])