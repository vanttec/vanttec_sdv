'''
    Node to detect the lane and calculate the center point of the lane
    The node:
        - receives frames from the multisense camera and processes them to detect the lane
        - uses a YOLOv8 model to detect the lane
        - calculates the center point of the lane and compares it with the center point of the camera
        - publishes the processed frames, the center point of the lane and the detection flag
'''
#!/usr/bin/env python3
  
# Import the necessary libraries
import rclpy # Python library for ROS 2
from rclpy.node import Node # Handles the creation of nodes
from rclpy.qos import QoSProfile, ReliabilityPolicy
from sensor_msgs.msg import Image # Image is the message type
from ament_index_python.packages import get_package_share_directory
import os
from cv_bridge import CvBridge # Package to convert between ROS and OpenCV Images
import cv2 # OpenCV library
import numpy as np
from ultralytics import YOLO # Yolov8

  
class ModelTesting(Node):
  def __init__(self):

    super().__init__('model_testing')
    package_share_directory = get_package_share_directory('sdv_vision')


    # TOPICS - SUBSCRIBERS
    qos_profile = QoSProfile(depth=10, reliability=ReliabilityPolicy.BEST_EFFORT)
    self.subscription = self.create_subscription(Image,'/multisense/left/image_color', self.listener_callback, qos_profile) # Frames from the multisense camera

    # TOPICS - PUBLISHERS
    self.pub_center_video= self.create_publisher(Image, '/model_testing_video', 10)

        
    # PARAMETERS
    self.declare_parameter('model_file','Campus_Lane.pt')
    # self.declare_parameter('class_interest', 2)

    # YOLO MODEL
    self.MODEL = self.get_parameter('model_file').get_parameter_value().string_value
    # self.MODEL_CLASS = self.get_parameter('class_interest').get_parameter_value().integer_value
    self.MODEL_PATH = os.path.join(package_share_directory,self.MODEL)
    self.get_logger().info('Model '+ self.MODEL +' selected')
    self.MODEL = YOLO(self.MODEL_PATH)
    self.MODEL_NAMES = self.MODEL.model.names
    self.get_logger().info('Model loaded')
    # self.get_logger().info('Segmentation Class: ' + str(self.MODEL_NAMES[self.MODEL_CLASS]))

    # Used to convert between ROS and OpenCV images
    self.br = CvBridge()


  def listener_callback(self, data):


    # Convert ROS Image message to OpenCV image
    current_frame = self.br.imgmsg_to_cv2(data)

    # YOLO predictions
    results = self.MODEL(current_frame)
    if results[0].masks is not None:
        current_frame = results[0].plot(labels=True,boxes=False) #https://docs.ultralytics.com/modes/predict/#plot-method-parameters
	
    self.pub_center_video.publish(self.br.cv2_to_imgmsg(current_frame,'bgr8'))


def main(args=None):
  
  # Initialize the rclpy library
  rclpy.init(args=args)
  
  # Create the node
  model_testing = ModelTesting()
  
  # Spin the node so the callback function is called.
  rclpy.spin(model_testing)
  
  model_testing.destroy_node()
  
  # Shutdown the ROS client library for Python
  rclpy.shutdown()
  
if __name__ == '__main__':
  main()
