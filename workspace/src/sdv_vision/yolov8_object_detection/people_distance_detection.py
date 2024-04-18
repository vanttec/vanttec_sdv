'''
    This script is used to detect people in a video stream and calculate the distance between the person and the camera.
    The node:
        - receives frames from the multisense camera and processes them to detect people
        - uses a YOLOv8 model to detect people
        - calculates the distance between the person and the camera
        - publishes the processed frames and the detection flag
'''
#!/usr/bin/env python3

# Import the necessary libraries
import rclpy # Python library for ROS 2
from rclpy.node import Node # Handles the creation of nodes
from rclpy.qos import QoSProfile, ReliabilityPolicy
from ament_index_python.packages import get_package_share_directory
from sensor_msgs.msg import Image # Image is the message type
from std_msgs.msg import String, Int32
from cv_bridge import CvBridge # Package to convert between ROS and OpenCV Images
import cv2 # OpenCV library
from ultralytics import YOLO # Yolov8
from ultralytics.utils.plotting import Annotator
import os
import yaml

def focal_length_finder(measured_distance, real_width, width_in_frame):
    focal_length = (width_in_frame * measured_distance) / real_width
    return focal_length

def distance_finder(focal_length, real_width, width_in_frame):
    distance = (real_width * focal_length) / width_in_frame
    return distance

class PeopleDistanceDetection(Node):
  def __init__(self):
    # Initiate the Node class's constructor and give it a name
    super().__init__('people_distance_detection')
    pkg_share_directory = get_package_share_directory('sdv_vision')

    # PARAMETERS
    self.declare_parameter('detection_mode','detection') #  Detection mode (calibration or detection)
    self.declare_parameter('calibration_distance',2.0) # Distance of calibration in meters (person2camera)
    self.declare_parameter('calibration_person_width',0.38) # Distance of person width in meters (shoulder2shoulder)
    self.declare_parameter('model_file','yolov8n-pose.pt') # Model file to use
    self.declare_parameter('caution_distances', [1.5,3.0]) # Distance thresholds for the caution and warning zones. [danger, warning]

    
    # CALIBRATION VALUES
    self.CALIBRATION_KNOWN_DISTANCE = self.get_parameter('calibration_distance').get_parameter_value().double_value
    self.CALIBRATION_PERSON_WIDTH = self.get_parameter('calibration_person_width').get_parameter_value().double_value
    self.focal_person = 426.3157894736842
    self.FOCAL_PATH = os.path.join(pkg_share_directory,'focal_person.yaml')

    # CAUTION DISTANCES
    self.caution_distances = self.get_parameter('caution_distances').get_parameter_value().double_array_value
    
    # TOPICS - SUBSCRIBERS
    self.subscription = self.create_subscription(Image, '/people_video_frames', self.listener_callback, 10) # Frames from a video stream
    
    # TOPICS - PUBLISHERS
    self.publisher_video= self.create_publisher(Image, '/people_distance_detection_video', 10)
    self.pub_flag = self.create_publisher(Int32, '/people_distance_detections_flag', 10)
    self.flag_detection = Int32()

    # YOLO MODEL
    self.MODEL_FILE = self.get_parameter('model_file').get_parameter_value().string_value
    self.MODEL_PATH= os.path.join(pkg_share_directory,self.MODEL_FILE)
    self.MODEL_CLASS = 0 # Person class
    self.MODEL = YOLO(self.MODEL_PATH)
    self.MODEL_NAMES = self.MODEL.model.names
    self.get_logger().info('Model loaded')
    self.get_logger().info('Detection Classes: ' + str(self.MODEL_NAMES[self.MODEL_CLASS]))
    
    # Used to convert between ROS and OpenCV images
    self.br = CvBridge()

  def save_focal_person(self):
    '''
        In the calibration state save the focal person value to a yaml file
    '''
    with open(self.FOCAL_PATH, 'w') as file:
        self.get_logger().info(str(self.focal_person))
        yaml.dump({'focal_person': self.focal_person}, file)
        self.get_logger().info('Focal person value saved to focal_person.yaml')


  def listener_callback(self, data):
    
    # Get the detection mode from the parameter server and convert it to a string value. (calibration or detection)
    mode = self.get_parameter('detection_mode').get_parameter_value().string_value

    # Convert ROS Image message to OpenCV image
    current_frame = self.br.imgmsg_to_cv2(data)

    # self.get_logger().info('Receiving video frame')
    # self.get_logger().info('Detection Mode: ' + mode)

    # YOLO predictions
    results = self.MODEL.predict(current_frame, classes=self.MODEL_CLASS, conf = 0.8)
    annotator = Annotator(current_frame, line_width=2)
    if results[0].boxes is not None:
        boxes_xyxy = results[0].boxes.xyxy.cpu()
        keypoints = results[0].keypoints.xy.cpu().numpy()
        flag_indicators = []
        color_box = (255, 255, 255)
        text_color = (0,0,0)
        for box_xyxy, keypoint in zip(boxes_xyxy, keypoints):
            shoulder_left_x, _sly = keypoint[5] 
            shoulder_right_x, _sry = keypoint[6]
            person_width = int(abs(shoulder_left_x - shoulder_right_x))
            if mode == "calibration":
                self.focal_person  = focal_length_finder(self.CALIBRATION_KNOWN_DISTANCE, self.CALIBRATION_PERSON_WIDTH, person_width)
                self.save_focal_person()    
                color_box = (255, 170, 0) 
                text = "Calibrating..."
                text_color = (255,255,255)
                flag_indicators.append(4)
            elif mode == "detection":
                distance = distance_finder(self.focal_person, self.CALIBRATION_PERSON_WIDTH, person_width)
                distance = round(float(distance), 1)
                if distance < self.caution_distances[0]: # Red - Danger zone
                    color_box = (0,0,167)
                    flag_indicators.append(1)
                elif distance >= self.caution_distances[0] and distance < self.caution_distances[1]: # Yellow - Warning zone
                    color_box = (0,204,235)
                    text_color = (0,0,0)
                    flag_indicators.append(2)
                elif distance >= self.caution_distances[1]: # Green - Safe zone
                    color_box = (0,184,79)
                    flag_indicators.append(3)
                text = f"Person - distance {distance} meters"
            annotator.box_label(box_xyxy, label=text,color=color_box,txt_color=(text_color))
        
        if len(flag_indicators) > 0:
            self.flag_detection.data = min(flag_indicators)
            self.pub_flag.publish(self.flag_detection)

    self.publisher_video.publish(self.br.cv2_to_imgmsg(current_frame,'bgr8'))
  
def main(args=None):
  
  # Initialize the rclpy library
  rclpy.init(args=args)
  
  # Create the node
  people_distance_detection = PeopleDistanceDetection()
  
  # Spin the node so the callback function is called.
  rclpy.spin(people_distance_detection)
  
  people_distance_detection.destroy_node()
  
  # Shutdown the ROS client library for Python
  rclpy.shutdown()
  
if __name__ == '__main__':
  main()
