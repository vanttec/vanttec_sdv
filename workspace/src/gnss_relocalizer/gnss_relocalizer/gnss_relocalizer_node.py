import math

import rclpy
from rclpy.node import Node

from std_msgs.msg import Bool
from sensor_msgs.msg import NavSatFix
from geometry_msgs.msg import PoseWithCovarianceStamped

from collections import deque

class GNSSRelocalizer(Node):

    def __init__(self):
        super().__init__('gnss_relocalizer')
        
        # =========================
        # Parameters
        # =========================

        # GNSS origin (map origin)
        self.declare_parameter('origin_lat', 25.6512)
        self.declare_parameter('origin_lon', -100.2891)

        # Optional map offsets
        self.declare_parameter('map_offset_x', 0.0)
        self.declare_parameter('map_offset_y', 0.0)

        # Recovery settings
        self.declare_parameter('cooldown_sec', 20.0)
        self.declare_parameter('fail_threshold', 5)

        # GPS filtering
        self.declare_parameter('gps_buffer_size', 20)

        # Covariance gating
        self.declare_parameter('max_gps_covariance', 25.0)

        self.origin_lat = self.get_parameter(
            'origin_lat').get_parameter_value().double_value

        self.origin_lon = self.get_parameter(
            'origin_lon').get_parameter_value().double_value

        self.map_offset_x = self.get_parameter(
            'map_offset_x').get_parameter_value().double_value

        self.map_offset_y = self.get_parameter(
            'map_offset_y').get_parameter_value().double_value

        self.cooldown_sec = self.get_parameter(
            'cooldown_sec').get_parameter_value().double_value

        self.fail_threshold = self.get_parameter(
            'fail_threshold').get_parameter_value().integer_value

        self.gps_buffer_size = self.get_parameter(
            'gps_buffer_size').get_parameter_value().integer_value

        self.max_gps_covariance = self.get_parameter(
            'max_gps_covariance').get_parameter_value().double_value



        # =========================
        # Subscribers
        # =========================
        self.gnss_sub = self.create_subscription(
            NavSatFix,
            '/vectornav/gnss',
            self.gnss_callback,
            10)

        self.localization_valid_sub = self.create_subscription(
            Bool,
            '/localization_valid',
            self.localization_valid_callback,
            10)

        self.pose_sub = self.create_subscription(
            PoseWithCovarianceStamped,
            '/pcl_pose',
            self.pose_callback,
            10)

        # =========================
        # Publisher
        # =========================
        self.initialpose_pub = self.create_publisher(
            PoseWithCovarianceStamped,
            '/initialpose',
            10)


        # =========================
        # State
        # =========================

        #GPS buffer
        self.gps_buffer = deque(maxlen=20)

        # Data
        self.latest_gnss = None
        self.latest_pose = None

        #Fail counter
        self.fail_counter = 0

        # Cooldown
        self.last_reinit_time = self.get_clock().now()
        self.cooldown_sec = 20.0

        # Fake conversion scale
        self.scale = 100000.0

        self.get_logger().info('GNSS Relocalizer initialized')

    def gnss_callback(self, msg):

        self.gps_buffer.append(
            (msg.latitude, msg.longitude)
        )


        self.latest_gnss = msg

    def pose_callback(self, msg):
        self.latest_pose = msg

    def localization_valid_callback(self, msg):

        if msg.data:
            self.fail_counter = 0
            return

        self.fail_counter =+ 1

        if (self.fail_counter > self.fail_threshold):
            self.get_logger().warn(
                f'Invalid streak: {self.fail_counter}'
            )
            return

        self.get_logger().warn('Localization fail detected')

        # Cooldown
        dt = (
            self.get_clock().now() -
            self.last_reinit_time
        ).nanoseconds / 1e9

        if dt < self.cooldown_sec:
            self.get_logger().warn('Cooldown active')
            return

        if self.latest_gnss is None:
            self.get_logger().warn('No GNSS data')
            return

        if self.latest_pose is None:
            self.get_logger().warn('No pose data')
            return

        #GPS covariance check
        gps_cov = self.latest_gnss.position_covariance[0]

        if gps_cov > self.max_gps_covariance:

            self.get_logger().warn(
                f'GPS covariance too high: {gps_cov:.2f}'
            )

            return

        self.publish_initialpose()

        self.last_reinit_time = self.get_clock().now()
        self.fail_counter = 0     

    def publish_initialpose(self):

        # Average GPS
        avg_lat = sum(x[0] for x in self.gps_buffer) / len(self.gps_buffer)

        avg_lon = sum(x[1] for x in self.gps_buffer) / len(self.gps_buffer)

        # Convert GNSS -> local ENU approximation
        x, y = self.latlon_to_xy(avg_lat, avg_lon)

        # Apply optional map offsets
        x += self.map_offset_x
        y += self.map_offset_y

        # Create initialpose message
        msg = PoseWithCovarianceStamped()

        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = 'map'

        # TEMPORARY fake conversion
        x = self.latest_gnss.longitude * self.scale
        y = self.latest_gnss.latitude * self.scale

        msg.pose.pose.position.x = x
        msg.pose.pose.position.y = y
        msg.pose.pose.position.z = 0.0

        # Keep current orientation
        msg.pose.pose.orientation = \
            self.latest_pose.pose.pose.orientation

        # Simple covariance
        msg.pose.covariance[0] = 10.0
        msg.pose.covariance[7] = 10.0
        msg.pose.covariance[35] = 1.0

        self.initialpose_pub.publish(msg)

        self.get_logger().warn(
            f'Published relocalization pose: '
            f'x={x:.2f}, y={y:.2f}'
        )

    # ==========================================================
    # Geographic conversion
    # ==========================================================

    def latlon_to_xy(self, lat, lon):

        R = 6378137.0  # Earth radius [m]

        dlat = math.radians(lat - self.origin_lat)

        dlon = math.radians(lon - self.origin_lon)

        x = (
            R *
            dlon *
            math.cos(math.radians(self.origin_lat))
        )

        y = R * dlat

        return x, y



def main(args=None):

    rclpy.init(args=args)

    node = GNSSRelocalizer()

    rclpy.spin(node)

    node.destroy_node()

    rclpy.shutdown()


if __name__ == '__main__':
    main()

