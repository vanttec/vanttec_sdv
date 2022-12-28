#!/usr/bin/env python
import can
import time
import rclpy
from rclpy.node import Node
from sdv_msg.msg import ThrottleMsg
from std_msgs.msg import String


class ThrottleModule(Node):
    def __init__(self):
        super().__init__('panel_module')
        #Send WiperPot position
        self.pot_id = 820 #hex.334
        #Send Max velocity
        self.max_id = 821 #hex.335
        self.receive_id = 547 #hex.223
        self.safe_velocity = 80 #Can not surpass 80km/h       
        self.signals={
        "max_velocity": [0,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0x0])],
        "pot_position": [0,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0x0])]
        }
        self.bus = can.interface.Bus(bustype='socketcan', channel='can1', bitrate=500000)
        self.pub_throttle_status = self.create_publisher(ThrottleMsg, 'throttle/status', 10)
        #Sub to activate multiple led with SDV Message
        self.sub_leds_panel = self.create_subscription(
           PanelMsg,
           'xbox_panel/control',
            self.xbox_callback,
            10
        )
        #Sub to change max velocity and position (Auto Mode)
        self.sub_throttle = self.create_subscription(
            ThrottleMsg,
            'xbox_throttle/control',
            self.throttle_callback,
            10
        )

    def throttle_callback(self,msg):
        if self.old_inverse_led == 0 and bool(msg.back.data):
            self.old_inverse_led = bool(msg.back.data)
            self.inverse_led=0  if self.inverse_led else 1
        else:
            self.old_inverse_led =bool(msg.back.data)
        if self.old_maxvel!=self.new_maxvel:
            self.bus.send(can.Message(arbitration_id=self.max_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0x0]), timeout=1)
        if self.new_pot!=self.old_pot:
            self.bus.send(can.Message(arbitration_id=self.pot_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0x0]), timeout=1)

   

def main(args=None):
    rclpy.init(args=args)

    panel = ThrottleModule()
    panel.get_logger().info('Throttle node started')
    rclpy.spin(panel)
    panel.destroy_node()
    rclpy.shutdown()
            
if __name__ == "__main__":
    
    main()
