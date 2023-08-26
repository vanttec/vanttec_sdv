import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch.launch_description_sources import PythonLaunchDescriptionSource

from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():

   can_params = os.path.join(
      get_package_share_directory('sdv_can'),
      'config',
      'can_params.yaml'
   )

   # can_node = Node(
   #    package='sdv_can',
   #    executable='can_node.py',
   #    namespace="can_devices",
   #    output="screen",
   #    name='can_node',
   #    parameters=[can_params]
   # )

   encoder_node = Node(
      package='sdv_can',
      executable='encoder_rm8004.py',
      namespace="can_devices",
      output='screen',
      name='encoder_rm8004',
      parameters=[can_params]
   )

   xbox_node = Node(
      package='sdv_can',
      executable='xbox_node.py',
      namespace="can_devices",
      output='screen',
      name='xbox_node',
      # Launch the node with root access (GPIO) in a shell
      prefix=["sudo -E env \"PYTHONPATH=$PYTHONPATH\" \"LD_LIBRARY_PATH=$LD_LIBRARY_PATH\" \"PATH=$PATH\" \"USER=$USER\"  bash -c "],
      shell=True
   )

   return LaunchDescription([
      xbox_node,
      # can_node,
      encoder_node
   ])