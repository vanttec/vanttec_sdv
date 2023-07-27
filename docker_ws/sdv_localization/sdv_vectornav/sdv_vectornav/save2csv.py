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
        # self.ins_sub_ = self.create_subscription( InsGroup, 'vectornav/raw/ins',
        #                                               self.save_ins, 10)
        # self.wheel_encoder_sub_ = self.create_subscription( Encoder, 'ifm_encoder',
        #                                               self.save_encoder, 10)
        # self.imu_sub_ = self.create_subscription( String, 'vectornav/raw/imu',
        #                                               self.save_imu, 10)
        # self.gps2_sub_ = self.create_subscription( String, 'vectornav/raw/gps2',
        #                                               self.save_gps, 10)
        # self.attitude_sub_ = self.create_subscription( String, 'vectornav/raw/attitude',
        #                                               self.save_attitude, 10)

        self.are_msg_arrived_ = False

        self.csv_file_path_ = '/home/ws/src/tests/imu_data.csv'
        self.csv_file_ = open(self.csv_file_path_, 'w')
        self.csv_writer_ = csv.writer(self.csv_file_)
        self.csv_writer_.writerow(['Time', 'AccelBody', 'VelBody', 'WheelAngle', 'Psi (yaw)'])

    def save_common(self, msg):
        if not self.are_msg_arrived_:
            self.are_msg_arrived_ = True
            self.start_time_ = self.get_clock().now()

        # self.csv_writer_.writerow([msg.header.stamp.sec, msg.accel, 0, 0, 0])
        elapsed_time = self.get_clock().now() - self.start_time_
        self.csv_writer_.writerow([elapsed_time.nanoseconds / 1e9, msg.accel, 0, 0, 0])

    def save_time(self, msg):
        self.get_logger().info('I heard: "%s"' % msg.data)

    def save_imu(self, msg):
        pass

    def save_gps(self, msg):
        pass

    def save_attitude(self, msg):
        pass

    def save_ins(self, msg):
        pass

    def save_encoder(self, msg):
        pass

    def close(self):
        self.csv_file.close()


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