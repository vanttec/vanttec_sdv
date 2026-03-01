#!/usr/bin/env python3

''' ----------------------------------------------------------------------------
 * @file: waypoints_publisher_node.py
 * @date: May 31, 2024
 * @author: Max Pacheco
 * @author: Juan Félix
 * @brief: Node to publish waypoints as a WaypointVector
 * -----------------------------------------------------------------------------
'''

import rclpy
from rclpy.node import Node

from ament_index_python.packages import get_package_share_directory

import os
import csv

from sdv_msgs.msg import WaypointVector

class WaypointsPublisherNode(Node):

    def __init__(self):

        super().__init__('waypoint_publisher_node')

        QUEUE_SIZE = 10
        TIME_PERIOD = 1

        # Definitios for waypoints publishing

        self.waypoints_msg_ = WaypointVector()
        self.waypoints_pub_ = self.create_publisher(WaypointVector, '/sdv/guidance/key_waypoints', QUEUE_SIZE)

        # Timer for publishing

        self.timer_ = self.create_timer(TIME_PERIOD, self.timer_callback)

        # Read csv file with waypoints and append them to a message 
        # that will be published

        waypoints_file_ = os.path.join(get_package_share_directory('sdv_control'), 'config', 'anniversary_waypoints_ned.csv')

        with open(waypoints_file_, 'r') as csv_file:

            csv_reader = csv.reader(csv_file, delimiter=',')

            for row in csv_reader:
                    
                self.waypoints_msg_.x_list.append(float(row[0]))
                self.waypoints_msg_.y_list.append(float(row[1]))
            
    def timer_callback(self):
        
        self.waypoints_pub_.publish(self.waypoints_msg_)

        # Publish waypoints just once
    
        self.timer_.cancel()

def main(args=None):

    rclpy.init(args=args)

    waypoints_publisher_node = WaypointsPublisherNode()
    rclpy.spin(waypoints_publisher_node)

    waypoints_publisher_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()