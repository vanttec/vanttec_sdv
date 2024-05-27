#!/usr/bin/env python3

import os
import csv
import math 
import numpy as np
from scipy.interpolate import CubicSpline

from ament_index_python.packages import get_package_share_directory

import rclpy
from rclpy.node import Node

from nav_msgs.msg import Path
from geometry_msgs.msg import Point
from geometry_msgs.msg import PoseStamped
from std_msgs.msg import Float32, Float64MultiArray
from sdv_msgs.msg import WpVector

def curvature_at(cs, t):
    x_, y_ = cs(t, nu=1)
    x__, y__ = cs(t, nu=2)
    return (x_ * y__ - y_ * x__) / (x_**2 + y_**2)**1.5

class PathPlannerNode(Node):

    def __init__(self):
        super().__init__('path_planner_node')

        parent_frame = 'odom'

        self.wp_sub_ = self.create_subscription(
            WpVector, '/sdv/guidance/key_waypoints', self.wp_callback, 10
        )
        self.path_pub_ = self.create_publisher(Path, "/sdv/guidance/reference_path", 10)
        self.curvature_arr_pub_ = self.create_publisher(Float64MultiArray, "/sdv/guidance/path_curvature", 10)

        self.timer = self.create_timer(1, self.timer_callback)

        self.path_ = Path()
        self.path_.header.frame_id = parent_frame
        self.path_.header.stamp = self.get_clock().now().to_msg()

    def timer_callback(self):
        self.path_pub_.publish(self.path_)
        self.curvature_arr_pub_.publish(self.curvature_arr)

    def wp_callback(self, msg):
        self.interpol(msg.data)

    def interpol(self, raw_data):
        self.path_ = Path()
        self.path_.header.frame_id = self.parent_frame
        self.path_.header.stamp = self.get_clock().now().to_msg()

        self.curvature_arr = Float64MultiArray()

        x = np.array(raw_data.x_list)
        y = np.array(raw_data.y_list)
        cs = CubicSpline(x, y)

        t = np.linspace(x[0], x[-1], 100)
        for i in range(100):
            pose_stmpd = PoseStamped()
            pose_stmpd.pose.position.x = x[i]
            pose_stmpd.pose.position.y = y[i]
            self.path_.poses.append(pose_stmpd)

            self.curvature_arr.data.append(curvature_at(cs, t[i]))

def main(args=None):
    rclpy.init(args=args)

    path_planner_node = PathPlannerNode()
    rclpy.spin(path_planner_node)
    path_planner_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()