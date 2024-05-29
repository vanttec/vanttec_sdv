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
import pathlib
import numpy as np
from ultralytics import YOLO # Yolov8
from std_msgs.msg import String, Int32

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

    super().__init__('lane_detection')
    package_share_directory = get_package_share_directory('sdv_vision')


    # TOPICS - SUBSCRIBERS
    qos_profile = QoSProfile(depth=10, reliability=ReliabilityPolicy.BEST_EFFORT)
    # self.subscription = self.create_subscription(Image,'/lane_video_frames', self.listener_callback, qos_profile) # Frames from the multisense camera
    self.subscription = self.create_subscription(Image,'/multisense/left/image_color', self.listener_callback, qos_profile) # Frames from the multisense camera

    # TOPICS - PUBLISHERS
    self.pub_processed_video = self.create_publisher(Image, '/processed_video_frames', 10)
    self.pub_center_video= self.create_publisher(Image, '/lane_detection_video', 10)
    self.pub_flag = self.create_publisher(Int32, '/lane_detection_flag', 10)
    self.pub_error = self.create_publisher(Int32, '/lane_detection_error', 10)

        
    # PARAMETERS
    self.declare_parameter('model_file','best_feb2024_FINSA.pt')
    self.declare_parameter('center_class', 0)
    self.declare_parameter('error_threshold', [9,13]) # Error threshold for the center point detection
    self.declare_parameter('center_point', [590, 500])

    # YOLO MODEL
    self.MODEL = self.get_parameter('model_file').get_parameter_value().string_value
    self.MODEL_CLASS = self.get_parameter('center_class').get_parameter_value().integer_value
    self.MODEL_PATH = os.path.join(package_share_directory,self.MODEL)
    self.get_logger().info('Model '+ self.MODEL +' selected')
    self.MODEL = YOLO(self.MODEL_PATH)
    self.MODEL_NAMES = self.MODEL.model.names
    self.get_logger().info('Model loaded')
    self.get_logger().info('Segmentation Class: ' + str(self.MODEL_NAMES[self.MODEL_CLASS]))

    # Used to convert between ROS and OpenCV images
    self.br = CvBridge()

    # Global variables
    self.error = Int32()
    self.detection_flag = Int32()

  def listener_callback(self, data):

    # Error threshold
    error_threshold = self.get_parameter('error_threshold').get_parameter_value().integer_array_value
    pt_org = self.get_parameter('center_point').get_parameter_value().integer_array_value

    # Convert ROS Image message to OpenCV image
    current_frame = self.br.imgmsg_to_cv2(data)
    masks_img = np.copy(current_frame)

    # Auxiliar images to display
    frame_gray = np.copy(current_frame)
    frame_gray = cv2.cvtColor(frame_gray, cv2.COLOR_BGR2GRAY)
    height,width = current_frame.shape[:2]
    # pt_org = np.array([590, 500]) # SETEAR CON VALORES REALES
    polylines_im = np.zeros((height, width, 1), np.uint8)

    # YOLO predictions
    results = self.MODEL.predict(current_frame, classes=self.MODEL_CLASS)
    if results[0].masks is not None:
        mask = results[0].masks.xy[0]
        mask = np.int32(mask)
        cv2.polylines(polylines_im, [mask], isClosed=False, color=255, thickness=5)

        #explicar q es lo que se esta haciendo
        polylines_im[height-210:height, 0:width] = 0  # SETEAR CON VALORES REALES
        polylines_im[0:450, 0:width] = 0  # SETEAR CON VALORES REALES
        # cv2.imshow('results',polylines_im)
        lines = cv2.HoughLinesP(polylines_im, 5, np.pi/180, 100, np.array([]), minLineLength=100, maxLineGap=10)
        if lines is not None:
            averaged_lines = average_slope_intercept(height, lines)
            if not np.isnan(averaged_lines).any():
                center_points = center_point_finder(500,680,averaged_lines) # SETEAR CON VALORES REALES
                for x1, y1, x2, y2 in averaged_lines:
                    cv2.line(frame_gray, (x1, y1), (x2, y2), (255, 0, 0), 10)
                for x, y in center_points:
                    cv2.circle(frame_gray, (x,y), 1, (255, 0, 0), 5)
                cv2.circle(frame_gray, (pt_org[0],pt_org[1]), 1, (0, 0, 0), 5)

                # POINTS COMPARE
                self.error.data = int(abs((center_points[0][0] - pt_org[0])/pt_org[0])*100)

                if self.error.data >= error_threshold[1]:
                    color_rect = (179,179,255)
                    color_path = (0,0,255)
                    warning_txt = 'COLLISION RISK'
                    self.detection_flag.data = 1
                    coords_txt = (480, 310)
                if self.error.data >= error_threshold[0] and self.error.data < error_threshold[1]:
                    color_rect = (184,249,255)
                    color_path = (0,188,255)
                    warning_txt = 'Caution'
                    self.detection_flag.data = 2
                    coords_txt = (540, 310)
                else:
                    color_rect = (179,255,219)
                    color_path = (0,255,0)
                    warning_txt = 'Aligned'
                    self.detection_flag.data = 3
                    coords_txt = (540, 310)

                cv2.rectangle(current_frame, (450,250), (750,350), color_rect, -1)  # SETEAR CON VALORES REALES
                cv2.putText(current_frame, warning_txt, coords_txt, cv2.FONT_HERSHEY_SIMPLEX, 1, color_path, 2, cv2.LINE_AA)
                cv2.fillPoly(masks_img, [mask], color_path)
                current_frame = cv2.addWeighted(current_frame, 0.7, masks_img, 0.3, 0)

    self.pub_processed_video.publish(self.br.cv2_to_imgmsg(frame_gray))
    self.pub_center_video.publish(self.br.cv2_to_imgmsg(current_frame,'bgr8'))
    self.pub_flag.publish(self.detection_flag)
    self.pub_error.publish(self.error)


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
