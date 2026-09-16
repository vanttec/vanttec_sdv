import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile
from rclpy.qos import ReliabilityPolicy

from PyQt5.QtCore import QObject, pyqtSignal

from std_msgs.msg import String, Bool, Float32, Float64
from sdv_msgs.srv import Uint8, LoadRoute
from std_srvs.srv import Empty
from sensor_msgs.msg import LaserScan


class RosSignals(QObject):

    localization = pyqtSignal(bool)
    progress = pyqtSignal(float)
    points_hz = pyqtSignal(float)
    packets_hz = pyqtSignal(float)
    disabled = pyqtSignal(bool)


class RosInterface(Node):

    def __init__(self):
        super().__init__('qt_gui_node')
        
        # Parameters
        self.signals = RosSignals()
        self.THROTTLE_LEVELS = [0.0, 0.2, 0.25, 0.30, 0.35, 0.40, 0.7, 0.8, 1.0]

        # Variables
        lidar_qos = QoSProfile(
            depth=1,
            reliability=ReliabilityPolicy.BEST_EFFORT
        )

        # Clients
        self.set_mode_client = self.create_client(
            Uint8,
            '/sdv/steering/set_mode'
        )
        self.reset_encoder_client = self.create_client(
            Empty,
            '/sdv/steering/reset_encoder'
        )
        self.change_path_client = self.create_client(
            LoadRoute,
            '/waypoints/change_path'
        )


        #while not self.set_mode_client.wait_for_service(timeout_sec=1.0):
        #    print("waiting for set_mode service...")

        # Subscribers
        self.loc_subscription = self.create_subscription(
            Bool,
            '/localization_valid',
            self.loc_callback,
            10
        )

        self.progress_subscription = self.create_subscription(
            Float32,
            '/waypoint_progress',
            self.progress_callback,
            10
        )

        self.packets_subscription = self.create_subscription(
            LaserScan,
            '/velodyne_packets',
            self.packets_callback,
            lidar_qos
        )

        self.points_subscription = self.create_subscription(
            LaserScan,
            '/velodyne_points',
            self.points_callback,
            lidar_qos
        )

        # Publishers
        self.pub = self.create_publisher(Float64, '/sdv/velocity/throttle', 10)

        # State
        self.last_packets_scan_time = None
        self.current_packets_hz = 0.0
        
        self.last_points_scan_time = None
        self.current_points_hz = 0.0

    def loc_callback(self, msg):
        self.signals.localization.emit(msg.data)

    def progress_callback(self, msg):
        self.signals.progress.emit(msg.data)

    def points_callback(self, msg):
        print('point', msg)

        now = time.time()

        if self.last_points_scan_time is not None:

            dt = now - self.last_points_scan_time

            if dt > 0:
                new_hz = 1.0 / dt
                
                # smoothing
                self.current_points_hz = (
                    0.9 * self.current_points_hz +
                    0.1 * new_hz
                )

                self.signals.points_hz.emit(
                    self.current_points_hz
                )

        self.last_points_scan_time = now

    def packets_callback(self, msg):

        now = time.time()

        if self.last_packets_scan_time is not None:

            dt = now - self.last_packets_scan_time

            if dt > 0:
                new_hz = 1.0 / dt
                
                # smoothing
                self.current_packets_hz = (
                    0.9 * self.current_packets_hz +
                    0.1 * new_hz
                )

                self.signals.packets_hz.emit(self.current_packets_hz)
                print(self.current_packets_hz)

        self.last_packets_scan_time = now

    def set_steering_mode(self, mode: int):

        if mode == 1:
            req = Uint8.Request()
            req.data = mode
            future = self.set_mode_client.call_async(req)
            future.add_done_callback(
                    lambda: self.set_mode_response(mode)
                )

            req2 = Empty.Request()
            future2 = self.reset_encoder_client.call_async(req2)
            future2.add_done_callback(self.reset_encoder_response)
        elif mode == 0:

            self.signals.disabled.emit(False)

            req = Uint8.Request()
            req.data = mode
            future = self.set_mode_client.call_async(req)
            future.add_done_callback(
                    lambda f: self.set_mode_response(f, mode)
                )

    def reset_encoder_response(self, future):
        try:
            response = future.result()
            self.get_logger().info(f"Reset Encoder Service response: {response}")

        except Exception as e:
            self.get_logger().error(str(e))
            print(str(e))

    def set_mode_response(self, future, mode):
        try:
            response = future.result()
            self.get_logger().info(f"Set Mode Service response: {response}")
            if mode == 1:
                self.signals.disabled.emit(False)
            elif mode == 0:
                self.signals.disabled.emit(True)


        except Exception as e:
            self.get_logger().error(str(e))
            print(str(e))

    def load_route(self, path):
        req = LoadRoute.Request()
        req.path = path
        future = self.change_path_client.call_async(req)
        future.add_done_callback(self.load_route_response)

    def load_route_response(self, future):
        try:
            response = future.result()
            self.get_logger().info(f"Route loaded: {response.success}")

        except Exception as e:
            self.get_logger().error(str(e))

    def change_velocity(self, index):
        msg = Float64()
        msg.data = float(self.THROTTLE_LEVELS[index])
        self.pub.publish(msg)
