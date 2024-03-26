#!/usr/bin/env python3

# Import the necessary libraries
import rclpy # Python library for ROS 2
from rclpy.node import Node # Handles the creation of nodes
from sensor_msgs.msg import Image # Image is the message type
from cv_bridge import CvBridge # Package to convert between ROS and OpenCV Images
import cv2 # OpenCV library
from ultralytics import YOLO # Yolov8

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
      
    # Create the subscriber. This subscriber will receive an Image
    # from the video_frames topic. The queue size is 10 messages.
    self.subscription = self.create_subscription(Image, 'video_frames', self.listener_callback, 10)
    self.subscription # prevent unused variable warning
    
    # Coordenates publisher - [x_up, y_up, x_down, y_down]
    self.publisher_video= self.create_publisher(Image, '/people_distance_detection', 10)
    
    # Used to convert between ROS and OpenCV images
    self.br = CvBridge()

    # PRAMETERS
    self.declare_parameter('detection_mode','calibration') # Detection mode
    self.declare_parameter('calibration_distance',2.0) # Distance of calibration in meters (person2camera)
    self.declare_parameter('person_width',0.38) # Distance of person width in meters (shoulder2shoulder)
    self.KNOWN_DISTANCE = self.get_parameter('calibration_distance').get_parameter_value().double_value
    self.PERSON_WIDTH = self.get_parameter('person_width').get_parameter_value().double_value
    self.focal_person = 0
    # YOLO MODEL
    self.MODEL_PATH= "./src/sdv_vision/Yolov8/weights/yolov8n-pose.pt"
    self.MODEL_CLASS = 0 # Person class
    self.MODEL = YOLO(self.MODEL_PATH)
    self.MODEL_NAMES = self.MODEL.model.names
    self.get_logger().info('Model loaded')
    self.get_logger().info('Detection Classes: ' + str(self.MODEL_NAMES[self.MODEL_CLASS]))

    
  def listener_callback(self, data):
    
    mode = self.get_parameter('detection_mode').get_parameter_value().string_value

    # Convert ROS Image message to OpenCV image
    current_frame = self.br.imgmsg_to_cv2(data)
    # Display the message on the console

    self.get_logger().info('Receiving video frame')
    self.get_logger().info('Detection Mode: ' + mode)

    # YOLO predictions
    results = self.MODEL.predict(current_frame, classes=self.MODEL_CLASS, show=True, conf = 0.8)
    if results[0].boxes  is not None:
        boxes_w = results[0].boxes.xywh.cpu()
        boxes_xyxy = results[0].boxes.xyxy.cpu()
        keypoints = results[0].keypoints.xy.cpu().numpy()
        for box_w, box_xyxy, keypoint in zip(boxes_w, boxes_xyxy, keypoints):
            shoulder_left_x, _sly = keypoint[5]
            shoulder_right_x, _sry = keypoint[6]
            person_width = int(abs(shoulder_left_x - shoulder_right_x))
            print("Person width: ", person_width)
            person_height = box_w[3]
            x,y = int(box_xyxy[0]), int(box_xyxy[1]+(person_height-50))
            if mode == "calibration":
                self.focal_person  = focal_length_finder(self.KNOWN_DISTANCE, self.PERSON_WIDTH, person_width)
                color_box = (255, 170, 0)
                text = "Calibrating..."
                rect_length = (x+120, y+25)
                print(f"Focal length: {self.focal_person}")
            elif mode == "detection":
                print(f"Focal length: {self.focal_person}")
                distance = distance_finder(self.focal_person, self.PERSON_WIDTH, person_width)
                distance = round(float(distance), 3)
                print(f"Distance: {distance} meters")
                if distance < 2:
                    color_box = (179,179,255)
                if distance >= 2 and distance < 3:
                    color_box = (184,249,255)
                if distance >= 3:
                    color_box = (179,255,219)
                text = "Distance "+str(distance)+" meters"
                rect_length = (x+192, y+25)
            cv2.rectangle(current_frame, (x, y-1), rect_length, color_box,-1 )
            cv2.putText(current_frame, text, (x+10,y+20), cv2.FONT_HERSHEY_SIMPLEX, 0.48, (255,255,255), 1)

               
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
