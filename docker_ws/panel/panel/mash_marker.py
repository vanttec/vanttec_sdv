#! /usr/bin/env python
# by Hortencia Alejandra Ramirez Vazquez

import rclpy
from rclpy.node import Node
from rclpy.time import Time

from visualization_msgs.msg import Marker
from std_msgs.msg import String

from ament_index_python.packages import get_package_share_directory

class Mesh_Marker(Node):
    def __init__(self):
        #node name
        super().__init__('mesh_marker')
        #publishers
        self.marker_pub = self.create_publisher(Marker, '/model_3d', 2)
        #subscribers
        self.name_object_subscription = self.create_subscription(String,'name_object',self.name_object_cb,10)
        self.name_object_subscription  # prevent unused variable warning


        self.marker = Marker()
        self.marker.header.frame_id = "base_link"
        self.marker.header.stamp = self.get_clock().now().to_msg()
        self.marker.ns = ""

        # Shape (mesh resource type - 10)
        self.marker.type = 10
        self.marker.id = 0
        self.marker.action = 0

    def timer_callback(self):
        self.marker_pub.publish(self.marker)

    def name_object_cb(self, msg):

        #testing
        self.object = {
            "cat": "/3d_models/cat.gltf",
            "tree1": "/3d_models/arbolito1.gltf",
            "tree2": "/3d_models/arbolito2.gltf",
            "tree3": "/3d_models/arbolito3.gltf",
            "bench": "/3d_models/banquita.gltf",
            "human1": "/3d_models/human1.gltf",
            "duck": "/3d_models/patito.gltf"
        }

         # Get the package path
        package_name = "panel"
        self.package_path = get_package_share_directory(package_name).replace("/share/" + package_name, "").replace("install", "src")

        self.get_logger().info('Object: "%s"' % msg.data)
        
        # Note: Must set mesh_resource to a valid URL for a model to appear
        #self.marker.mesh_resource = self.object[msg.data]
        self.marker.mesh_resource = self.package_path + self.object[msg.data]
        print(self.marker.mesh_resource)
        self.marker.mesh_use_embedded_materials = True

        # Scale
        self.marker.scale.x = 10.0
        self.marker.scale.y = 10.0
        self.marker.scale.z = 10.0

        # Color
        self.marker.color.r = 0.0
        self.marker.color.g = 0.0
        self.marker.color.b = 0.0
        self.marker.color.a = 1.0

        # Pose
        self.marker.pose.position.x = 3.0
        self.marker.pose.position.y = 0.0
        self.marker.pose.position.z = 0.0
        self.marker.pose.orientation.x = 0.0
        self.marker.pose.orientation.y = 0.0
        self.marker.pose.orientation.z = 0.0
        self.marker.pose.orientation.w = 1.0

        self.timer = self.create_timer(0.5, self.timer_callback)

def main(args=None):
    rclpy.init(args=args)

    mesh_marker = Mesh_Marker()
    mesh_marker.get_logger().info('Mesh marker node started')
    rclpy.spin(mesh_marker)
    mesh_marker.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
