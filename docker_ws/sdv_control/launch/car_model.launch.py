from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import TextSubstitution, LaunchConfiguration

def generate_launch_description():

   nodes_frequency = DeclareLaunchArgument(
      name='frequency',
      default_value=TextSubstitution(text='100')
   )

   return LaunchDescription([
      nodes_frequency,

      # launch_ros.actions.Node(
      #    package='sdv_manual_control',
      #    executable='sdv_manual_control',
      #    name=['sdv_manual_control', launch.substitutions.LaunchConfiguration('role_name')],
      #    output='screen',
      #    emulate_tty=True,
      #    parameters=[
      #          {
      #             'role_name': launch.substitutions.LaunchConfiguration('role_name')
      #          }
      #    ]
      # ),

      Node(
         package='sdv_control',
         executable='sdc1_simulation_node',
         namespace="",
         name='sdc1_simulation_node',
         parameters=[{
            'frequency': LaunchConfiguration('frequency')
         }]
      ),

      # Node(
      #    package='sdv_control',
      #    executable='car_tf2_broadcast_node',
      #    namespace="",
      #    name='car_tf2_broadcast_node',
      #    parameters=[{
      #       'frequency': LaunchConfiguration('frequency')
      #    }]
      # )
   ])

    