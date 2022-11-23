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
        self.receive_signals={
            1: "panel/wiper",
            2: "panel/horn",
            3: "panel/right_upper_front_light",
            4: "panel/left_upper_front_light",
            5: "panel/right_down_front_light",
            6: "panel/left_down_front_light",
            7: "panel/status",
            8: "panel/error",
        }
        self.signals={
        "panel/wiper": [False,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0x1])],
        "panel/horn": [False,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0x2])],
        "panel/right_upper_front_light": [False,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0x3])],
        "panel/left_upper_front_light": [False,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0x4])],
        "panel/right_down_front_light": [False,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0x5])],
        "panel/left_down_front_light": [False,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0x6])],
        "panel/status": [False,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0x7])],
        "panel/error": [False,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0x8])],
        }
        self.bus = can.interface.Bus(bustype='socketcan', channel='can1', bitrate=500000)
        self.data_start = 8
        self.bit_len = 6
        self.bit_panel_array=[]
        self.pub_panel_status = self.create_publisher(PanelMsg, 'panel/status', 10)
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
    def decimalToBinary(self,ip_val):
        if ip_val >= 1:
            self.decimalToBinary(ip_val // 2)
        self.bit_panel_array.append(ip_val % 2)
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
                    msg.wiper.data = self.signals["panel/wiper"][0]
                    msg.horn.data = self.signals["panel/horn"][0]
                    msg.right_upper_front_light.data = self.signals["panel/right_upper_front_light"][0]
                    msg.left_upper_front_light.data = self.signals["panel/left_upper_front_light"][0]
                    msg.right_down_front_light.data = self.signals["panel/right_down_front_light"][0]
                    msg.left_down_front_light.data = self.signals["panel/left_down_front_light"][0]
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
