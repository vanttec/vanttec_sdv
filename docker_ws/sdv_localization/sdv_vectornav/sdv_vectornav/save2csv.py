#!/usr/bin/env python3

import os
import csv

import rclpy
from rclpy.node import Node

from std_msgs.msg import String


class IMU2CSV(Node):

    def __init__(self):
        super().__init__('to_csv_node')

        self.common_sub = self.create_subscription( String, 'vectornav/raw/common',
                                                      self.save_common, 10)
        self.imu_sub = self.create_subscription( String, 'vectornav/raw/imu',
                                                      self.save_imu, 10)
        self.gps2_sub = self.create_subscription( String, 'vectornav/raw/gps2',
                                                      self.save_gps, 10)
        self.attitude_sub = self.create_subscription( String, 'vectornav/raw/attitude',
                                                      self.save_attitude, 10)
        self.ins_sub = self.create_subscription( String, 'vectornav/raw/ins',
                                                      self.save_ins, 10)
        self.wheel_encoder_sub = self.create_subscription( String, 'ifm_encoder',
                                                      self.save_encoder, 10)

        self.csv_file_path = 'imu_data.csv'
        self.csv_file = open(self.csv_file_path, 'w')
        self.csv_writer = csv.writer(self.csv_file)
        self.csv_writer.writerow(['Time', 'AccelBody', 'VelBody', 'WheelAngle', 'Psi (yaw)'])

    def save_common(self, msg):
        self.get_logger().info('I heard: "%s"' % msg.data)

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