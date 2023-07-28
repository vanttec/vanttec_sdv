#!/usr/bin/env python3

import os
import csv

import rclpy
from rclpy.node import Node

from sdv_msgs.msg import Encoder
from vectornav_msgs.msg import CommonGroup, InsGroup, ImuGroup

#include "vectornav_msgs/msg/attitude_group.hpp"
#include "vectornav_msgs/msg/common_group.hpp"
#include "vectornav_msgs/msg/gps_group.hpp"
#include "vectornav_msgs/msg/imu_group.hpp"
#include "vectornav_msgs/msg/ins_group.hpp"
#include "vectornav_msgs/msg/time_group.hpp"


class IMU2CSV(Node):

    def __init__(self):
        super().__init__('to_csv_node')

        self.common_sub_ = self.create_subscription( CommonGroup, 'vectornav/raw/common',
                                                      self.save_common, 10)
        self.ins_sub_ = self.create_subscription( InsGroup, 'vectornav/raw/ins',
                                                      self.save_ins, 10)
        self.wheel_encoder_sub_ = self.create_subscription( Encoder, 'ifm_encoder',
                                                      self.save_wheel_encoder, 10)
        # self.imu_sub_ = self.create_subscription( String, 'vectornav/raw/imu',
        #                                               self.save_imu, 10)
        # self.gps2_sub_ = self.create_subscription( String, 'vectornav/raw/gps2',
        #                                               self.save_gps, 10)
        # self.attitude_sub_ = self.create_subscription( String, 'vectornav/raw/attitude',
        #                                               self.save_attitude, 10)

        self.is_msg_arrived_ = False

        test = 'step90'

        self.accel_file_path_ = '/home/ws/src/tests/' + test + '/accel_data.csv'
        self.accel_file_ = open(self.accel_file_path_, 'w')
        self.accel_file_writer_ = csv.writer(self.accel_file_)
        self.accel_file_writer_.writerow(['Time', 'AccelBody(x)','AccelBody(y)','AccelBody(z)', 'Psi'])

        self.vel_file_path_ = '/home/ws/src/tests/' + test + '/vel_data.csv'
        self.vel_file_ = open(self.vel_file_path_, 'w')
        self.vel_file_writer_ = csv.writer(self.vel_file_)
        self.vel_file_writer_.writerow(['Time', 'VelBody(x)','VelBody(y)','VelBody(z)'])

        self.encoder_file_path_ = '/home/ws/src/tests/' + test + '/encoder_data.csv'
        self.encoder_file_ = open(self.encoder_file_path_, 'w')
        self.encoder_file_writer_ = csv.writer(self.encoder_file_)
        self.encoder_file_writer_.writerow(['Time', 'WheelAngle'])

        # self.vel_file_writer_.writerow(['Time', 'AccelBody(x)','AccelBody(y)','AccelBody(z)', 'VelBody', 'WheelAngle', 'Psi (yaw)'])

    def save_common(self, msg):
        if not self.is_msg_arrived_:
            self.is_msg_arrived_ = True
            self.start_time_ = self.get_clock().now()

        elapsed_time = self.get_clock().now() - self.start_time_
        self.accel_file_writer_.writerow([elapsed_time.nanoseconds / 1e9, msg.accel.x, msg.accel.y, msg.accel.z, msg.yawpitchroll.x])

    def save_ins(self, msg):
        if not self.is_msg_arrived_:
            self.is_msg_arrived_ = True
            self.start_time_ = self.get_clock().now()

        elapsed_time = self.get_clock().now() - self.start_time_
        self.vel_file_writer_.writerow([elapsed_time.nanoseconds / 1e9, msg.velbody.x, msg.velbody.y, msg.velbody.z])

    def save_wheel_encoder(self, msg):
        if not self.is_msg_arrived_:
            self.is_msg_arrived_ = True
            self.start_time_ = self.get_clock().now()

        elapsed_time = self.get_clock().now() - self.start_time_
        self.encoder_file_writer_.writerow([elapsed_time.nanoseconds / 1e9, msg.abs_angle])

    # def save_imu(self, msg):
    #     pass

    # def save_gps(self, msg):
    #     pass

    # def save_attitude(self, msg):
    #     pass


    def close(self):
        self.accel_file_.close()
        self.vel_file_.close()
        self.encoder_file_.close()

def main(args=None):
    rclpy.init(args=args)

    to_csv = IMU2CSV()

    rclpy.spin(to_csv)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    to_csv.destroy_node()
    to_csv.close()
    rclpy.shutdown()


if __name__ == '__main__':
    main()