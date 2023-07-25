#! /usr/bin/env python
import rclpy
from rclpy.node import Node
from visualization_msgs.msg import Marker
from rclpy.time import Time


class Foxglove(Node):
    def __init__(self):
        super().__init__('foxglove')
        self.marker_pub = self.create_publisher(Marker,"/avocado", 2)
        self.marker = Marker()
        self.marker.header.frame_id = "base_link"
        self.marker.header.stamp = self.get_clock().now().to_msg()
        self.marker.ns = ""
        # Shape (mesh resource type - 10)
        self.marker.type = 10
        self.marker.id = 0
        self.marker.action = 0
        # Note: Must set mesh_resource to a valid URL for a model to appear
        # self.marker.mesh_resource = 'package://sdv_description/meshes/yolo/Avocado.glb'
        
        #self.marker.mesh_resource = "https://storage.googleapis.com/fluttermarket-8e919.appspot.com/ROS/Avocado.glb"
        self.marker.mesh_resource = 'file:///ws/src/sdv_ros/can_devices/panel/meshes/Avocado.glb'
        self.marker.mesh_use_embedded_materials = False

        #Scale
        self.marker.scale.x = 10.0
        self.marker.scale.y = 10.0
        self.marker.scale.z = 10.0

        #Color
        self.marker.color.r = 0.0
        self.marker.color.g = 0.0
        self.marker.color.b = 0.0
        self.marker.color.a = 1.0
        #Pose
        self.marker.pose.position.x = 3.0
        self.marker.pose.position.y = 0.0
        self.marker.pose.position.z = 0.0
        self.marker.pose.orientation.x = 0.0
        self.marker.pose.orientation.y = 0.0
        self.marker.pose.orientation.z = 0.0
        self.marker.pose.orientation.w = 1.0        
        self.timer = self.create_timer(0.1, self.timer_callback)
    def timer_callback(self):
        self.marker_pub.publish(self.marker)


def main(args=None):
    rclpy.init(args=args)

    fox = Foxglove()
    fox.get_logger().info('Foxglove node started')
    rclpy.spin(fox)
    fox.destroy_node()
    rclpy.shutdown()
            
if __name__ == "__main__":
    
    main()
