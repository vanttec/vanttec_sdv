#!/usr/bin/env python3

# do not launch this node alone unless you know what you are doing
# you are better of launching 'remote_steer.launch.py'

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy

import can

class Remote2CAN(Node):

    def __init__(self):
        super().__init__('remote_joystick_to_can')
        self.subscription = self.create_subscription(
            Joy, '/joy', self.convert, 10
        )
        self.subscription

        self.steering_module_id = 0x408
        self.steer_task_id_xbox = 0x08

        # TODO cambiar a can1 en la jetson???
        self.bus = can.interface.Bus(bustype='socketcan', channel='can0', bitrate=125000)

    def convert(self, msg):

        #TODO modify dead zones??

        #msg.axes - son los valores de los joysticks
        #msg.buttons - son los valores de los botones

        #DEBUG le ponemos un `-` para que la izquierda sea negativo y viceversa 
        d = -msg.axes[0] # direccion

        self.get_logger().debug('joystick: "%d"' % d)

        if d > 0: # derecha
            d = 0
        elif d < 0:
            d = 1
        else:
            d = 2

        cmsg = can.Message(
            arbitration_id = self.steering_module_id,
            is_extended_id = False,
            data = [ self.steer_task_id_xbox, int(d) ]
        )

        self.bus.send(cmsg, timeout=0.1)

def main(args=None):
    rclpy.init(args=args)

    r2c = Remote2CAN()

    rclpy.spin(r2c)

    r2c.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()