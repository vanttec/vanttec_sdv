#!/usr/bin/env python3

import os

from ament_index_python.packages import get_package_share_directory

import rclpy
from rclpy.node import Node

from std_msgs.msg import Float32
from sdv_msgs.msg import EtaPose
from nav_msgs.msg import Path

import yaml
from yaml.loader import SafeLoader


class WaypointNode(Node):

    def __init__(self):
        super().__init__('waypoint_handler_node')
        self.vel_pub_ = self.create_publisher(Float32, '/car_control/setpoint/velocity', 10)
        self.path_pub_ = self.create_publisher(Path, '/car_control/reference_path', 10)
        
        timer_period = 0.01  # seconds
        self.eta_sub_ = self.create_subscription(
            EtaPose,
            '/car_simulation/dynamic_model/eta_pose',
            self.eta_pose_callback,
            10)
        self.eta_sub_  # prevent unused variable warning


        car_params = os.path.join(
            get_package_share_directory('sdv_control'),
            'config',
            'car_guidance_control.yaml'
        )


        with open('/home/max/sdv/src/sdv_ros/docker_ws/sdv_control/config/waypoints.yaml') as f:
            self.data = yaml.load(f, Loader=SafeLoader)
        self.index_list = range(len(self.data))
        self.index = 0
        self.path_update()

    def path_update(self):
        i = self.index
        dt = self.data
        l = len(dt)
        i_next = self.index_list[(i+1)%l]
        msg = Path()
        msg.p1.x = dt[i]['x']*1.0
        msg.p1.y = dt[i]['y']*1.0
        msg.p2.x = dt[i_next]['x']*1.0
        msg.p2.y = dt[i_next]['y']*1.0
        self.path_pub_.publish(msg)
        self.get_logger().info('New waypoint!')
        self.index = i_next
        
    def vel_update(self, new_vel):
        msg = Float32()
        msg.data = new_vel*1.0
        self.vel_pub_.publish(msg)

    def eta_pose_callback(self, msg):
        x = msg.x
        y = msg.y
        self.get_logger().info('"%s"' % self.index)

        dx = self.data[self.index]['x']*1.0
        dy = self.data[self.index]['y']*1.0
        d = ((x-dx)**2 + (y-dy)**2)**(1/2)
        if d < 7:
            self.path_update()
            self.vel_update(0.5)
            self.get_logger().info("Here comes a corner: Lowering speed.")
        else:
            self.vel_update(10)


def main(args=None):
    rclpy.init(args=args)

    waypoint_handler_node = WaypointNode()

    rclpy.spin(waypoint_handler_node)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    waypoint_handler_node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()


# Read yaml
# Subscribe to eta_pose
# When waypoint reached by 0.1 m, change waypoint
#   Change speed
#   Change path