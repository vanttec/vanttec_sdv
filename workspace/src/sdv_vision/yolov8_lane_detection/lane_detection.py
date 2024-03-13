#!/usr/bin/env python3
# Basic ROS 2 program to subscribe to real-time streaming 
# video from your built-in webcam
# Author:
# - Addison Sears-Collins
# - https://automaticaddison.com
  
# Import the necessary libraries
import rclpy # Python library for ROS 2
from rclpy.node import Node # Handles the creation of nodes
from sensor_msgs.msg import Image # Image is the message type
from cv_bridge import CvBridge # Package to convert between ROS and OpenCV Images
import cv2 # OpenCV library
import pathlib
import numpy as np
from ultralytics import YOLO # Yolov8
from std_msgs.msg import Float64MultiArray # Enable use of std_msgs/Float64MultiArray message


def display_lines(image, lines):
    line_image = np.zeros_like(image)
    if lines is not None:
        for x1, y1, x2, y2 in lines:
            cv2.line(line_image, (x1, y1), (x2, y2), (255, 0, 0), 10)
    return line_image

def make_coordinates(img_height, line_parameters):
    if np.isnan(line_parameters).any():
        print('No line parameters')
        return np.array([0, 0, 0, 0])
    else:
        slope, intercept = line_parameters
        y1 = img_height
        y2 = int(y1*(3/5))
        x1 = int((y1 - intercept)/slope)
        x2 = int((y2 - intercept)/slope)
        if x1 > 10000 or x2 > 10000 or x1 < -10000 or x2 < -10000:
            return np.array([0, 0, 0, 0])
        return np.array([x1, y1, x2, y2])
  
def average_slope_intercept(img_height, lines):
    left_fit = []
    right_fit = []
    for line in lines:
        x1, y1, x2, y2 = line.reshape(4)
        parameters = np.polyfit((x1, x2), (y1, y2), 1)
        slope = parameters[0]
        intercept = parameters[1]
        if slope < 0:
            left_fit.append((slope, intercept))
        else:
            right_fit.append((slope, intercept))
    # Promedio
    left_fit_average = np.average(left_fit, axis=0)
    right_fit_average = np.average(right_fit, axis=0)
    # Mediana
    # left_fit_average = np.median(left_fit, axis=0)
    # right_fit_average = np.median(right_fit, axis=0)
    print("Left line average",left_fit_average)
    print("Right line average",right_fit_average)
    left_line = make_coordinates(img_height, left_fit_average)
    right_line = make_coordinates(img_height, right_fit_average)
    return np.array([left_line, right_line])

def center_point_finder(yPresent,yFuture,lines):
    x_coordinates = []
    for line in lines:
        x1, y1, x2, y2 = line
        # Calculate slope
        m = (y2 - y1) / (x2 - x1)
        # Calculate x coordinate
        x = ((yPresent - y1) / m) + x1
        x=int(x)
        x_coordinates.append(x)
        x = ((yFuture - y1) / m) + x1
        x=int(x)
        x_coordinates.append(x)
    if ((x_coordinates[2]-x_coordinates[0])%2==0):
        xPm=int(x_coordinates[0]+((x_coordinates[2]-x_coordinates[0])/2))
    else:
        xPm=int(x_coordinates[0]+((x_coordinates[2]-x_coordinates[0]+1)/2))
    if ((x_coordinates[3]-x_coordinates[1])%2==0):
        xFm=int(x_coordinates[1]+((x_coordinates[3]-x_coordinates[1])/2))
    else:
        xFm=int(x_coordinates[1]+((x_coordinates[3]-x_coordinates[1]+1)/2))
    centerPoints=np.array([
        np.array([xPm,yPresent]),
        np.array([xFm, yFuture])
    ])
    return(centerPoints)
  
def makePoints(image, centers):
  circle_image = np.zeros_like(image)
  if centers is not None:
      for x, y in centers:
          cv2.circle(circle_image, (x,y),1, (0, 255, 0), 5)
  return circle_image


