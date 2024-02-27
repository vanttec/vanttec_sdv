#!/usr/bin/env python3
import time
import rclpy
from rclpy.node import Node
from sdv_msgs.msg import Encoder
import json
import can

class Direccion_mode(Node):
    def __init__(self):
        super().__init__('direction_mode')
        #Json
        self.panel_module_id_tx = 1040 #hex.410
        self.panel_module_id_rx = 1033 #hex.409
        file_path = '/home/max/sdv/src/vanttec_sdv/docker_ws/sdv_can/resources/panel_functionalities.json'
        self.bus = can.interface.Bus(bustype='socketcan', channel='can0', bitrate=125000)
        self.json_data = self.read_json_file(file_path)
        #Subscription
        self.encoder_panel = self.create_subscription(
            Encoder,
            '/ifm_encoder',
            self.encoder_callback,
            10
        )
        self.encoder_panel
        #Variables
        # self.file = open('./rosbagGiros.csv', 'w')
        # self.writer = csv.writer(self.file)
        self.encoder_angle = 0
        self.curr_angle = 0
        self.past_angle = 0
        # self.fig = plt.figure()
        # self.ax1 = self.fig.add_subplot([0, 2500, 0, 1])
    def read_json_file(self, file_path):
                with open(file_path, 'r') as file:
                    data = json.load(file)
                return data

    def encoder_callback(self, msg):
        print(msg.abs_angle) 
        try:
            self.encoder_status(msg.abs_angle)
            print(self.encoder_state)
        except Exception as error:
            self.get_logger().debug('Direccion panel has failed')

    def encoder_status(self,msg):
        self.angle_encoder = msg
        if self.angle_encoder > 250:
            self.encoder_state = 1
        elif self.angle_encoder < -250:
            self.encoder_state = -1
        else:
            self.encoder_state = 0
        self.izquierda_derecha(msg)

    def izquierda_derecha(self, msg):
        self.curr_angle = msg
        if self.curr_angle != self.past_angle:
            if self.encoder_state == 1:
                data_can = self.json_data["panelDet"]["giro_repentino_derecha"][0]
                self.bus.send(can.Message(arbitration_id=self.panel_module_id_tx,is_extended_id=False, data=data_can),timeout=1)
            elif self.encoder_state == -1:
                data_can = self.json_data["panelDet"]["giro_repentino_izquierda"][0]
                self.bus.send(can.Message(arbitration_id=self.panel_module_id_tx,is_extended_id=False, data=data_can),timeout=1)
            else:
                data_can = self.json_data["panelDet"]["reset"][0]
                self.bus.send(can.Message(arbitration_id=self.panel_module_id_tx,is_extended_id=False, data=data_can),timeout=1)
        self.past_angle = self.curr_angle
       
def main(args):
    rclpy.init(args=args)
    logger = Direccion_mode()
    rclpy.spin(logger)
    logger.destroy_node()
    rclpy.shutdown()



if __name__ == "__main__":
    main(None)