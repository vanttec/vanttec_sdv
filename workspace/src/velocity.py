#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math
from collections import deque

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy, DurabilityPolicy

from geometry_msgs.msg import PoseWithCovarianceStamped, TwistWithCovarianceStamped
from std_msgs.msg import Float32
from nav_msgs.msg import Odometry

def yaw_from_quaternion(qx, qy, qz, qw) -> float:
    siny_cosp = 2.0 * (qw * qz + qx * qy)
    cosy_cosp = 1.0 - 2.0 * (qy * qy + qz * qz)
    return math.atan2(siny_cosp, cosy_cosp)

def angle_wrap_pi(angle: float) -> float:
    return (angle + math.pi) % (2.0 * math.pi) - math.pi

class PoseToVelocityCov(Node):
    def __init__(self):
        super().__init__('pose_to_velocity_cov')

        # ---- Parameters ----
        self.declare_parameter('input_topic', '/pcl_pose')
        self.declare_parameter('output_topic', '/control/velocity_body')
        self.declare_parameter('frame_id', 'map')
        self.declare_parameter('smooth_window', 1)
        self.declare_parameter('min_dt', 1e-4)
        self.declare_parameter('max_speed', 100.0)
        self.declare_parameter('propagate_covariance', True)
        # nuevos (opcionales)
        self.declare_parameter('speed_topic', '/pcl_speed')          # Float32 (|v|)
        self.declare_parameter('publish_speed_xy', False)            # también |v_xy|
        self.declare_parameter('speed_xy_topic', '/pcl_speed_xy')    # Float32 (|v_xy|)

        input_topic = self.get_parameter('input_topic').get_parameter_value().string_value
        output_topic = self.get_parameter('output_topic').get_parameter_value().string_value
        self.frame_id = self.get_parameter('frame_id').get_parameter_value().string_value
        self.smooth_window = max(1, int(self.get_parameter('smooth_window').get_parameter_value().integer_value))
        self.min_dt = self.get_parameter('min_dt').get_parameter_value().double_value
        self.max_speed = self.get_parameter('max_speed').get_parameter_value().double_value
        self.propagate_cov = self.get_parameter('propagate_covariance').get_parameter_value().bool_value

        self.speed_topic = self.get_parameter('speed_topic').get_parameter_value().string_value
        self.publish_speed_xy = self.get_parameter('publish_speed_xy').get_parameter_value().bool_value
        self.speed_xy_topic = self.get_parameter('speed_xy_topic').get_parameter_value().string_value

        # QoS
        qos = QoSProfile(reliability=ReliabilityPolicy.RELIABLE,
                         history=HistoryPolicy.KEEP_LAST, depth=10)

        # "latched" para Float32 (que el último valor quede disponible)
        latched_qos = QoSProfile(reliability=ReliabilityPolicy.RELIABLE,
                                 history=HistoryPolicy.KEEP_LAST, depth=1,
                                 durability=DurabilityPolicy.TRANSIENT_LOCAL)

        # ---- I/O ----
        self.sub = self.create_subscription(PoseWithCovarianceStamped, input_topic, self.pose_cb, qos)
        self.pub_twist = self.create_publisher(Odometry, output_topic, qos)
        self.pub_speed = self.create_publisher(Float32, self.speed_topic, latched_qos)
        self.pub_speed_xy = None
        if self.publish_speed_xy:
            self.pub_speed_xy = self.create_publisher(Float32, self.speed_xy_topic, latched_qos)

        # ---- State ----
        self.last_t = None
        self.last_x = None
        self.last_y = None
        self.last_z = None
        self.last_yaw = None
        self.last_pos_cov = None

        self.buf_vx = deque(maxlen=self.smooth_window)
        self.buf_vy = deque(maxlen=self.smooth_window)
        self.buf_vz = deque(maxlen=self.smooth_window)
        self.buf_wz = deque(maxlen=self.smooth_window)

        self.get_logger().info(f"Pose→Velocity listo. Sub: {input_topic}, Pub: {output_topic} + {self.speed_topic}")

    def pose_cb(self, msg: PoseWithCovarianceStamped):
        x = msg.pose.pose.position.x
        y = msg.pose.pose.position.y
        z = msg.pose.pose.position.z
        qx = msg.pose.pose.orientation.x
        qy = msg.pose.pose.orientation.y
        qz = msg.pose.pose.orientation.z
        qw = msg.pose.pose.orientation.w
        t = msg.header.stamp.sec + msg.header.stamp.nanosec * 1e-9

        if self.last_t is None:
            self.last_t = t
            self.last_x, self.last_y, self.last_z = x, y, z
            self.last_yaw = yaw_from_quaternion(qx, qy, qz, qw)
            self.last_pos_cov = list(msg.pose.covariance)
            return

        dt = t - self.last_t
        if dt < self.min_dt:
            return

        dx = x - self.last_x
        dy = y - self.last_y
        dz = z - self.last_z
        vx = dx / dt
        vy = dy / dt
        vz = dz / dt

        yaw_now = yaw_from_quaternion(qx, qy, qz, qw)
        dyaw = angle_wrap_pi(yaw_now - self.last_yaw)
        wz = dyaw / dt

        speed = math.sqrt(vx*vx + vy*vy + vz*vz)
        if not math.isfinite(speed) or speed > self.max_speed:
            self.last_t = t
            self.last_x, self.last_y, self.last_z = x, y, z
            self.last_yaw = yaw_now
            self.last_pos_cov = list(msg.pose.covariance)
            return

        # Suavizado
        self.buf_vx.append(vx); self.buf_vy.append(vy); self.buf_vz.append(vz); self.buf_wz.append(wz)
        vx_f = sum(self.buf_vx)/len(self.buf_vx)
        vy_f = sum(self.buf_vy)/len(self.buf_vy)
        vz_f = sum(self.buf_vz)/len(self.buf_vz)
        wz_f = sum(self.buf_wz)/len(self.buf_wz)

        # Magnitudes
        speed_f = math.sqrt(vx_f*vx_f + vy_f*vy_f + vz_f*vz_f)
        speed_xy_f = math.sqrt(vx_f*vx_f + vy_f*vy_f)

        # ---- Publica Twist con cov ----
        out = TwistWithCovarianceStamped()
        out.header.stamp = msg.header.stamp
        out.header.frame_id = self.frame_id
        out.twist.twist.linear.x = speed_f
        out.twist.twist.linear.y = vy_f
        out.twist.twist.linear.z = vz_f
        out.twist.twist.angular.z = wz_f

        cov = [0.0]*36
        if self.propagate_cov and self.last_pos_cov is not None:
            var_x_now = msg.pose.covariance[0];  var_x_prev = self.last_pos_cov[0]
            var_y_now = msg.pose.covariance[7];  var_y_prev = self.last_pos_cov[7]
            var_z_now = msg.pose.covariance[14]; var_z_prev = self.last_pos_cov[14]
            var_yaw_now = msg.pose.covariance[35]; var_yaw_prev = self.last_pos_cov[35]
            var_vx = max(1e-9, (var_x_now + var_x_prev)/(dt*dt))
            var_vy = max(1e-9, (var_y_now + var_y_prev)/(dt*dt))
            var_vz = max(1e-9, (var_z_now + var_z_prev)/(dt*dt))
            var_wz = max(1e-9, (var_yaw_now + var_yaw_prev)/(dt*dt))
            cov[0]=var_vx; cov[7]=var_vy; cov[14]=var_vz; cov[35]=var_wz
        else:
            cov[0]=0.05; cov[7]=0.05; cov[14]=0.05; cov[35]=0.02

        out.twist.covariance = cov
        self.pub_twist.publish(out)

        # ---- Publica velocidad absoluta |v| ----
        sp_msg = Float32(); sp_msg.data = float(speed_f)
        self.pub_speed.publish(sp_msg)

        # (Opcional) publica |v_xy|
        if self.pub_speed_xy:
            spxy_msg = Float32(); spxy_msg.data = float(speed_xy_f)
            self.pub_speed_xy.publish(spxy_msg)

        # ---- Update state ----
        self.last_t = t
        self.last_x, self.last_y, self.last_z = x, y, z
        self.last_yaw = yaw_now
        self.last_pos_cov = list(msg.pose.covariance)

def main():
    rclpy.init()
    node = PoseToVelocityCov()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
