#!/usr/bin/env python
import can
import time
import rclpy
from rclpy.node import Node
from sdv_msg.msg import PanelMsg
from std_msgs.msg import String, Float32
from sdv_msgs.msg import Encoder
from sensor_msgs.msg import Imu
import json

class PanelModule(Node):
    def __init__(self):
        super().__init__('panel_module')
        ##--------------------PANEL INDICATORS-----------------------##
        self.panel_module_id_tx = 0x410 #hex.410
        self.panel_module_id_rx = 0x409 #hex.409
        self.general_module_id_tx = 0x403
        self.general_module_id_rx = 0x404 
        # Provide the path to your JSON file
        file_path = '/home/ws/src/sdv_can/resources/panel_functionalities.json'
        # Read the JSON file and store its contents in a dictionary
        self.bus = can.interface.Bus(bustype='socketcan', channel='can0', bitrate=125000)
        self.json_data = self.read_json_file(file_path)
        self.encoder_angle = 0
        timer_period = 0.01 #Seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.imu_data = Imu()
        self.object_key=""
        self.traffic_key=""
        self.lane_key=""
        self.xbox_status={
            "giro_prominente_derecha":0,
            "giro_prominente_izquierda":0,
            "gran_trafico":0,
            "reset":0}
        self.battery_voltage = Float32()
        ##--------------------PANEL Publishers-----------------------##
        self.audio_panel= self.create_publisher(String, '/sdv/sdv/panel/audio', 10)
        self.pub_battery= self.create_publisher(Float32, '/sdv/panel/battery_voltage', 10)
      
        ##--------------------PANEL Subscribers-----------------------##

        self.encoder_panel = self.create_subscription(
            Encoder,
            '/ifm_encoder',
            self.encoder_callback,
            10
        )
        self.vel_car = self.create_subscription(
            Imu,
            '/vectornav/imu',
            self.imu_callback,
            10
        )
        self.object_sub = self.create_subscription(
            String,
            '/sdv/perception/object_status',
            self.object_notification_callback,
            10
        )
        self.traffic_sub = self.create_subscription(
            String,
            '/sdv/perception/traffic_status',
            self.recognize_traffic_callback,
            10
        )
        self.lane_sub = self.create_subscription(
            String,
            '/sdv/perception/lane_status',
            self.detect_lane_callback,
            10
        )


    def serializeFloatSingle(self, binNum: int):
        if not (binNum & ~(1<<31)):
            floatNum = 0
        else:
            sign = (binNum >> 31)
            expn = (binNum >> 23) & ((1<<8)-1)
            bias = (1<<(8-1))-1
            bexp = expn - bias
            frac = (binNum) & ((1<<23)-1)

            floatNum = (-1)**sign * (2**bexp) * (1 + frac/(1<<23))
            
        return float(floatNum)
    def read_json_file(self, file_path):
        with open(file_path, 'r') as file:
            data = json.load(file)
        return data
    def encoder_callback(self, msg):
        self.encoder_angle = msg.angle
    def object_notification_callback(self, msg):
        self.object_key = msg.data
    def recognize_traffic_callback(self, msg):
        self.traffic_key = msg.data
    def detect_lane_callback(self, msg):
        self.lane_key = msg.data
    def imu_callback(self, msg):
        self.imu_data=msg
    def km_to_m(self, km):
        return km*1000/pow(3600,2)

    def timer_callback(self):
        try:
        # Panel Mov agarrarlo de IMU topico
        if(self.imu_data.linear_acceleration.x > self.km_to_m(3)):
            data_can = self.json_data["panelMov"]["aceleracion"][0]
            self.bus.send(can.Message(arbitration_id=self.panel_module_id_tx,is_extended_id=False, data=data_can),timeout=1)
        elif(self.imu_data.linear_acceleration.x < self.km_to_m(2)):
            data_can = self.json_data["panelMov"]["estacionario"][0]
            self.bus.send(can.Message(arbitration_id=self.panel_module_id_tx,is_extended_id=False, data=data_can),timeout=1)
            audio = self.json_data["panelMov"]["estacionario"][1]
            if len(audio)>=1:
                self.audio_panel.publish(audio_file)
        else:
            data_can = self.json_data["panelMov"]["reset"][0]
            self.bus.send(can.Message(arbitration_id=self.panel_module_id_tx,is_extended_id=False, data=data_can),timeout=1) 
        # Panel Det agarrarlo de imu y encoder  
        if(self.encoder_angle > 100):
            data_can = self.json_data["panelDet"]["giro_prominente_derecha"][0]
            self.bus.send(can.Message(arbitration_id=self.panel_module_id_tx,is_extended_id=False, data=data_can),timeout=1)
        elif(self.encoder_angle < -100):
            data_can = self.json_data["panelDet"]["giro_prominente_izquierda"][0]
            self.bus.send(can.Message(arbitration_id=self.panel_module_id_tx,is_extended_id=False, data=data_can),timeout=1)

        # Object Notification agarrarlo de perception
        if(self.object_key!="" and self.object_key in self.json_data["objectNotification"]):
            data_can = self.json_data["objectNotification"][self.object_key][0]
            self.bus.send(can.Message(arbitration_id=self.panel_module_id_tx,is_extended_id=False, data=data_can),timeout=1)
            audio = self.json_data["objectNotification"][self.object_key][1]
            if len(audio)>=1:
                self.audio_panel.publish(audio_file)
        # Recognize traffic agarrarlo de perception
        if(self.traffic_key!="" and self.traffic_key in self.json_data["recognizeTraffic"]):
            data_can = self.json_data["recognizeTraffic"][self.traffic_key][0]
            self.bus.send(can.Message(arbitration_id=self.panel_module_id_tx,is_extended_id=False, data=data_can),timeout=1)
            audio = self.json_data["recognizeTraffic"][self.traffic_key][1]
            if len(audio)>=1:
                self.audio_panel.publish(audio_file)
        # Detect Lane agarrarlo de perception
        if(self.lane_key!="" and self.lane_key in self.json_data["detectLane"]):
            data_can = self.json_data["recognizeTraffic"][self.lane_key][0]
            self.bus.send(can.Message(arbitration_id=self.panel_module_id_tx,is_extended_id=False, data=data_can),timeout=1)
        
        #Publish battery voltage 
        receivedMsg = self.bus.recv(1)
        if receivedMsg is not None:
            if receivedMsg.arbitration_id == self.panel_module_id_rx:
                if receivedMsg.data[0] == 0x5:
                    data_volts =  (receivedMsg.data[1] << 24) | (receivedMsg.data[2] << 16) | (receivedMsg.data[3] << 8) | (0 << 0)
                    self.battery_voltage.data = self.serializeFloatSingle(data_volts)
                    self.pub_battery.publish(self.battery_voltage)
            elif receivedMsg.arbitration_id == self.general_module_id_tx:
                if receivedMsg.data[0] == 0x0:
                    audio_file = self.json_data["emergency_audio_mode"][str(receivedMsg.data[1])]
                    self.audio_panel.publish(audio_file)
                elif receivedMsg.data[0] == 0x2:
                    audio_file = self.json_data["drive_audio_mode"][str(receivedMsg.data[1])]
                    self.audio_panel.publish(audio_file)
                elif receivedMsg.data[0] == 0x3:
                    audio_file = self.json_data["driver_present_audio_mode"][str(receivedMsg.data[1])]
                    self.audio_panel.publish(audio_file)



                    



    

def main(args=None):
    rclpy.init(args=args)

    panel = PanelModule()
    panel.get_logger().info('Panel node started')
    rclpy.spin(panel)
    panel.destroy_node()
    rclpy.shutdown()
            
if __name__ == "__main__":
    
    main()