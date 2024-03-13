#!/usr/bin/env python3
import time
import rclpy
from rclpy.node import Node
from vectornav_msgs.msg import CommonGroup
import json
# import csv
import can

class Velocity_mode(Node):
    def __init__(self):
        super().__init__('velocity_mode')
        self.panel_module_id_tx = 1040 #hex.410
        self.panel_module_id_rx = 1033 #hex.409
        # Provide the path to your JSON file
        self.bus = can.interface.Bus(bustype='socketcan', channel='can0', bitrate=125000)
        file_path = '/home/ws/src/sdv_can/resources/panel_functionalities.json'
        self.json_data = self.read_json_file(file_path)
        #Subscription
        self.vector_sub = self.create_subscription(
            CommonGroup,
            '/vectornav/raw/common',
            self.velocity_callback,
            10
        )
        self.vector_sub
        #Variables
        # self.file = open('./rosbagAceleracion.csv', 'w')
        # self.writer = csv.writer(self.file)
        self.past_values = []
        self.category_accel = 0
        self.past_state_imu = 0

    def read_json_file(self, file_path):
            with open(file_path, 'r') as file:
                data = json.load(file)
            return data

    def velocity_callback(self, msg):
        print(msg.velocity.x)
        try:
            # self.writer.writerow([msg.velocity.x, msg.accel.x])
            self.compare_past_values(msg.velocity.x)
        except Exception as error:
            self.get_logger().debug('Velocity panel has failed')

    def compare_past_values(self, msg):
        self.actual_value = abs(msg)
        if len(self.past_values) > 3:
            self.past_values.pop(0)
            self.comparador_past_values = self.actual_value-(sum(self.past_values)/3)
            # print(self.comparador_past_values)
            if self.comparador_past_values > 0.06:
                self.category_accel = 1
            elif self.comparador_past_values < 0:
                self.category_accel = -1
            else:
                self.category_accel = 0 
            # print(self.category_accel)
        self.past_values.append(self.actual_value)
        self.aceleracion_frenado()


    def aceleracion_frenado(self):
        self.current_state_imu = self.category_accel
        # Panel Mov agarrarlo de IMU topico
        if (self.past_state_imu != self.current_state_imu):
            if (self.current_state_imu == 1):
                # print('acelera')
                data_can = self.json_data["panelMov"]["aceleracion"][0]
                self.bus.send(can.Message(arbitration_id=self.panel_module_id_tx,is_extended_id=False, data=data_can),timeout=1)
            elif(self.current_state_imu == -1):
                # print('frena')
                data_can = self.json_data["panelMov"]["frenado"][0]
                self.bus.send(can.Message(arbitration_id=self.panel_module_id_tx,is_extended_id=False, data=data_can),timeout=1)
            else:
                # print(self.current_state_imu)
                data_can = self.json_data["panelMov"]["reset"][0]
                self.bus.send(can.Message(arbitration_id=self.panel_module_id_tx,is_extended_id=False, data=data_can),timeout=1) 
            self.past_state_imu = self.current_state_imu
            print(self.current_state_imu)
       
def main(args):
    rclpy.init(args=args)
    logger = Velocity_mode()
    rclpy.spin(logger)
    logger.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main(None)