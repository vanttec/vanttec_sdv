#!/usr/bin/env python3

# Import the necessary libraries
import rclpy # Python library for ROS 2
from rclpy.node import Node # Handles the creation of nodes
from sensor_msgs.msg import Image # Image is the message type
from std_msgs.msg import String, Int32
from cv_bridge import CvBridge # Package to convert between ROS and OpenCV Images
import cv2 # OpenCV library
from ultralytics import YOLO # Yolov8
from ultralytics.utils.plotting import Annotator, colors
from rclpy.qos import QoSProfile, ReliabilityPolicy

def focal_length_finder(measured_distance, real_width, width_in_frame):
    focal_length = (width_in_frame * measured_distance) / real_width
    return focal_length

def distance_finder(focal_length, real_width, width_in_frame):
    distance = (real_width * focal_length) / width_in_frame
    return distance

class PersonDistanceDetection(Node):
  def __init__(self):
    # Initiate the Node class's constructor and give it a name
    super().__init__('person_distance_detection')



    # PRAMETERS
    self.declare_parameter('detection_mode','calibration') #  Detection mode (calibration or detection)
    self.declare_parameter('calibration_distance',2.0) # Distance of calibration in meters (person2camera)
    self.declare_parameter('person_width',0.38) # Distance of person width in meters (shoulder2shoulder)
    self.declare_parameter('image_input','video') # Usage mode (testing or deployment)

    self.KNOWN_DISTANCE = self.get_parameter('calibration_distance').get_parameter_value().double_value
    self.PERSON_WIDTH = self.get_parameter('person_width').get_parameter_value().double_value
    self.IMAGE_INPUT = self.get_parameter('image_input').get_parameter_value().string_value
    self.focal_person = 0

    # YOLO MODEL
    self.MODEL_PATH= "/home/fcanof/vanttec_sdv/workspace/src/sdv_vision/Yolov8/weights/yolov8n-pose.pt"
    self.MODEL_CLASS = 0 # Person class
    self.MODEL = YOLO(self.MODEL_PATH)
    self.MODEL_NAMES = self.MODEL.model.names
    self.get_logger().info('Model loaded')
    self.get_logger().info('Detection Classes: ' + str(self.MODEL_NAMES[self.MODEL_CLASS]))

    
    # TOPICS - SUBSCRIBERS
    if self.IMAGE_INPUT == "video": # For testing purposes
        self.subscription = self.create_subscription(Image, '/video_frames', self.listener_callback, 10) # Frames from a video
    elif self.IMAGE_INPUT == "multisense": # For deployment
        qos_profile = QoSProfile(depth=10, reliability=ReliabilityPolicy.BEST_EFFORT)
        self.subscription = self.create_subscription(Image,'/multisense/left/image_color', self.listener_callback, qos_profile) # Frames from the multisense camera
    
    # TOPICS - PUBLISHERS
    self.publisher_video= self.create_publisher(Image, '/people_distance_detection', 10)
    self.pub_flag = self.create_publisher(Int32, '/flag_detections', 10)
    
    # Used to convert between ROS and OpenCV images
    self.br = CvBridge()

  def listener_callback(self, data):
    # PRAMETERS
    mode = self.get_parameter('detection_mode').get_parameter_value().string_value
    flag_detection = Int32()
    # Convert ROS Image message to OpenCV image
    current_frame = self.br.imgmsg_to_cv2(data)

    self.get_logger().info('Receiving video frame')
    self.get_logger().info('Detection Mode: ' + mode)

    # YOLO predictions
    results = self.MODEL.predict(current_frame, classes=self.MODEL_CLASS, conf = 0.8)
    # current_frame = results[0].plot(kpt_line=False,kpt_radius=0)
    annotator = Annotator(current_frame, line_width=2)
    if results[0].boxes is not None:
        boxes_w = results[0].boxes.xywh.cpu()
        boxes_xyxy = results[0].boxes.xyxy.cpu()
        keypoints = results[0].keypoints.xy.cpu().numpy()
        flag_indicators = []
        for box_w, box_xyxy, keypoint in zip(boxes_w, boxes_xyxy, keypoints):
            shoulder_left_x, _sly = keypoint[5]
            shoulder_right_x, _sry = keypoint[6]
            person_width = int(abs(shoulder_left_x - shoulder_right_x))
            # print("Person width: ", person_width)
            person_height = box_w[3]
            x,y = int(box_xyxy[0]), int(box_xyxy[1]+(person_height-50))
            if mode == "calibration":
                self.focal_person  = focal_length_finder(self.KNOWN_DISTANCE, self.PERSON_WIDTH, person_width)
                color_box = (255, 170, 0) 
                text = "Calibrating..."
                text_color = (255,255,255)
                flag_indicators.append(4)
            elif mode == "detection":
                distance = distance_finder(self.focal_person, self.PERSON_WIDTH, person_width)
                distance = round(float(distance), 2)
                if distance < 1.5: # Red - Danger zone
                    color_box = (0,0,167)
                    text_color = (255,255,255)
                    flag_indicators.append(1)
                if distance >= 1.5 and distance < 3: # Yellow - Warning zone
                    color_box = (0,204,235)
                    text_color = (0,0,0)
                    flag_indicators.append(2)
                if distance >= 3: # Green - Safe zone
                    color_box = (0,184,79)
                    flag_indicators.append(3)
                    text_color = (255,255,255)
                text = "Person - distance "+str(distance)+" meters"
            annotator.box_label(box_xyxy, label=text,color=color_box,txt_color=text_color)
        if len(flag_indicators) > 0:
            flag_detection.data = min(flag_indicators)
            self.pub_flag.publish(flag_detection)
               
    self.publisher_video.publish(self.br.cv2_to_imgmsg(current_frame,'bgr8'))
  
def main(args=None):
  
  # Initialize the rclpy library
  rclpy.init(args=args)
  
  # Create the node
  person_distance_detection = PersonDistanceDetection()
  
  # Spin the node so the callback function is called.
  rclpy.spin(person_distance_detection)
  
  person_distance_detection.destroy_node()
  
  # Shutdown the ROS client library for Python
  rclpy.shutdown()
  
if __name__ == '__main__':
  main()
