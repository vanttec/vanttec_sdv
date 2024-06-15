#!/usr/bin/env python3

# do not launch this node alone unless you know what you are doing
# you are better of launching 'remote_steer.launch.py'

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy
from std_msgs.msg import Float64, Bool
from sdv_msgs.srv import Uint8
from functools import partial

import math

class RemoteMapping(Node):

    def __init__(self):
        super().__init__('remote_joystick_mapping_node')
        self.jsub = self.create_subscription(Joy, '/joy', self.convert, 10)
        self.jsub

        self.steer_pub = self.create_publisher(Float64, '/sdv/steering/setpoint', 10)
        self.steer_pub
        self.steer_msg = Float64()

        self.throttle_pub = self.create_publisher(Float64, '/sdv/velocity/throttle', 10)
        self.throttle_pub
        self.throttle_msg = Float64()

        self.set_mode_srv = self.create_client(Uint8, '/sdv/steering/set_mode')
        self.set_mode_srv
        self.mode_req = Uint8.Request()
        self.mode_req.data = 1 # manual mode on default

        self.set_lightshow_srv = self.create_client(Uint8, '/sdv/steering/activate/lightshow')
        self.set_lightshow_srv
        self.lightshow_req = Uint8.Request()
        self.lightshow_req.data = 0
        self.light_back = True

        self.delta_dt = 0.15
        self.curr_steer = 0.
        self.past_steer = 0.
        self.curr_throttle = 0.
        self.past_throttle = 0.

        self.dropout = 0.01

    def convert(self, msg):
        #[DEBUG]
        #msg.axes - son los valores de los joysticks
        #msg.buttons - son los valores de los botones

        joystick_axes_index = 0 # Left/Right Axis stick left 
        accel_axes_index = 2 # Left/Right Axis stick left 
        braking_axes_index = 5 # Left/Right Axis stick left 
        mode_button_index = 6  # boton back
        light_button_index = 3 # boton Y


        # modify steer setpoint
        steer_delta = -msg.axes[joystick_axes_index]
        self.curr_steer += steer_delta * self.delta_dt
        self.curr_steer = max(-3 * math.pi, min(self.curr_steer, 3 * math.pi))

        if abs(self.curr_steer - self.past_steer) < self.dropout:
            self.curr_steer = self.past_steer
        self.past_steer = self.curr_steer

        self.steer_msg.data = self.curr_steer
        self.steer_pub.publish(self.steer_msg)


        # modify throttle setpoint
        throttle_delta = msg.axes[accel_axes_index] - msg.axes[braking_axes_index]
        self.curr_throttle += throttle_delta * self.delta_dt
        self.curr_throttle = max(-1., min(self.curr_throttle, 1.))

        if abs(self.curr_throttle - self.past_throttle) < self.dropout:
            self.curr_throttle = self.past_throttle
        self.past_throttle = self.curr_throttle

        self.throttle_msg.data = self.curr_throttle
        self.throttle_pub.publish(self.throttle_msg)


        # toggle operating mode
        if msg.buttons[mode_button_index]:
            # [DEBUG] dumb way to toggle between 0 & 1
            self.mode_req.data = 1 - self.mode_req.data

            future = self.set_mode_srv.call_async(self.mode_req)
            future.add_done_callback( self.callback_done )
        

        # toggle light show
        if msg.buttons[light_button_index]:
            if self.light_back:
                self.lightshow_req.data = 1 - self.lightshow_req.data
                
                future = self.set_lightshow_srv.call_async(self.lightshow_req)
                future.add_done_callback( self.callback_done )
                self.light_back = False
        else:
            self.light_back = True


    def callback_done(self, msg):
        self.get_logger().info('CAN service called')



def main(args=None):
    rclpy.init(args=args)

    rmn = RemoteMapping()

    rclpy.spin(rmn)

    rmn.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
