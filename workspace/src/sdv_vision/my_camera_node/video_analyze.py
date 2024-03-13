#!/usr/bin/env python3
# Basic ROS 2 program to subscribe to real-time streaming 
# video from your built-in webcam
# Author:
# - Addison Sears-Collins
# - https://automaticaddison.com

# FIMSA Project - April 2024
  
# Import the necessary libraries
import rclpy # Python library for ROS 2
from rclpy.node import Node # Handles the creation of nodes
from sensor_msgs.msg import Image # Image is the message type
from cv_bridge import CvBridge # Package to convert between ROS and OpenCV Images
import cv2 # OpenCV library
import numpy as np
import rclpy.qos
from ultralytics import YOLO # Library to manage YOLO models and results

def display_lines(image, lines):
  '''
  image: image in numpy array format
  lines: line parameters in terms of pixel coordinates

  return: binary image with lines displayed
  '''
  line_image = np.zeros_like(image)
  if lines is not None:
      for x1, y1, x2, y2 in lines:
          cv2.line(line_image, (x1, y1), (x2, y2), (255, 0, 0), 10)
  return line_image

def make_coordinates(image, line_parameters):
  '''
  image: image in numpy array format
  line_parameters: line parameters in terms of slope and point of intersection

  return: line parameters in terms of two pixel coordinates
  '''
  if np.isnan(line_parameters).any():
      return np.array([0, 0, 0, 0])
  else:
      slope, intercept = line_parameters
      y1 = image.shape[0]
      y2 = int(y1*(3/5))
      x1 = int((y1 - intercept)/slope)
      x2 = int((y2 - intercept)/slope)
      return np.array([x1, y1, x2, y2])
  
def average_slope_intercept(image, lines):
  '''
  image : 
  '''
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
  left_fit_average = np.average(left_fit, axis=0)
  right_fit_average = np.average(right_fit, axis=0)
  left_line = make_coordinates(image, left_fit_average)
  right_line = make_coordinates(image, right_fit_average)
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

class ImageSubscriber(Node):
  def __init__(self):
    # Initiate the Node class's constructor and give it a name
    super().__init__('image_subscriber')
      
    # Create the subscriber. This subscriber will receive an Image
    # from the video_frames topic. The queue size is 10 messages.
    self.subscription = self.create_subscription(
      Image, 
      'video_frames', 
      self.listener_callback, 
      qos_profile=rclpy.qos.qos_profile_sensor_data)
    self.subscription # prevent unused variable warning
      
    # Used to convert between ROS and OpenCV images
    self.br = CvBridge()
    self.MODEL_PATH= "/workspace/src/sdv_vision/my_camera_node/Yolov8/weights_train4/best.pt"
  
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
    current_frame = self.br.imgmsg_to_cv2(data)

    # Convert ROS Image message to OpenCV image
    #model = YOLO("/Yolov8/weights_train4/best.pt")  # segmentation model

    # Initialize the YOLO model with the weights file path
    model = YOLO(self.MODEL_PATH)

    # Now you can access the names attribute
    names = model.model.names
    
    '''ret, im0 = cap.read()
    if not ret:
        print("Video frame is empty or video processing has been successfully completed.")
        break
    '''
    
    results = model.predict(current_frame)

    polylines_im = np.zeros((current_frame.shape[0], current_frame.shape[1], 1), np.uint8)
    height,width = polylines_im.shape[:2]
    if results[0].masks is not None:
        clss = results[0].boxes.cls.cpu().tolist()
        masks = results[0].masks.xy
        for mask, cls in zip(masks, clss):
            if mask is not None and names[int(cls)] == "center":
                cv2.polylines(polylines_im, [np.int32(mask)], isClosed=False, color=255, thickness=5)
    polylines_im = cv2.medianBlur(polylines_im, 7)
    polylines_im[height-100:height, 0:width] = 0
    lines = cv2.HoughLinesP(polylines_im, 5, np.pi/180, 100, np.array([]), minLineLength=100, maxLineGap=10)
    if lines is not None:
        averaged_lines = average_slope_intercept(current_frame, lines)
        line_image = display_lines(current_frame, averaged_lines)
        im0 = cv2.addWeighted(current_frame, 0.8, line_image, 1, 1)

    center_points = center_point_finder(500,680,averaged_lines)
    center_point_image=makePoints(im0,center_points)
    combo_combo_image=cv2.addWeighted(im0, 0.8, center_point_image, 1, 1)

    #out.write(combo_combo_image)

    # Display image
    cv2.imshow("camera", combo_combo_image)
    cv2.waitKey(1)

  
def main(args=None):
  
  # Initialize the rclpy library
  rclpy.init(args=args)
  
  # Create the node
  image_subscriber = ImageSubscriber()
  
  # Spin the node so the callback function is called.
  rclpy.spin(image_subscriber)
  
  # Destroy the node explicitly
  # (optional - otherwise it will be done automatically
  # when the garbage collector destroys the node object)
  image_subscriber.destroy_node()
  
  # Shutdown the ROS client library for Python
  rclpy.shutdown()
  
if __name__ == '__main__':
  main()
