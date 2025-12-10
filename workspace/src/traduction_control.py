#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

from nav_msgs.msg import Path
from visualization_msgs.msg import Marker
from geometry_msgs.msg import Point
from rclpy.duration import Duration
import math

class PathToMarkersNode(Node):
    def __init__(self):
        super().__init__('path_to_markers_node')

        # Parameters
        self.declare_parameter('input_topic', '/sdv_trajectory')
        self.declare_parameter('line_topic', '/path_marker_line')
        self.declare_parameter('points_topic', '/target_waypoint_marker')
        self.declare_parameter('frame_id', 'map')
        self.declare_parameter('publish_rate_hz', 20.0)

        # Visualization
        self.declare_parameter('line_width', 0.05)
        self.declare_parameter('point_size', 0.12)
        self.declare_parameter('color_rgba', [0.0, 1.0, 0.0, 1.0])
        self.declare_parameter('points_color_rgba', [1.0, 0.4, 0.0, 1.0])
        self.declare_parameter('lifetime_sec', 0.0)
        self.declare_parameter('namespace', 'path_vis')

        # **Nueva resolución de interpolación**
        self.declare_parameter('interpolation_resolution_m', 0.1)

        input_topic = self.get_parameter('input_topic').value
        self.line_topic = self.get_parameter('line_topic').value
        self.points_topic = self.get_parameter('points_topic').value
        self.frame_id = self.get_parameter('frame_id').value

        self.line_pub = self.create_publisher(Marker, self.line_topic, 10)
        self.points_pub = self.create_publisher(Marker, self.points_topic, 10)

        self.create_subscription(Path, input_topic, self.path_callback, 10)

        self.latest_path = None
        self.timer = self.create_timer(1.0 / float(self.get_parameter('publish_rate_hz').value),
                                       self.publish_markers)

    def path_callback(self, msg: Path):
        self.latest_path = msg

    def interpolate_path(self, poses, resolution):
        points = []
        if len(poses) < 2:
            return points

        prev = poses[0].pose.position
        for pose in poses[1:]:
            curr = pose.pose.position
            dist = math.dist((prev.x, prev.y, prev.z), (curr.x, curr.y, curr.z))
            steps = max(1, int(dist / resolution))
            for i in range(steps + 1):
                t = i / steps
                x = prev.x + t * (curr.x - prev.x)
                y = prev.y + t * (curr.y - prev.y)
                z = prev.z + t * (curr.z - prev.z)
                points.append(Point(x=x, y=y, z=z))
            prev = curr
        return points

    def publish_markers(self):
        if self.latest_path is None:
            return

        resolution = float(self.get_parameter('interpolation_resolution_m').value)
        points = self.interpolate_path(self.latest_path.poses, resolution)

        # Line marker
        line_marker = Marker()
        line_marker.header.frame_id = self.frame_id
        line_marker.header.stamp = self.get_clock().now().to_msg()
        line_marker.ns = self.get_parameter('namespace').value
        line_marker.id = 0
        line_marker.type = Marker.LINE_STRIP
        line_marker.action = Marker.ADD
        line_marker.scale.x = self.get_parameter('line_width').value
        line_marker.color.r, line_marker.color.g, line_marker.color.b, line_marker.color.a = self.get_parameter('color_rgba').value
        line_marker.points = points

        # Points marker
        points_marker = Marker()
        points_marker.header = line_marker.header
        points_marker.ns = line_marker.ns
        points_marker.id = 1
        points_marker.type = Marker.SPHERE_LIST
        points_marker.action = Marker.ADD
        points_marker.scale.x = points_marker.scale.y = points_marker.scale.z = self.get_parameter('point_size').value
        points_marker.color.r, points_marker.color.g, points_marker.color.b, points_marker.color.a = self.get_parameter('points_color_rgba').value
        points_marker.points = points

        self.line_pub.publish(line_marker)
        self.points_pub.publish(points_marker)


def main():
    rclpy.init()
    node = PathToMarkersNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
