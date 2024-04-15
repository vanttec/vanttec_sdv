#!/usr/bin/env python3
  
# Import the necessary libraries
import rclpy # Python Client Library for ROS 2
from rclpy.node import Node # Handles the creation of nodes
from rclpy.qos import QoSProfile, ReliabilityPolicy
from sensor_msgs.msg import Image # Video is the message type
from cv_bridge import CvBridge # Package to convert between ROS and OpenCV Videos
import cv2 # OpenCV library
import os

class VideoWriter(Node):
  def __init__(self):
    """
    Class constructor to set up the node
    """
    # Initiate the Node class's constructor and give it a name
    super().__init__('video_writer')


    qos_profile = QoSProfile(depth=10, reliability=ReliabilityPolicy.BEST_EFFORT)
    self.subscription = self.create_subscription(Image,'/multisense/left/image_color', self.listener_callback, qos_profile) # Frames from the multisense camera
    self.output = cv2.VideoWriter('finsa_soleado.avi', cv2.VideoWriter_fourcc(*'MJPG'), 30.0, (1280, 720))

    # Used to convert between ROS and OpenCV Videos
    self.br = CvBridge()

  def listener_callback(self, data):
    self.get_logger().info('Writing video')
    current_frame = self.br.imgmsg_to_cv2(data)
    self.output.write(current_frame)

  
def main(args=None):
  

  rclpy.init(args=args)

  video_writer = VideoWriter()

  rclpy.spin(video_writer)

  video_writer.destroy_node()
  
  rclpy.shutdown()
  
if __name__ == '__main__':
  main()
