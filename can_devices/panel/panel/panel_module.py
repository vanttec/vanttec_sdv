#!/usr/bin/env python
import can
import time
import rclpy
from rclpy.node import Node
from sdv_msg.msg import PanelMsg
from std_msgs.msg import String


class PanelModule(Node):
    def __init__(self):
        super().__init__('panel_module')
        self.send_id = 819 #hex.333 
        self.receive_id = 546 #hex.222 
        self.signals={
        "on/panel/wiper": [False,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0x1])],
        "on/panel/horn": [False,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0x2])],
        "on/panel/right_upper_front_light": [False,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0x3])],
        "on/panel/left_upper_front_light": [False,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0x4])],
        "on/panel/right_down_front_light": [False,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0x5])],
        "on/panel/left_down_front_light": [False,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0x6])],
        "panel/status": [False,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0x7])],
        "panel/error": [False,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0x8])],
        "off/panel/wiper": [False,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0xB])],
        "off/panel/horn": [False,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0xC])],
        "off/panel/right_upper_front_light": [False,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0xD])],
        "off/panel/left_upper_front_light": [False,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0xE])],
        "off/panel/right_down_front_light": [False,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0xF])],
        "off/panel/left_down_front_light": [False,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0x10])],
        }
        self.receive_signals={
            1: "on/panel/wiper",
            2: "on/panel/horn",
            3: "on/panel/right_upper_front_light",
            4: "on/panel/left_upper_front_light",
            5: "on/panel/right_down_front_light",
            6: "on/panel/left_down_front_light",
            7: "panel/status",
            8: "panel/error",
            11: "on/panel/wiper",
            12: "off/panel/horn",
            13: "off/panel/right_upper_front_light",
            14: "off/panel/left_upper_front_light",
            15: "of/panel/right_down_front_light",
            16: "off/panel/left_down_front_light",
        }
        self.bus = can.interface.Bus(bustype='socketcan', channel='can1', bitrate=500000)
        self.data_start = 8
        self.bit_len = 6
        self.bit_panel_array=[]
        self.old_inverse_led = 0
        self.inverse_led = 0
        self.pub_panel_status = self.create_publisher(PanelMsg, 'panel/status', 10)
        #Sub to activate a single led or ask for the status of all leds
        self.sub_panel = self.create_subscription(
            String,
            'panel_control',
            self.panel_callback,
            10
        )
        self.sub_panel
        self.status_sub_panel = self.create_subscription(
            String,
            'status_panel',
            self.status_panel,
            10
        )
        self.status_sub_panel
        #Sub to activate multiple led with SDV Message
        self.sub_leds_panel = self.create_subscription(
           PanelMsg,
           'xbox_panel/control',
            self.xbox_callback,
            10
        )
    def decimalToBinary(self,ip_val):
        if ip_val >= 1:
            self.decimalToBinary(ip_val // 2)
        self.bit_panel_array.append(ip_val % 2)
    def xbox_callback(self,msg):
        if self.old_inverse_led == 0 and bool(msg.back.data):
            self.old_inverse_led = bool(msg.back.data)
            self.inverse_led=0  if self.inverse_led else 1
        else:
            self.old_inverse_led =bool(msg.back.data)
        if self.inverse_led:
            self.bus.send(self.signals["on/panel/wiper"][1], timeout=1) if bool(msg.wiper.data) else None
            self.bus.send(self.signals["on/panel/horn"][1], timeout=1) if bool(msg.horn.data) else None
            self.bus.send(self.signals["on/panel/right_upper_front_light"][1], timeout=1) if bool(msg.right_upper_front_light.data) else None
            self.bus.send(self.signals["on/panel/left_upper_front_light"][1], timeout=1) if bool(msg.left_upper_front_light.data) else None
        else:
            self.bus.send(self.signals["off/panel/wiper"][1], timeout=1) if bool(msg.wiper.data) else None
            self.bus.send(self.signals["off/panel/horn"][1], timeout=1) if bool(msg.horn.data) else None
            self.bus.send(self.signals["off/panel/right_upper_front_light"][1], timeout=1) if bool(msg.right_upper_front_light.data) else None
            self.bus.send(self.signals["off/panel/left_upper_front_light"][1], timeout=1) if bool(msg.left_upper_front_light.data) else None

    def panel_callback(self,msg):
        try:
            action = self.signals[msg.data]
            #Send action
            self.bus.send(action[1], timeout=1)
        except:
            #Send error
            self.bus.send(self.signals[self.receive_signals[len(self.signals)]][1], timeout=1)
    def status_panel(self,ros_msg):
        self.get_logger().warn('status: "%s"' % ros_msg.data)
        #Send STM32 panel status
        self.bus.send(self.signals["panel/status"][1], timeout=1)
        receivedMsg = self.bus.recv()
        message = receivedMsg.arbitration_id & self.receive_id
        try:
            if message == self.receive_id:
                if receivedMsg is not None:
                    codedMsg = receivedMsg.data
                    decodedMsg = codedMsg.hex()
                    hexaPos = (decodedMsg[6:8])
                    decimalPos = int(hexaPos, 16)
                    self.decimalToBinary(decimalPos)
                    print(self.bit_panel_array)
                    for signal in range(self.bit_len):
                        self.signals[self.receive_signals[signal+1]][0]= self.bit_panel_array[signal] == 1
                    msg = PanelMsg()
                    msg.wiper.data = self.signals["on/panel/wiper"][0]
                    msg.horn.data = self.signals["on/panel/horn"][0]
                    msg.right_upper_front_light.data = self.signals["on/panel/right_upper_front_light"][0]
                    msg.left_upper_front_light.data = self.signals["on/panel/left_upper_front_light"][0]
                    msg.right_down_front_light.data = self.signals["on/panel/right_down_front_light"][0]
                    msg.left_down_front_light.data = self.signals["on/panel/left_down_front_light"][0]
                    #Publish Panel information
                    self.pub_panel_status.publish(msg)
                    self.bit_panel_array = []
        except Exception as e:
            self.get_logger().warn('error in panel module "%s"' % e)
   
        

def main(args=None):
    rclpy.init(args=args)

    panel = PanelModule()
    panel.get_logger().info('Panel node started')
    rclpy.spin(panel)
    panel.destroy_node()
    rclpy.shutdown()
            
if __name__ == "__main__":
    
    main()
