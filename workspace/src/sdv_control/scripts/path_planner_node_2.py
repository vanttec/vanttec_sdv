#!/usr/bin/env python3

''' ----------------------------------------------------------------------------
 * @file: path_planner_node.py
 * @date: May 31, 2024
 * @author: Max Pacheco
 * @author: Juan Félix
 * @brief: Node that receives waypoints, interpolates them, calculates the curvature and publishes the results
 * -----------------------------------------------------------------------------
'''

import rclpy
from rclpy.node import Node

import numpy as np
from scipy.interpolate import CubicSpline

from nav_msgs.msg import Path
from std_msgs.msg import Float32MultiArray
from geometry_msgs.msg import PoseStamped
from sdv_msgs.msg import WaypointVector

class PathPlannerNode(Node):

    def __init__(self):

        super().__init__('path_planner_node')

        QUEUE_SIZE = 10
        TIME_PERIOD = 1

        # Definitions for path publishing

        self.parent_frame_ = 'odom'
        self.path_ = Path()
        self.path_.header.frame_id = self.parent_frame_
        self.path_.header.stamp = self.get_clock().now().to_msg()
        self.path_.poses.clear()

        self.path_pub_ = self.create_publisher(Path, '/sdv/guidance/reference_path', QUEUE_SIZE)

        # Definitions for curvature publishing

        self.curvature_array_ = Float32MultiArray()
        self.curvature_pub_ = self.create_publisher(Float32MultiArray, "/sdv/guidance/path_curvature", QUEUE_SIZE)

        # Timer for publishing

        self.timer_ = self.create_timer(TIME_PERIOD, self.timer_callback)

        # Waypoints subscriber

        self.waypoints_sub_ = self.create_subscription(WaypointVector, '/sdv/guidance/key_waypoints', self.waypoint_callback, QUEUE_SIZE)

    def timer_callback(self):

        self.path_.header.stamp = self.get_clock().now().to_msg()
        self.path_pub_.publish(self.path_)
        self.curvature_pub_.publish(self.curvature_array_)

    def waypoint_callback(self, msg):
        
        # Once waypoints are received, they are interpolated
        # The result is appended to the path, which is periodically published
        # Curvature is also calculated

        self.interpolate_waypoints(msg)

    def interpolate_waypoints(self, data):

        # Arrays of x and y waypoints coordinates

        x = np.asarray(data.x_list)
        y = np.asarray(data.y_list)

        # Ensure that there are enough waypoints for interpolation

        if x.size < 2 or y.size < 2:
            self.get_logger().warn("Not enough waypoints for interpolation.")

        # Define an arbitrary parameter to parametrize the curve

        path_t = np.linspace(0, 1, x.size)

        # Create Cubic Spline objects

        cs_x = CubicSpline(path_t, x)
        cs_y = CubicSpline(path_t, y)

        # Define values for the arbitrary parameter over which
        # x and y will be interpolated

        NUM_INTERPOLATION_POINTS = 5000

        t = np.linspace(np.min(path_t), np.max(path_t), NUM_INTERPOLATION_POINTS)

        # Interpolate along t
        # r[:, 0] -> Interpolated X coordinates
        # r[:, 1] -> Interpolated Y coordinates

        r = np.column_stack((cs_x(t), cs_y(t)))

        self.path_.poses.clear()    # Clear previous poses

        # Modify path

        for i in range(NUM_INTERPOLATION_POINTS):

            pose_stmpd = PoseStamped()
            
            pose_stmpd.header.frame_id = self.parent_frame_
            pose_stmpd.pose.position.x = r[i, 0]
            pose_stmpd.pose.position.y = r[i, 1]
            self.path_.poses.append(pose_stmpd)

        # Calculate curvature
        
        curvature = self.calculate_curvature(cs_x, cs_y, t)
        self.curvature_array_.data = curvature.tolist()

    def calculate_curvature(self, spline_x, spline_y, t):

        # Calculate curvature using first and second derivative of the spline

        dx_dt = spline_x(t, 1)
        d2x_dt2 = spline_x(t, 2)
        dy_dt = spline_y(t, 1)
        d2y_dt2 = spline_y(t, 2)

        numerator = dx_dt * d2y_dt2 - dy_dt * d2x_dt2
        denominator = (dx_dt ** 2 + dy_dt ** 2) ** (3 / 2)

        curvature = np.divide(numerator, denominator)

        return curvature

def main(args=None):

    rclpy.init(args=args)

    path_planner_node = PathPlannerNode()
    rclpy.spin(path_planner_node)

    path_planner_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()