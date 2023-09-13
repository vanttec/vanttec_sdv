#!/usr/bin/env python3

'''
 * @file: waypoint_handler.py
 * @date: August 22, 2023
 * @author: Max Pacheco
 * @author: Sebas Mtz
 *
 * @brief: Node to publish waypoints in NED and ENU reference frames
'''

import os
import csv

from ament_index_python.packages import get_package_share_directory

import rclpy
from rclpy.node import Node

from nav_msgs.msg import Path
from geometry_msgs.msg import PoseStamped

class WaypointNode(Node):

    def __init__(self):
        super().__init__('waypoint_handler')

        self.declare_parameter('parent_frame', rclpy.Parameter.Type.STRING)

        parent_frame = self.get_parameter('parent_frame').value

        self.path_pub_ned_ = self.create_publisher(Path, '/sdc_control/reference_path_ned', 10)
        self.path_pub_enu_ = self.create_publisher(Path, '/sdc_control/reference_path_enu', 10)

        timer_period = 0.1
        self.timer = self.create_timer(timer_period, self.timer_callback)

        self.waypoints_file_ = os.path.join(
            get_package_share_directory('sdv_control'),
            'config',
            'waypoints_carreta.csv'
        )

        self.path_ned_ = Path()
        self.path_ned_.header.frame_id = parent_frame
        self.path_ned_.header.stamp = self.get_clock().now().to_msg()

        self.path_enu_ = Path()
        self.path_enu_.header.frame_id = parent_frame
        self.path_enu_.header.stamp = self.get_clock().now().to_msg()

        with open(self.waypoints_file_, 'r') as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=',')

            for row in csv_reader:
                # For NED path
                pose_stmpd_ned = PoseStamped()
                pose_stmpd_ned.header.frame_id = parent_frame
                pose_stmpd_ned.pose.position.x = float(row[0])
                pose_stmpd_ned.pose.position.y = float(row[1])
                self.path_ned_.poses.append(pose_stmpd_ned)

                # For ENU path
                x_enu, y_enu = self.ned_to_enu(float(row[0]), float(row[1]))
                pose_stmpd_enu = PoseStamped()
                pose_stmpd_enu.header.frame_id = parent_frame
                pose_stmpd_enu.pose.position.x = x_enu
                pose_stmpd_enu.pose.position.y = y_enu
                self.path_enu_.poses.append(pose_stmpd_enu)

    def ned_to_enu(self, x_ned, y_ned):
        """
        Converts a point from NED to ENU.
        """
        x_enu = y_ned
        y_enu = x_ned
        return x_enu, y_enu

    def timer_callback(self):
        self.path_pub_ned_.publish(self.path_ned_)
        self.path_pub_enu_.publish(self.path_enu_)

def main(args=None):
    rclpy.init(args=args)

    waypoint_handler = WaypointNode()
    rclpy.spin(waypoint_handler)
    waypoint_handler.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
