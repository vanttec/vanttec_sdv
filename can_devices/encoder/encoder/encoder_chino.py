#!/usr/bin/env python
import can
import time
import rclpy
from rclpy.node import Node
from std_msgs.msg import Int32, Int16, Float64

class EncoderPublisher(Node):

    def __init__(self):
        super().__init__('encoder_rm')
        self.publisher_absolute_pos = self.create_publisher(Int32, 'encoder/abs_pos', 10)
        # self.publisher_turn_number = self.create_publisher(Int16, 'encoder/turn_num', 10)
        self.publisher_angle = self.create_publisher(Float64, 'encoder/angle', 10)
        timer_period = 0.01 #Seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.bus = can.interface.Bus(bustype='socketcan', channel='can0', bitrate=500000)

        self.sendMsg = can.Message(arbitration_id=1, is_extended_id=False, data=[0x04, 0x01, 0x01, 0x00])

        self.steps = 4096
        self.degrees = 360

    def timer_callback(self):
        absPos = Int32()
        # turNum = Int16()
        angle = Float64()
        self.bus.send(self.sendMsg, timeout=1)
        receivedMsg = self.bus.recv(1)

        if receivedMsg is not None:
            if receivedMsg.is_rx:

                d = int( (msg.data.hex()[6:])[::-1], 16)
                absPos.data = d
                
                decimal = d / 65535 # 0 - 1
                angle.data = decimal * degrees # 0 - 360
                
                self.publisher_absolute_pos.publish(absPos)
                # self.publisher_turn_number.publish(turNum)
                self.publisher_angle.publish(angle)

    def cambiar_id(self, id, new):
        # command 0x02 - change device id
        msg = can.Message(arbitration_id=1, is_extended_id=False, data=[0x04, id, 0x02, new])
        self.bus.send( msg, timeout=1 )

    def query_mode(self, id):
        # command 0x04 - set encoder to query mode
        msg = can.Message(arbitration_id=1, is_extended_id=False, data=[0x04, id, 0x04, 0x00])
        self.bus.send( msg, timeout=1 )


    
def main(args=None):
    rclpy.init(args=args)

    encoder_publisher = EncoderPublisher()

    rclpy.spin(encoder_publisher)

    encoder_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()
