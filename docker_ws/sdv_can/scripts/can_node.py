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
from std_msgs.msg import UInt8, Float32, String
import can
import struct

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
            '/sdc_control/control_signal/D',
            self.throttle_callback,
            1)
        self.steer_sub = self.create_subscription(
            Float32,
            '/sdc_control/control_signal/delta',
            self.steering_callback,
            1)

        self.auto_mode_sub = self.create_subscription(
            String,
            '/sdv/xbox_controller/auto_mode',
            self.auto_mode_callback,
            1)
        self.drive_mode_sub = self.create_subscription(
            String,
            '/sdv/drive_mode',
            self.drive_mode_callback,
            1)

        self.emergency_stop_sub = self.create_subscription(
            String,
            '/sdv/emergency_stop',
            self.emergency_stop_callback,
            1)
        
        self.throttle = -1
        self.wheel_angle = -2
        self.auto_mode = "Joystick_Controller"
        self.prev_auto_mode = "Joystick_Controller"
        self.emergency_stop = "Deactivated"
        self.drive_mode = "Manual"

        # self.prev_delta_angle = 0
        # *------------------* VANTTEC_IDS *------------------*
        self.admin_id = 0x401
        self.general_module_id_tx = 0x403
        self.general_module_id_rx = 0x404
        self.throttle_module_id = 0x406
        self.steering_module_id = 0x408
        self.braking_module_id = 0x412
        self.steer_task_id_control = 0x00

        self.car_messages= {
                "throttle": can.Message(arbitration_id=self.throttle_module_id,is_extended_id=False, data=[0x5,0x1]),
                }

    def emergency_stop_callback(self, msg):
        self.emergency_stop = msg.data

    def auto_mode_callback(self, msg):
        self.auto_mode = msg.data
    def drive_mode_callback(self, msg):
        self.drive_mode = msg.data

    def throttle_callback(self, msg):
        if self.emergency_stop=="Deactivated":
            if self.drive_mode == "Automatic":
                if self.auto_mode == "Setpoint_Controller":
                    if(msg.data != self.throttle):
                        self.car_messages["throttle"].data[1] = msg.data
                        self.bus.send(self.car_messages["throttle"],timeout=0.01)
                        self.throttle = msg.data

    def steering_callback(self, delta):
        # Steering to steering wheel relation:
        # delta in rads
        # wheel angle in degrees
        # delta = 0.0658 * wheel / 57.2958

        # REAL MAX DELTA = 31 degrees = 0.541052 rads
        # REAL MIN DELTA = -22.5 degrees = -0.3926991 rads

        delta_to_wheel = 0.0658 / 57.2958 # relationship delta in degrees - wheel in radians

        # MAKE SURE THESE STEERING WHEEL VALS ARE THE SAME AS IN THE STEERING PCB!!!!!
        MAX_STEERING_WHEEL_ANGLE = 550 # degrees
        MIN_STEERING_WHEEL_ANGLE = -360 # degrees

        # ERROR_OFFSET_RAD = 10 / 57.295

        # If the difference between consecutive delta angles is too low, do not publish it
        # if(abs(delta.data - self.prev_delta_angle) < ERROR_OFFSET_RAD):


        # WHEN delta.data = 0.541052 the result is less than 700, which is the real max steering wheel angle, so it is safe
        delta_angle = delta.data


        if(delta_angle > MAX_STEERING_WHEEL_ANGLE):
            delta_angle = MAX_STEERING_WHEEL_ANGLE
        elif(delta_angle < MIN_STEERING_WHEEL_ANGLE):
            delta_angle = MIN_STEERING_WHEEL_ANGLE

        wheel_angle = delta_angle / delta_to_wheel # degrees

        normalized_wheel_angle = wheel_angle / MAX_STEERING_WHEEL_ANGLE if delta_angle >= 0 else wheel_angle / -MIN_STEERING_WHEEL_ANGLE

        # self.get_logger().info("Wheel angle = %f" % wheel_angle)
        # self.get_logger().info("Normalized wheel angle = " + str(normalized_wheel_angle))

        self.prev_delta_angle = delta_angle
        
        if self.emergency_stop=="Deactivated":
            if self.drive_mode == "Automatic":
                if self.prev_auto_mode == "Joystick_Controller" and self.auto_mode =="Setpoint_Controller":
                        steer_data = bytearray(struct.pack("f", normalized_wheel_angle))
                        #Insert ID so it can select the proper STM32 Task
                        steer_data.insert(0, self.steer_task_id_control)
                        self.bus.send(can.Message(arbitration_id=self.steering_module_id,is_extended_id=False, data=steer_data), timeout=0.1)
                        self.wheel_angle = normalized_wheel_angle
                else:
                    if self.auto_mode == "Setpoint_Controller":
                        self.get_logger().info("Normalized wheel angle = %f" % normalized_wheel_angle)
                        self.get_logger().info("In degrees wheel angle = %f" % wheel_angle)
                        if(normalized_wheel_angle != self.wheel_angle):
                            steer_data = bytearray(struct.pack("f", normalized_wheel_angle))
                            #Insert ID so it can select the proper STM32 Task
                            steer_data.insert(0, self.steer_task_id_control)
                            self.bus.send(can.Message(arbitration_id=self.steering_module_id,is_extended_id=False, data=steer_data), timeout=0.1)
                            self.wheel_angle = normalized_wheel_angle
                self.prev_auto_mode = self.auto_mode


def main(args=None):
    rclpy.init(args=args)
    sdv_control_node = SDVControlNode()
    rclpy.spin(sdv_control_node)
    sdv_control_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
