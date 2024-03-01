#!/usr/bin/env python3
# Basic ROS 2 program to publish real-time streaming 
# video from your built-in webcam
# Author:
# - Addison Sears-Collins
# - https://automaticaddison.com
  
# Import the necessary libraries
import rclpy # Python Client Library for ROS 2
from rclpy.node import Node # Handles the creation of nodes
from sensor_msgs.msg import Image # Video is the message type
from cv_bridge import CvBridge # Package to convert between ROS and OpenCV Videos
import cv2 # OpenCV library

class VideoPublisher(Node):
  """
  Create an VideoPublisher class, which is a subclass of the Node class.
  """
  def __init__(self):
    """
    Class constructor to set up the node
    """
    # Initiate the Node class's constructor and give it a name
    super().__init__('video_publisher')
    
    # Create the publisher. This publisher will publish an Video
    # to the video_frames topic. The queue size is 10 messages.
    self.publisher_ = self.create_publisher(Image, 'video_frames', 10)
    
    # We will publish a message every 0.1 seconds
    timer_period = 0.05  # seconds
    
    # Create the timer
    self.timer = self.create_timer(timer_period, self.timer_callback)
    
    # Create a VideoCapture object
    # The argument '0' gets the default webcam.
    #self.cap = cv2.VideoCapture(0)
    self.cap = cv2.VideoCapture('/workspace/src/sdv_vision/my_camera_node/carril.mp4')
    
    # Used to convert between ROS and OpenCV Videos
    self.br = CvBridge()

  def timer_callback(self):
    """
    Callback function.
    This function gets called every 0.1 seconds.
    """
    # Capture frame-by-frame
    # This method returns True/False as well
    # as the video frame.
    ret, frame = self.cap.read()
          
    if ret == True:
      self.publisher_.publish(self.br.cv2_to_imgmsg(frame))
      self.get_logger().info('Aqui toy')
    # Display the message on the console
    self.get_logger().info('Publishing video frame')
  
def main(args=None):
  

  rclpy.init(args=args)

  video_publisher = VideoPublisher()

  rclpy.spin(video_publisher)

  video_publisher.destroy_node()
  rclpy.shutdown()
  
if __name__ == '__main__':
  main()
