#!/usr/bin/env python3

import os
import csv

from ament_index_python.packages import get_package_share_directory

import rclpy
from rclpy.node import Node

from std_msgs.msg import Float32, Header
from sdv_msgs.msg import EtaPose
from nav_msgs.msg import Path
from geometry_msgs.msg import PoseStamped

class WaypointNode(Node):

    def __init__(self):
        super().__init__('waypoint_handler')

        # self.vel_pub_ = self.create_publisher(Float32, '/car_control/setpoint/velocity', 10)
        self.path_pub_ = self.create_publisher(Path, '/car_control/reference_path', 10)
        
        self.eta_sub_ = self.create_subscription(
            EtaPose,
            '/car_simulation/dynamic_model/eta_pose',
            self.eta_pose_callback,
            10)
        
        self.eta_sub_  # prevent unused variable warning

        timer_period = 0.1
        self.timer = self.create_timer(timer_period, self.timer_callback)

        self.waypoints_file_ = os.path.join(
            get_package_share_directory('sdv_control'),
            'config',
            'waypoints.csv'
        )

        self.path_ = Path()
        self.path_.header.frame_id = "odom"
        self.path_.header.stamp = self.get_clock().now().to_msg()

        with open(self.waypoints_file_, 'r') as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=',')
            pose_stmpd = PoseStamped()

            for row in csv_reader:
                pose_stmpd.pose.position.x = row[0]
                pose_stmpd.pose.position.y = row[1]
        
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