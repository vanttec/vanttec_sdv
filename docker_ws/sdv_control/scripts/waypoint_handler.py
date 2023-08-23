#!/usr/bin/env python3
''' ----------------------------------------------------------------------------
 * @file: waypoint_handler.py
 * @date: August 22, 2023
 * @author: Max Pacheco
 * @author: Sebas Mtz
 *
 * @brief: Node to publish waypoints in NED reference frame
 * -----------------------------------------------------------------------------
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

        # self.vel_pub_ = self.create_publisher(Float32, '/car_control/setpoint/velocity', 10)
        self.path_pub_ = self.create_publisher(Path, '/car_control/reference_path', 10)
        
        timer_period = 0.1
        self.timer = self.create_timer(timer_period, self.timer_callback)

        self.waypoints_file_ = os.path.join(
            get_package_share_directory('sdv_control'),
            'config',
            # 'sim_waypoints.csv'
            'sim_waypoints_simple.csv'
            # 'parking_waypoints_ned.csv'
        )

        self.path_ = Path()
        self.path_.header.frame_id = parent_frame
        self.path_.header.stamp = self.get_clock().now().to_msg()

        with open(self.waypoints_file_, 'r') as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=',')

            for row in csv_reader:
                pose_stmpd = PoseStamped()
                pose_stmpd.header.frame_id = parent_frame
                pose_stmpd.pose.position.x = float(row[0])
                pose_stmpd.pose.position.y = float(row[1])
        
                self.path_.poses.append(pose_stmpd)

    def timer_callback(self):
        self.path_pub_.publish(self.path_)


def main(args=None):
    rclpy.init(args=args)

    waypoint_handler = WaypointNode()
    rclpy.spin(waypoint_handler)
    waypoint_handler.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()