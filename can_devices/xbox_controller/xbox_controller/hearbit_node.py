#! /usr/bin/env python
import rclpy
from rclpy.node import Node

class Heartbeat(Node):
    def __init__(self):
        super().__init__('Heartbit node started')      
        self.timer = self.create_timer(0.1, self.timer_callback)

    def timer_callback(self):
        #Analyse if any module stopped transmitting heartbeat counter
        print("")

def main(args=None):
    rclpy.init(args=args)

    heartbeat = Heartbeat()
    heartbeat.get_logger().info('Heartbeat node started')
    rclpy.spin(heartbit)
    heartbeat.destroy_node()
    rclpy.shutdown()
            
if __name__ == "__main__":
    
    main()
