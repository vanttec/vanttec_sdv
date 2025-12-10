#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from typing import List
import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy, DurabilityPolicy

from geometry_msgs.msg import TwistWithCovarianceStamped
from nav_msgs.msg import Odometry


class TwistToOdom(Node):
    """
    Two modes:
      1) Forward mode (use_mock_data=False): Convert TwistWithCovarianceStamped -> Odometry (original behavior).
      2) Mock mode (use_mock_data=True): Periodically publish fake Odometry with configurable constant velocities
         (default: linear.x = 1.0 m/s) on the output topic, regardless of input.
    """

    def __init__(self):
        super().__init__('twist_to_odom')

        # ---- Parameters ----
        # IO
        self.declare_parameter('input_topic', '/vectornav/velocity_body')
        self.declare_parameter('output_topic', '/control/velocity_body')
        # Frames
        self.declare_parameter('odom_frame_id', 'map')
        self.declare_parameter('child_frame_id', 'base_link')
        self.declare_parameter('copy_header_frame', False)   # only applies in forward mode
        # Covariances
        self.declare_parameter('pose_covariance_diag', 1e6)
        self.declare_parameter('twist_covariance_diag', 1e2) # used in mock mode
        # Mode & publish rate
        self.declare_parameter('use_mock_data', False)
        self.declare_parameter('publish_rate_hz', 20.0)
        # Mock values
        self.declare_parameter('mock_linear_x', 1.0)   # m/s
        self.declare_parameter('mock_linear_y', 0.0)
        self.declare_parameter('mock_linear_z', 0.0)
        self.declare_parameter('mock_angular_x', 0.0)  # rad/s
        self.declare_parameter('mock_angular_y', 0.0)
        self.declare_parameter('mock_angular_z', 0.0)

        input_topic  = self.get_parameter('input_topic').get_parameter_value().string_value
        output_topic = self.get_parameter('output_topic').get_parameter_value().string_value
        self.use_mock = bool(self.get_parameter('use_mock_data').value)
        rate_hz = float(self.get_parameter('publish_rate_hz').value)

        # QoS
        qos = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            history=HistoryPolicy.KEEP_LAST,
            depth=10
        )
        # Latch-ish behavior for mock odom (so late subscribers see last msg)
        # QoS para Odom: RELIABLE, KEEP_LAST(10), VOLATILE
        odom_qos = QoSProfile(
            reliability=ReliabilityPolicy.RELIABLE,
            history=HistoryPolicy.KEEP_LAST,
            depth=10
        )

        self._odom_pub = self.create_publisher(
            Odometry,
            output_topic,
            latched_qos if self.use_mock else odom_qos
        )


        # Subscription is only used in forward mode
        self._twist_sub = None
        if not self.use_mock:
            self._twist_sub = self.create_subscription(
                TwistWithCovarianceStamped, input_topic, self._cb_twist, qos
            )

        # Mock timer (only when mock mode)
        self._mock_timer = None
        if self.use_mock:
            period = 1.0 / max(0.1, rate_hz)
            self._mock_timer = self.create_timer(period, self._publish_mock)

        self.get_logger().info(
            "TwistToOdom running\n"
            f"  mode = {'MOCK' if self.use_mock else 'FORWARD'}\n"
            f"  input_topic = {input_topic}\n"
            f"  output_topic = {output_topic}\n"
            f"  odom_frame_id = {self.get_parameter('odom_frame_id').value}\n"
            f"  child_frame_id = {self.get_parameter('child_frame_id').value}\n"
            f"  pose_cov_diag = {self.get_parameter('pose_covariance_diag').value}\n"
            f"  twist_cov_diag (mock) = {self.get_parameter('twist_covariance_diag').value}\n"
            f"  publish_rate_hz = {rate_hz}\n"
            f"  mock v = ({self.get_parameter('mock_linear_x').value}, "
            f"{self.get_parameter('mock_linear_y').value}, "
            f"{self.get_parameter('mock_linear_z').value}) m/s, "
            f"omega = ({self.get_parameter('mock_angular_x').value}, "
            f"{self.get_parameter('mock_angular_y').value}, "
            f"{self.get_parameter('mock_angular_z').value}) rad/s"
        )

    # ---------- Forward mode callback ----------
    def _cb_twist(self, msg: TwistWithCovarianceStamped):
        odom = Odometry()

        # Header
        odom.header = msg.header
        if not self.get_parameter('copy_header_frame').value:
            odom.header.frame_id = self.get_parameter('odom_frame_id').value

        # Child frame
        odom.child_frame_id = self.get_parameter('child_frame_id').value

        # Pose unknown
        pose_cov_diag = float(self.get_parameter('pose_covariance_diag').value)
        odom.pose.pose.position.x = 0.0
        odom.pose.pose.position.y = 0.0
        odom.pose.pose.position.z = 0.0
        odom.pose.pose.orientation.x = 0.0
        odom.pose.pose.orientation.y = 0.0
        odom.pose.pose.orientation.z = 0.0
        odom.pose.pose.orientation.w = 1.0
        odom.pose.covariance = self._diag36(pose_cov_diag)

        # Twist copied
        odom.twist.twist = msg.twist.twist
        odom.twist.covariance = list(msg.twist.covariance)

        self._odom_pub.publish(odom)

    # ---------- Mock mode publisher ----------
    def _publish_mock(self):
        odom = Odometry()
        now = self.get_clock().now().to_msg()

        # Header
        odom.header.stamp = now
        odom.header.frame_id = self.get_parameter('odom_frame_id').value
        odom.child_frame_id = self.get_parameter('child_frame_id').value

        # Pose: zero with large covariance (unknown pose)
        pose_cov_diag = float(self.get_parameter('pose_covariance_diag').value)
        odom.pose.pose.orientation.w = 1.0
        odom.pose.covariance = self._diag36(pose_cov_diag)

        # Twist: constant (imaginary) values
        odom.twist.twist.linear.x  = float(self.get_parameter('mock_linear_x').value)
        odom.twist.twist.linear.y  = float(self.get_parameter('mock_linear_y').value)
        odom.twist.twist.linear.z  = float(self.get_parameter('mock_linear_z').value)
        odom.twist.twist.angular.x = float(self.get_parameter('mock_angular_x').value)
        odom.twist.twist.angular.y = float(self.get_parameter('mock_angular_y').value)
        odom.twist.twist.angular.z = float(self.get_parameter('mock_angular_z').value)

        twist_cov_diag = float(self.get_parameter('twist_covariance_diag').value)
        odom.twist.covariance = self._diag36(twist_cov_diag)

        self._odom_pub.publish(odom)

    @staticmethod
    def _diag36(val: float) -> List[float]:
        cov = [0.0] * 36
        for i in range(6):
            cov[i * 6 + i] = val
        return cov


def main():
    rclpy.init()
    node = TwistToOdom()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()