class LaneDetection(Node):
  def __init__(self):
    # Initiate the Node class's constructor and give it a name
    super().__init__('lane_detection')
      
    # Create the subscriber. This subscriber will receive an Image
    # from the video_frames topic. The queue size is 10 messages.
    self.subscription = self.create_subscription(Image, 'video_frames', self.listener_callback, 10)
    self.subscription # prevent unused variable warning
    
    # Coordenates publisher - [x_up, y_up, x_down, y_down]
    self.publisher_center_pts= self.create_publisher(Float64MultiArray, '/center_pts', 10)
    # Used to convert between ROS and OpenCV images
    self.br = CvBridge()

    # YOLO MODEL
    self.MODEL_PATH= "/vanttec_sdv/workspace/src/sdv_vision/yolov8_lane_detection/Yolov8/weights/best_feb2024_FINSA.pt"
    self.MODEL = YOLO(self.MODEL_PATH)
    self.MODEL_NAMES = self.MODEL.model.names
    self.get_logger().info('Model loaded')

    # COUNTER OPTIMIZATION
    self.counter = 0 

  def get_className(classNo):
    if classNo==0:
      return "Lolo"
    elif classNo==1:
      return "Someone else"
    
  def listener_callback(self, data):
    """
    Callback function.
    """
    # Display the message on the console
    self.get_logger().info('Receiving video frame')

    # Convert ROS Image message to OpenCV image
    current_frame = self.br.imgmsg_to_cv2(data)
    counter = self.counter + 1
    msg = Float64MultiArray()

    # Auxiliar images to display
    frame_gray = np.copy(current_frame)
    frame_gray = cv2.cvtColor(frame_gray, cv2.COLOR_BGR2GRAY)
    combo_combo_image = frame_gray
    height,width = current_frame.shape[:2]
    polylines_im = np.zeros((height, width, 1), np.uint8)

    # YOLO predictions
    results = self.MODEL.predict(current_frame)
    if counter%2 == 0:    
      if results[0].masks is not None:
          clss = results[0].boxes.cls.cpu().tolist()
          masks = results[0].masks.xy
          for mask, cls in zip(masks, clss):
              if mask is not None and self.MODEL_NAMES[int(cls)] == "center":
                  cv2.polylines(polylines_im, [np.int32(mask)], isClosed=False, color=255, thickness=5)
          polylines_im[height-205:height, 0:width] = 0
          polylines_im[0:450, 0:width] = 0
          lines = cv2.HoughLinesP(polylines_im, 5, np.pi/180, 100, np.array([]), minLineLength=100, maxLineGap=10)
          if lines is not None:
              averaged_lines = average_slope_intercept(height, lines)
              if not np.isnan(averaged_lines).any():
                line_image = display_lines(frame_gray, averaged_lines)
                combo_image = cv2.addWeighted(frame_gray, 0.8, line_image, 1, 1)
                center_points = center_point_finder(500,680,averaged_lines)
                center_point_image=makePoints(combo_image,center_points)
                combo_combo_image=cv2.addWeighted(combo_image, 0.8, center_point_image, 1, 1)
                # Publish center points
                msg.data = center_points.flatten()
                self.publisher_center_pts.publish(msg)

    cv2.imshow('result',combo_combo_image)
    cv2.waitKey(1)

  
def main(args=None):
  
  # Initialize the rclpy library
  rclpy.init(args=args)
  
  # Create the node
  lane_detection = LaneDetection()
  
  # Spin the node so the callback function is called.
  rclpy.spin(lane_detection)
  
  # Destroy the node explicitly
  # (optional - otherwise it will be done automatically
  # when the garbage collector destroys the node object)
  lane_detection.destroy_node()
  
  # Shutdown the ROS client library for Python
  rclpy.shutdown()
  
if __name__ == '__main__':
  main()
