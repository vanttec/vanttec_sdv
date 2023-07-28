#! /usr/bin/env python
import rclpy
from rclpy.node import Node
import can
from  std_msgs.msg import BoolMultiArray
class Heartbeat(Node):
    def __init__(self):
        super().__init__('Heartbit node started')      
        self.timer = self.create_timer(0.1, self.timer_callback)
        self.bus = can.interface.Bus(bustype='socketcan', channel='can0', bitrate=125000, can_filters=filters)
        self.timeout = 3
        self.module_pub = self.create_publisher(Marker,"/sdv/diagnostics/module_status", 2)
        self.module_msg = BoolMultiArray()

        # *------------------* VANTTEC_IDS-TX *------------------*
        #Dict -> key: Module, value:[name,bool if module has died, actual time , prev time]
        self.module_status = {
           0x403: ["general",False,0,0],
           0x405: ["throttle", False,0,0],
           0x407: ["panel", False,0,0],
           0x409: ["steering", False,0,0],
           0x411: ["brake", False,0,0]
        }

    def timer_callback(self):
        #Analyse if any module stopped transmitting heartbeat counter
        print("")
        msg =  self.bus.recv(1)
        if msg is not None:
            if msg.arbitration_id in module_status:  
                self.module_status[msg.arbitration_id][2] = self.get_clock().now().to_msg().sec
                if self.module_status[msg.arbitration_id][2] - self.module_status[msg.arbitration_id][3] >= self.timeout:
                    #Module not activated
                    self.module_status[msg.arbitration_id][1] = False
                else:
                    #Module activated
                    self.module_status[msg.arbitration_id][1] = True
                self.module_status[msg.arbitration_id][3] = self.module_status[msg.arbitration_id][2]
                self.module_msg.data = [value[1] for value in a.values()]
                self.module_pub.publish(self.module_msg)

def main(args=None):
    rclpy.init(args=args)

    heartbeat = Heartbeat()
    heartbeat.get_logger().info('Heartbeat node started')
    rclpy.spin(heartbit)
    heartbeat.destroy_node()
    rclpy.shutdown()
            
if __name__ == "__main__":
    
    main()
