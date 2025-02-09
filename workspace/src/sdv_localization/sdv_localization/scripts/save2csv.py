#!/usr/bin/env python3

import os
import csv

import rclpy
from rclpy.node import Node

from sdv_msgs.msg import Encoder, EtaPose
from std_msgs.msg import UInt8, Float32
from geometry_msgs.msg import PoseWithCovarianceStamped, Accel, Twist
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

        # /* Subscribers */ #
        ### From real-word experiments ### 
        # self.common_sub_ = self.create_subscription( CommonGroup, 'vectornav/raw/common',
        #                                               self.save_common, 1)
        # self.ins_sub_ = self.create_subscription( InsGroup, 'vectornav/raw/ins',
        #                                               self.save_ins, 1)
        # self.wheel_encoder_sub_ = self.create_subscription( Encoder, 'ifm_encoder',
        #                                               self.save_wheel_encoder, 1)
        # self.pot_step_sub_ = self.create_subscription( UInt8, 'potentiometer_step',
        #                                               self.pot_step, 1)
        # self.imu_sub_ = self.create_subscription( String, 'vectornav/raw/imu',
        #                                               self.save_imu, 1)
        # self.gps2_sub_ = self.create_subscription( String, 'vectornav/raw/gps2',
        #                                               self.save_gps, 1)
        # self.attitude_sub_ = self.create_subscription( String, 'vectornav/raw/attitude',
        #                                               self.save_attitude, 1)
        # self.pose_sub_ = self.create_subscription( PoseWithCovarianceStamped, 'sdv_localization/vectornav/pose',
        #                                               self.save_pose, 1)

        ### From dynamic model node ###
        self.accel_sub_ = self.create_subscription( Accel, "/sdc_simulation/dynamic_model/accel",
                                                    self.save_accel, 1)
        self.vel_sub_ = self.create_subscription( Twist, "/sdc_simulation/dynamic_model/vel",
                                                    self.save_vel, 1)
        self.eta_pose_sub_ = self.create_subscription( EtaPose, "/sdc_simulation/dynamic_model/eta_pose",
                                                    self.save_eta_pose, 1)
        self.steering_sub_ = self.create_subscription( Float32, "/sdc_control/control_signal/delta",
                                                    self.save_steering, 1)
        self.throttle_sub_ = self.create_subscription( UInt8, "/sdc_control/control_signal/D",
                                                    self.save_throttle, 1)

        timer_period = 0.1  # seconds
        # self.timer = self.create_timer(timer_period, self.pot_callback)
        self.pot_val = 0

        self.is_msg_arrived_ = False
        
        # To save data from dynamic model
        self.accel_msg = False
        self.vel_msg = False
        self.pose_msg = False
        self.throttle_msg = False
        self.steering_msg = False

        self.ax = 0
        self.ay = 0
        self.vx = 0
        self.vy = 0
        self.x = 0
        self.y = 0
        self.psi = 0
        self.r = 0
        self.delta = 0
        self.D = 0

        ### csv files creation ###

        rosbag_path = '/docker-ros/ws/src/tests/'
        # test = 'pruebas1ago/resistance/step90/data'
        test = ''

        # self.accel_file_path_ = rosbag_path + test + '/accel_data.csv'
        # self.accel_file_ = open(self.accel_file_path_, 'w')
        # self.accel_file_writer_ = csv.writer(self.accel_file_)
        # self.accel_file_writer_.writerow(['Time', 'AccelBody(x)','AccelBody(y)','AccelBody(z)', 'Theta', 'Psi', 'Psi_dot'])

        # self.vel_file_path_ = rosbag_path + test + '/vel_data.csv'
        # self.vel_file_ = open(self.vel_file_path_, 'w')
        # self.vel_file_writer_ = csv.writer(self.vel_file_)
        # self.vel_file_writer_.writerow(['Time', 'VelBody(x)','VelBody(y)','VelBody(z)'])

        # self.encoder_file_path_ = rosbag_path + test + '/encoder_data.csv'
        # self.encoder_file_ = open(self.encoder_file_path_, 'w')
        # self.encoder_file_writer_ = csv.writer(self.encoder_file_)
        # self.encoder_file_writer_.writerow(['Time', 'WheelAngle', 'SteeringAngle'])

        # self.pot_file_path_ = rosbag_path + test + '/pot_data.csv'
        # self.pot_file_ = open(self.pot_file_path_, 'w')
        # self.pot_file_writer_ = csv.writer(self.pot_file_)
        # self.pot_file_writer_.writerow(['Time', 'Pot_Step'])

        # self.pose_file_path_ = rosbag_path + test + '/pose_data.csv'
        # self.pose_file_ = open(self.pose_file_path_, 'w')
        # self.pose_file_writer_ = csv.writer(self.pose_file_)
        # self.pose_file_writer_.writerow(['Time', 'x', 'y'])

        self.state_file_path_ = rosbag_path + test + 'state_data.csv'
        self.pose_file_ = open(self.state_file_path_, 'w')
        self.state_file_writer_ = csv.writer(self.pose_file_)
        self.state_file_writer_.writerow(['Time', 'ax', 'ay', 'vx', 'vy', 'x', 'y', 'psi', 'r', 'delta', 'D'])


    ### From real-word experiments ###

    def save_pose(self, msg):
        if not self.is_msg_arrived_:
            self.is_msg_arrived_ = True
            self.start_time_ = self.get_clock().now()

        if self.is_msg_arrived_:
            elapsed_time = self.get_clock().now() - self.start_time_
            self.pose_file_writer_.writerow([elapsed_time.nanoseconds / 1e9, msg.pose.pose.position.x, msg.pose.pose.position.y])

    def pot_callback(self):
        if self.is_msg_arrived_:
            elapsed_time = self.get_clock().now() - self.start_time_
            self.pot_file_writer_.writerow([elapsed_time.nanoseconds / 1e9, self.pot_val])

    def pot_step(self, msg):
        if not self.is_msg_arrived_:
            self.is_msg_arrived_ = True
            self.start_time_ = self.get_clock().now()
            
        if self.pot_val != msg.data:
            self.pot_val = msg.data

    def save_common(self, msg):
        # if not self.is_msg_arrived_:
        #     self.is_msg_arrived_ = True
        #     self.start_time_ = self.get_clock().now()
        
        if self.is_msg_arrived_:
            elapsed_time = self.get_clock().now() - self.start_time_
            self.accel_file_writer_.writerow([elapsed_time.nanoseconds / 1e9, msg.accel.x, msg.accel.y, msg.accel.z, msg.yawpitchroll.y, msg.yawpitchroll.x, msg.angularrate.z])

    def save_ins(self, msg):
        # if not self.is_msg_arrived_:
        #     self.is_msg_arrived_ = True
        #     self.start_time_ = self.get_clock().now()
        
        if self.is_msg_arrived_:
            elapsed_time = self.get_clock().now() - self.start_time_
            self.vel_file_writer_.writerow([elapsed_time.nanoseconds / 1e9, msg.velbody.x, msg.velbody.y, msg.velbody.z])

    def save_wheel_encoder(self, msg):
        # if not self.is_msg_arrived_:
        #     self.is_msg_arrived_ = True
        #     self.start_time_ = self.get_clock().now()
        
        if self.is_msg_arrived_:
            elapsed_time = self.get_clock().now() - self.start_time_
            MAX_WHEEL_ANGLE = 715.78
            MIN_WHEEL_ANGLE = -577

            MAX_DELTA_R = 44
            MIN_DELTA_R = -44 #TO CHECK

            MAX_DELTA_L = 38 #TO CHECK
            MIN_DELTA_L = -38
            
            delta_r = msg.abs_angle * MAX_DELTA_R/MAX_WHEEL_ANGLE if msg.abs_angle >= 0 else msg.abs_angle * MIN_DELTA_R/MIN_WHEEL_ANGLE
            delta_l = msg.abs_angle * MAX_DELTA_L/MAX_WHEEL_ANGLE if msg.abs_angle >= 0 else msg.abs_angle * MIN_DELTA_L/MIN_WHEEL_ANGLE
            delta = (delta_l + delta_r) / 2
            self.encoder_file_writer_.writerow([elapsed_time.nanoseconds / 1e9, msg.abs_angle, delta])

    ### From dynamic model node ###
    def save_state(self):
        if (self.accel_msg and self.vel_msg and self.pose_msg and self.throttle_msg and self.steering_msg):

            elapsed_time = self.get_clock().now() - self.start_time_

            self.state_file_writer_.writerow([elapsed_time.nanoseconds / 1e9,
                                              self.ax, self.ay, self.vx, self.vy, self.x, self.y,
                                              self.psi, self.r, self.delta, self.D])

            self.accel_msg = False
            self.vel_msg = False
            self.pose_msg = False
            self.throttle_msg = False
            self.steering_msg = False

            self.ax = 0
            self.ay = 0
            self.vx = 0
            self.vy = 0
            self.x = 0
            self.y = 0
            self.psi = 0
            self.r = 0
            self.delta = 0
            self.D = 0

    def save_accel(self, msg):
        if not self.is_msg_arrived_:
            self.start_time_ = self.get_clock().now()
            self.is_msg_arrived_ = True
            
        self.accel_msg = True

        self.ax = msg.linear.x
        self.ay = msg.linear.y

        self.save_state()

    def save_vel(self, msg):
        if not self.is_msg_arrived_:
            self.start_time_ = self.get_clock().now()
            self.is_msg_arrived_ = True
            
        self.vel_msg = True

        self.vx = msg.linear.x
        self.vy = msg.linear.y
        self.r =  msg.angular.z

        self.save_state()

    def save_eta_pose(self, msg):
        if not self.is_msg_arrived_:
            self.start_time_ = self.get_clock().now()
            self.is_msg_arrived_ = True
            
        self.pose_msg = True

        self.x = msg.x
        self.y = msg.y
        self.psi = msg.psi

        self.save_state()

    def save_throttle(self, msg):
        if not self.is_msg_arrived_:
            self.start_time_ = self.get_clock().now()
            self.is_msg_arrived_ = True
            
        self.throttle_msg = True

        self.D = msg.data
        self.save_state()

    def save_steering(self, msg):
        if not self.is_msg_arrived_:
            self.start_time_ = self.get_clock().now()
            self.is_msg_arrived_ = True
            
        self.steering_msg = True
        
        self.delta = msg.data
        self.save_state()

    def close(self):
        # self.accel_file_.close()
        # self.vel_file_.close()
        # self.encoder_file_.close()
        # self.pot_file_writer.close()
        # self.pose_file_writer_.close()
        self.state_file_writer_.close()

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