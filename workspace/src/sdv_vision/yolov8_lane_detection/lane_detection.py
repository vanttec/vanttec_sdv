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
    left_line = make_coordinates(img_height, left_fit_average)
    right_line = make_coordinates(img_height, right_fit_average)
    return np.array([left_line, right_line])

def center_point_finder(yPresent,yFuture,lines):
    x_coordinates = []
    for line in lines:
        x1, y1, x2, y2 = line
         # Calculate slope
        if(x2==x1):
            m = 0.001
        else:
            m = (y2 - y1) / (x2 - x1)
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
    self.publisher_processed_video = self.create_publisher(Image, 'processed_video_frames', 10)
    self.publisher_center_video= self.create_publisher(Image, 'center_video_flag', 10)
    
    # Used to convert between ROS and OpenCV images
    self.br = CvBridge()

    # PRAMETERS
    self.declare_parameter('model_path','FINSA')
    model = self.get_parameter('model_path').get_parameter_value().string_value
    if model == 'FINSA': # FINSA model
        self.MODEL_PATH= "./src/sdv_vision/Yolov8/weights/best_feb2024_FINSA.pt"
        self.MODEL_CLASS = 0
        self.get_logger().info('Model FINSA selected')
    elif model == 'campus': # Campus model
        self.MODEL_PATH= "./src/sdv_vision/Yolov8/weights/best_CampusSeg.pt"
        self.MODEL_CLASS = 1
        self.get_logger().info('Model Campus Segmentation selected')
    else:
        self.get_logger().info('No Model selected')
    # YOLO MODEL
    self.MODEL = YOLO(self.MODEL_PATH)
    self.MODEL_NAMES = self.MODEL.model.names
    self.get_logger().info('Model loaded')
    self.get_logger().info('Segmentation Class: ' + str(self.MODEL_NAMES[self.MODEL_CLASS]))

    # COUNTER OPTIMIZATION
    self.counter = 0 
    self.ORG_PT_UP = np.array([596, 500])

    
  def listener_callback(self, data):
    
    # Display the message on the console
    self.get_logger().info('Receiving video frame')

    # Convert ROS Image message to OpenCV image
    current_frame = self.br.imgmsg_to_cv2(data)
    masks_img = np.copy(current_frame)
    masks = np.zeros(current_frame.shape[:2], np.uint8)
    # self.counter = self.counter + 1
    msg = Float64MultiArray()

    # Auxiliar images to display
    frame_gray = np.copy(current_frame)
    frame_gray = cv2.cvtColor(frame_gray, cv2.COLOR_BGR2GRAY)
    # combo_combo_image = frame_gray
    height,width = current_frame.shape[:2]
    pt_org = np.array([590, 500])
    polylines_im = np.zeros((height, width, 1), np.uint8)

    # YOLO predictions
    results = self.MODEL.predict(current_frame, classes=self.MODEL_CLASS)
    if results[0].masks is not None:
        mask = results[0].masks.xy[0]
        mask = np.int32(mask)
        cv2.polylines(polylines_im, [mask], isClosed=False, color=255, thickness=5)
        polylines_im[height-210:height, 0:width] = 0
        polylines_im[0:450, 0:width] = 0
        # cv2.imshow('results',polylines_im)
        lines = cv2.HoughLinesP(polylines_im, 5, np.pi/180, 100, np.array([]), minLineLength=100, maxLineGap=10)
        if lines is not None:
            averaged_lines = average_slope_intercept(height, lines)
            if not np.isnan(averaged_lines).any():
                center_points = center_point_finder(500,680,averaged_lines)
                for x1, y1, x2, y2 in averaged_lines:
                    cv2.line(frame_gray, (x1, y1), (x2, y2), (255, 0, 0), 10)
                for x, y in center_points:
                    cv2.circle(frame_gray, (x,y), 1, (255, 0, 0), 5)
                cv2.circle(frame_gray, (pt_org[0],pt_org[1]), 1, (0, 0, 0), 5)
                print(center_points)
                # POINTS COMPARE
                error = ((center_points[0][0] - pt_org[0])/pt_org[0])*100
                error = abs(round(error, 2))
                print('Error: ' + str(error))
                if error>=5 and error<10:
                    color_rect = (184,249,255)
                    color_path = (0,188,255)
                    warning_txt = 'Caution'
                    coords_txt = (540, 310)
                elif error>=10:
                    color_rect = (179,179,255)
                    color_path = (0,0,255)
                    warning_txt = 'COLLISION RISK'
                    coords_txt = (480, 310)
                else:
                    color_rect = (179,255,219)
                    color_path = (0,255,0)
                    warning_txt = 'Aligned'
                    coords_txt = (540, 310)
                cv2.rectangle(current_frame, (450,250), (750,350), color_rect, -1)
                # cv2.polylines(current_frame, [mask], isClosed=True, color=color_path, thickness=5) 
                cv2.putText(current_frame, warning_txt, coords_txt, cv2.FONT_HERSHEY_SIMPLEX, 1, color_path, 2, cv2.LINE_AA)
                cv2.fillPoly(masks_img, [mask], color_path)
                current_frame = cv2.addWeighted(current_frame, 0.7, masks_img, 0.3, 0)
                # Publish center points
                # msg.data = center_points.flatten()
                # self.publisher_center_pts.publish(msg)
            # else:
            #     msg.data = center_points.flatten()
            #     self.publisher_center_pts.publish([0, 0, 0, 0])
               
    self.publisher_processed_video.publish(self.br.cv2_to_imgmsg(frame_gray))
    self.publisher_center_video.publish(self.br.cv2_to_imgmsg(current_frame,'bgr8'))
  
def main(args=None):
  
  # Initialize the rclpy library
  rclpy.init(args=args)
  
  # Create the node
  lane_detection = LaneDetection()
  
  # Spin the node so the callback function is called.
  rclpy.spin(lane_detection)
  
  lane_detection.destroy_node()
  
  # Shutdown the ROS client library for Python
  rclpy.shutdown()
  
if __name__ == '__main__':
  main()
