#!/usr/bin/env python3
''' ----------------------------------------------------------------------------
 * @file: can_node.py
 * @date: August 14, 2023
 * @author: Edison Altamirano
 *
 * @brief: CAN node to send throttle, brake, and steering commands to the canbus
 * -----------------------------------------------------------------------------
'''

import rclpy
from rclpy.node import Node
from std_msgs.msg import UInt8, Float32
import can

class SDVControlNode(Node):
    def __init__(self):
        super().__init__('can_node')
        self.declare_parameter('channel', rclpy.Parameter.Type.STRING)
        self.declare_parameter('bitrate', rclpy.Parameter.Type.INTEGER)

        channel = self.get_parameter('channel').value
        bitrate = self.get_parameter('bitrate').value

        self.bus = can.interface.Bus(bustype='socketcan', channel=channel, bitrate=bitrate)

        # Initialize subscriber
        self.throttle_sub = self.create_subscription(
            UInt8,
            '/car_control/control_signal/D',
            self.throttle_callback,
            1)
        self.steer_sub = self.create_subscription(
            Float32,
            '/car_control/control_signal/Delta',
            self.steering_callback,
            1)

        self.throttle = -1
        self.steer = -2
        # *------------------* VANTTEC_IDS *------------------*
        self.admin_id = 0x401
        self.general_module_id_tx = 0x403
        self.general_module_id_rx = 0x404
        self.throttle_module_id = 0x406
        self.steering_module_id = 0x408
        self.braking_module_id = 0x412

        self.car_messages= {
                "throttle": can.Message(arbitration_id=self.throttle_module_id,is_extended_id=False, data=[0x5,0x1]),
                "steering": can.Message(arbitration_id=self.steering_module_id,is_extended_id=False, data=[0x00,0x00]),
            }

    def throttle_callback(self, msg):
        if(msg.data != self.throttle):
            self.car_messages["throttle"].data[1] = msg.data
            self.bus.send(self.car_messages["throttle"],timeout=0.01)
            self.throttle = msg.data

    def steering_callback(self, msg):
        if(msg.data != self.steer):
            self.car_messages["steering"].data[1] = msg.data
            self.bus.send(self.car_messages["steering"],timeout=0.01)
            self.steer = msg.data



def main(args=None):
    rclpy.init(args=args)
    sdv_control_node = SDVControlNode()
    rclpy.spin(sdv_control_node)
    sdv_control_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
