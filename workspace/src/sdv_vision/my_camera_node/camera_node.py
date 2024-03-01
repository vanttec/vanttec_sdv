#!/usr/bin/env python3


import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2

class CameraNode(Node):
    def __init__(self):
        super().__init__('camera_node')
        self.publisher_ = self.create_publisher(Image, 'camera/image', 10)
        self.cv_bridge = CvBridge()
        self.timer_ = self.create_timer(1.0 / 30, self.capture_frame)

    def capture_frame(self):
        # OpenCV code to capture a frame (e.g., from a camera)
        # Replace this with your actual OpenCV code
        frame = cv2.imread('your_image.jpg')

        # Convert the OpenCV frame to a ROS 2 Image message
        image_msg = self.cv_bridge.cv2_to_imgmsg(frame)

        # Publish the image message
        self.publisher_.publish(image_msg)
        self.get_logger().info('Published a frame')

def main(args=None):
    rclpy.init(args=args)
    node = CameraNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()
