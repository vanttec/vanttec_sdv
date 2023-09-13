#!/usr/bin/env python3

import can
import can.interfaces.socketcan as socketcan
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
from sdv_msgs.msg import Encoder

class RM8004Encoder(Node):

    def __init__(self):
        super().__init__('encoder_rm8004')

        # IFM RM8004 Encoder params
        self.steps = 4096
        self.revolutions = 4096
        self.degrees = 360
        self.encoder_data = Encoder()
        self.encoder_id = 0x20
        self.bit_res = 16777216 #2^24

        # Car steering params
        self.declare_parameter('channel', rclpy.Parameter.Type.STRING)
        self.declare_parameter('bitrate', rclpy.Parameter.Type.INTEGER)

        channel = self.get_parameter('channel').value
        bitrate = self.get_parameter('bitrate').value

        self.get_logger().info("%s" %channel)
        self.get_logger().info("%s" %bitrate)

        self.car_steering_range = 1279 #degrees
        self.car_steering_range_pos = self.car_steering_range*self.revolutions//self.degrees

        # Publishers
        self.encoder_pub = self.create_publisher(Encoder, '/ifm_encoder', 10)
        self.steering_pub = self.create_publisher(Float32, '/sdc_state/steering', 10)

        timer_period = 0.01 #Seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        
        # CANBus
        filters = [
            {"can_id": 0x1A0, "can_mask": 0x1A0, "extended": False}
        ]
        self.bus = can.interface.Bus(bustype='socketcan', channel=channel, bitrate=bitrate, can_filters=filters)
        start_msg = can.Message(arbitration_id=000,is_extended_id=False, data=[0x01, 0x00]) # to enter operational mode

        # get_pos_msg = can.Message(arbitration_id=0x600+self.encoder_id,is_extended_id=False, data=[0x43, 0x04, 0x60, 0x0])

        # self.bus.send(get_pos_msg, timeout=1)
        # received_msg = self.bus.recv(1)

        # while received_msg is None:
        #     received_msg = self.bus.recv(1)
        
        # coded_msg = received_msg.data
        # decoded_msg = coded_msg.hex()
        # hex_pos = (decoded_msg[6:7]+decoded_msg[4:6]+decoded_msg[2:4]+decoded_msg[0:2])
        # absolute_pos = int(hex_pos, 16)

        # if(absolute_pos > self.car_steering_range_pos):
        #     preset_val_msg = can.Message(arbitration_id=0x600+self.encoder_id,is_extended_id=False, data=[0x23, 0x03, 0x60, 0x0, 0x0, 0x0, 0x0])
        #     self.bus.send(start_msg, timeout=1)
        #     save_msg = can.Message(arbitration_id=0x600+self.encoder_id,is_extended_id=False, data=[0x23, 0x10, 0x10, 0x01, 0x73, 0x61, 0x76, 0x65])
        #     self.bus.send(save_msg, timeout=1)

        self.bus.send(start_msg, timeout=1)


    def timer_callback(self):
        msg = self.bus.recv(0.05)
        if msg is not None:
            if msg.arbitration_id == 0x1A0:     #Si recibe el 0A0, algo est[a] mal
                coded_msg = msg.data
                decoded_msg = coded_msg.hex()
                hex_pos = (decoded_msg[6:7]+decoded_msg[4:6]+decoded_msg[2:4]+decoded_msg[0:2])
                absolute_pos = int(hex_pos, 16)
                step = absolute_pos%self.steps
                
                # To account when encoder pos is outside the total max steering angle

                # if(abs_angle > self.car_steering_range):
                #     offset = self.car_steering_range_pos*(absolute_pos//self.steps)
                #     self.get_logger().info("Offset: %d\n" % offset)
                #     absolute_pos  = absolute_pos - offset

                # To set to [-angle,+angle] range
                if absolute_pos > self.bit_res/2: #2^24 /2
                    absolute_pos = absolute_pos - self.bit_res
                    step = step - self.steps

                abs_angle = float(self.degrees*absolute_pos/self.revolutions)

                # Results are negative to account for gears

                self.encoder_data.turn = -absolute_pos//self.steps
                self.encoder_data.abs_angle = -abs_angle
                self.encoder_data.angle = -float(self.degrees*step/self.steps)

                # self.get_logger().info("Step: %d" %step)
                # self.get_logger().info("Turn: %d" %self.encoder_data.turn)
                # self.get_logger().info("Angle: %d" %self.encoder_data.angle)
                # self.get_logger().info("Abs angle: %d" %self.encoder_data.abs_angle)

                self.encoder_pub.publish(self.encoder_data)

                delta_angle = Float32()
                delta_angle.data = self.encoder_data.abs_angle * 0.0454 # degrees
                self.steering_pub.publish(delta_angle)

def main(args=None):
    rclpy.init(args=args)
    encoder_publisher = RM8004Encoder()
    rclpy.spin(encoder_publisher)
    encoder_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()