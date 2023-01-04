#!/usr/bin/env python
import can
import time
import rclpy
from rclpy.node import Node
from sdv_msg.msg import ThrottleMsg
from std_msgs.msg import String
from numpy import interp

class ThrottleModule(Node):
    def __init__(self):
        super().__init__('panel_module')
        #Send WiperPot position
        self.pot_id = 820 #hex.334
        #Send Max velocity
        self.max_id = 821 #hex.335
        self.receive_id = 547 #hex.223
        self.old_maxvel = 80
        self.new_maxvel = 80 #Can not surpass 80km/h       
        self.signals={
        "max_velocity": [0,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0x0])],
        "pot_position": [0,can.Message(arbitration_id=self.send_id,is_extended_id=False, data=[0x0, 0x0, 0x0, 0x0])]
        }
        self.bus = can.interface.Bus(bustype='socketcan', channel='can1', bitrate=500000)
        self.pub_throttle_status = self.create_publisher(ThrottleMsg, 'throttle/status', 10)

        #Sub to change max velocity and position (Auto Mode)
        self.sub_throttle = self.create_subscription(
            ThrottleMsg,
            'xbox_throttle/control',
            self.throttle_callback,
            10
        )
        self.old_increase_maxvel = 0 
        self.increase_maxvel = 0 
        self.old_decrease_maxvel = 0 
        self.decrease_maxvel = 0
        self.new_pot = 0
        self.old_pot = 0 
        self.limit_pot = 0

    def throttle_callback(self,msg):
        #Detect down bottom to decrease velocity
        if self.old_decrease_maxvel == 0 and bool(msg.decrease_maxvel.data):
            self.old_decrease_maxvel = bool(msg.decrease_maxvel.data)
            self.decrease_maxvel=0  if self.decrease_maxvel else 1
        else:
            self.old_decrease_maxvel =bool(msg.decrease_maxvel.data)
        #Detect up button to increase velocity    
        if self.old_increase_maxvel == 0 and bool(msg.increase_maxvel.data):
            self.old_increase_maxvel = bool(msg.increase_maxvel.data)
            self.increase_maxvel=0  if self.increase_maxvel else 1
        else:
            self.old_increase_maxvel =bool(msg.increase_maxvel.data)
        #Change max velocity
        if self.increase_maxvel:
            self.new_maxvel+=5
        if self.decrease_maxvel:
            self.new_maxvel-=5
        if self.old_maxvel!=self.new_maxvel:
            self.limit_pot = interp(self.new_maxvel, [0,80], [0,127])
            new_pos  = (lambda x, y: (int(x), int(x*y) % y/y))(self.limit_pot, 1e7)
            integer = new_pos[0]
            decimal =  hex(int(new_pos[1]*1e7))[2:]
            dec1 = int(decimal[:2],base=16)
            dec2 = int(decimal[2:4],base=16)
            dec3 = int(decimal[4:6],base=16)
            self.old_maxvel=self.new_maxvel
            self.bus.send(can.Message(arbitration_id=self.max_id,is_extended_id=False, data=[integer, dec1, dec2, dec3]), timeout=1)
        #Change pot position
        self.new_pot = msg.data.pot
        if self.new_pot!=self.old_pot:
            temp_pos = interp(self.new_pot, [0,1], [0,self.limit_pot])
            new_pos  = (lambda x, y: (int(x), int(x*y) % y/y))(temp_pos, 1e7)
            integer = new_pos[0]
            decimal =  hex(int(new_pos[1]*1e7))[2:]
            dec1 = int(decimal[:2],base=16)
            dec2 = int(decimal[2:4],base=16)
            dec3 = int(decimal[4:6],base=16)
            self.old_pot=self.new_pot
            self.bus.send(can.Message(arbitration_id=self.pot_id,is_extended_id=False,  data=[integer, dec1, dec2, dec3]), timeout=1)

   

def main(args=None):
    rclpy.init(args=args)

    panel = ThrottleModule()
    panel.get_logger().info('Throttle node started')
    rclpy.spin(panel)
    panel.destroy_node()
    rclpy.shutdown()
            
if __name__ == "__main__":
    
    main()
