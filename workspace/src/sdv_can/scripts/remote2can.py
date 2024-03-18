#!/usr/bin/env python3

# do not launch this node alone unless you know what you are doing
# you are better of launching 'remote_steer.launch.py'

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy
from std_msgs.msg import Float64

import math

class RemoteMapping(Node):

    def __init__(self):
        super().__init__('remote_joystick_mapping_node')
        self.jsub = self.create_subscription(
            Joy, '/joy', self.convert, 10
        )
        self.jsub

        # no me gustan los yams la verdad jajas
        self.fpub = self.create_publisher(Float64, "sdv/steering/setpoint", 10)
        self.fpub

        self.angle_increment = 0.15
        self.curr_angle = 0.0
        self.past_angle = 0.0

        self.dropout = 0.01

    def convert(self, msg):

        #TODO modify dead zones??

        #msg.axes - son los valores de los joysticks
        #msg.buttons - son los valores de los botones

        joystick_index = 0

        #[DEBUG] le ponemos un `-` para que la izquierda sea negativo y viceversa
        delta = -msg.axes[joystick_index]
        self.curr_angle += delta * self.angle_increment
        self.curr_angle = max(-3 * math.pi, min(self.curr_angle, 3 * math.pi))

        if abs(self.curr_angle - self.past_angle) < self.dropout:
            self.curr_angle = self.past_angle

        f64_msg = Float64()
        f64_msg.data = self.curr_angle

        self.get_logger().debug('joystick: "%d"' % self.curr_angle)

        self.fpub.publish(f64_msg)

        self.past_angle = self.curr_angle


def main(args=None):
    rclpy.init(args=args)

    rmn = RemoteMapping()

    rclpy.spin(rmn)

    rmn.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
