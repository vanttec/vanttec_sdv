#!/usr/bin/env python
import can
import time
import rclpy
from rclpy.node import Node
from sdv_msg.msg import PanelMsg
from std_msgs.msg import String
from sdv_msg.msg import Encoder
import json

class PanelModule(Node):
    def __init__(self):
        super().__init__('panel_module')
        self.panel_module_id = 1040 #hex.410
        #self.bus = can.interface.Bus(bustype='socketcan', channel='can0', bitrate=100000)
        # Provide the path to your JSON file
        file_path = '/ws1/src/sdv_ros/can_devices/panel/resource/panel_functionalities.json'
        # Read the JSON file and store its contents in a dictionary
        self.json_data = self.read_json_file(file_path)
        self.encoder_panel = self.create_subscription(
            Encoder,
            '/ifm_encoder',
            self.encoder_callback,
            10
        )
        self.encoder_angle = 0
        timer_period = 0.01 #Seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
    def read_json_file(self, file_path):
        with open(file_path, 'r') as file:
            data = json.load(file)
        return data
    def encoder_callback(self, msg):
        self.encoder_angle = msg.angle
    def timer_callback(self):
        if(self.encoder_angle > 100) or (self.encoder_angle < -100):
            #Giro prominente
            data_can = self.json_data["panelDet"]["giro_prominente"]
            self.get_logger().warn('data: "%s"' % data_can)
            #self.bus.send(can.Message(arbitration_id=self.panel_module_id,is_extended_id=False, data=data_can),timeout=1)



    

def main(args=None):
    rclpy.init(args=args)

    panel = PanelModule()
    panel.get_logger().info('Panel node started')
    rclpy.spin(panel)
    panel.destroy_node()
    rclpy.shutdown()
            
if __name__ == "__main__":
    
    main()
