#!/usr/bin/env python

import can
import rclpy
from rclpy.node import Node
from std_msgs.msg import Int32, Int16, Float64
from sdv_msg.msg import Encoder

class RM8004Encoder(Node):

    def __init__(self):
        super().__init__('encoder_rm8004')

        # IFM RM8004 Encoder params
        self.steps = 4096
        self.revolutions = 4096
        self.degrees = 360
        self.encoder_data = Encoder()

        # CANBus
        self.bus = can.interface.Bus(bustype='socketcan', channel='can0', bitrate=125000)
        # self.sendMsg = can.Message(arbitration_id=1568,is_extended_id=False, data=[0x43, 0x04, 0x60, 0x0])
        self.start_msg = can.Message(arbitration_id=000,is_extended_id=False, data=[0x01, 0x00])

        # Publishers
        self.encoder_pub = self.create_publisher(Encoder, 'ifm_encoder', 10)

        timer_period = 0.01 #Seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        
        self.bus.send(self.start_msg, timeout=1)

    def timer_callback(self):
        absolute_position = Int32()
        turn_number = Int16()
        abs_angle = Float64()
        angle = Float64()
        msg = self.bus.recv(1)

        if msg is not None:
            coded_msg = msg.data
            decoded_msg = coded_msg.hex()
            hex_pos = (decoded_msg[4:6]+decoded_msg[2:4]+decoded_msg[0:2])
            decimal_pos = int(hex_pos, 16)
            absolute_position.data = decimal_pos
            step = decimal_pos%self.steps

            self.encoder_data.turn = decimal_pos//self.steps
            self.encoder_data.abs_angle = float(self.degrees*decimal_pos/self.revolutions)
            self.encoder_data.angle = float(self.degrees*step/self.steps)

            # self.get_logger().info("Position: %d" %decimal_pos)
            # self.get_logger().info("Step: %d" %step)
            # self.get_logger().info("Turn: %d" %turn_number.data)
            # self.get_logger().info("Angle: %d" %angle.data)
            # self.get_logger().info("Abs angle: %d" %abs_angle)

            self.encoder_pub.publish(self.encoder_data)

def main(args=None):
    rclpy.init(args=args)
    encoder_publisher = RM8004Encoder()
    rclpy.spin(encoder_publisher)
    encoder_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()