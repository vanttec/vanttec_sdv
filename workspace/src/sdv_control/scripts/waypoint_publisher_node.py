#!/usr/bin/env python3
"""
Nodo que publica waypoints desde archivo YAML al Stanley Controller
Publica continuamente el waypoint objetivo basado en lookahead
"""

import rclpy
from rclpy.node import Node
from visualization_msgs.msg import Marker
from geometry_msgs.msg import Point, TransformStamped
from tf2_ros import TransformException
from tf2_ros.buffer import Buffer
from tf2_ros.transform_listener import TransformListener
import yaml
import math
from pathlib import Path
from std_msgs.msg import Float32, String
from sdv_msgs.srv import LoadRoute

# CONFIGURACIÓN - COPIA/PEGA TU DIRECTORIO AQUÍ
# ============================================================================
WAYPOINTS_YAML = "/home/vanttec/vanttec_sdv/workspace/src/sdv_control/config/rutas/RutaHUB1.yaml"
# ============================================================================


class WaypointPublisher(Node):
    def __init__(self):
        super().__init__('waypoint_publisher')
        
        #naturalmente en 4
        self.declare_parameter('waypoints_file', WAYPOINTS_YAML)
        self.declare_parameter('lookahead_distance', 3.2)
        self.declare_parameter('publish_rate', 10.0)
        
        waypoints_file = self.get_parameter('waypoints_file').value
        self.lookahead_distance = self.get_parameter('lookahead_distance').value
        self.timer = None

        # Servicio
        self.change_path_service = self.create_service(
                LoadRoute,
                '/waypoints/change_path',
                self.start_new_path_callback
        )
        
        # Usar la variable configurada al inicio si no se especifica parámetro
        if not waypoints_file:
            waypoints_file = WAYPOINTS_YAML

        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)
        
        self.publisher = self.create_publisher(Marker, '/target_waypoint_marker', 10)
        self.percentage_pub = self.create_publisher(Float32, '/waypoint_progress', 10)

        self.load_path(waypoints_file)
        
        
    def load_waypoints(self, filepath):
        """Carga waypoints desde YAML"""
        with open(filepath, 'r') as f:
            data = yaml.safe_load(f)
        
        waypoints = []
        for wp in data['waypoints']:
            waypoints.append([wp['x'], wp['y'], wp['z']])
        
        self.get_logger().info(f'Cargados {len(waypoints)} waypoints desde {filepath}')
        return waypoints
    
    def get_vehicle_position(self):
        """Obtiene posición del vehículo en frame map"""
        try:
            transform = self.tf_buffer.lookup_transform(
                'map', 'velodyne',
                rclpy.time.Time())
            
            x = transform.transform.translation.x
            y = transform.transform.translation.y
            z = transform.transform.translation.z -1.45 #Removi el -1.5 inecesario
            
            return (x, y, z)
        except TransformException as ex:
            self.get_logger().warn(f'Transform error: {ex}', throttle_duration_sec=2.0)
            return None
    
    def distance_2d(self, p1, p2):
        """Distancia euclidiana 2D"""
        return math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)
    
    def find_target_waypoint(self, vehicle_pos):
        """Encuentra waypoint objetivo sin depender de punto inicial"""

        # Buscar waypoint más cercano en TODO el path
        min_dist = float('inf')
        closest_idx = 0

        for i in range(len(self.waypoints)):
            dist = self.distance_2d(vehicle_pos, self.waypoints[i])
            if dist < min_dist:
                min_dist = dist
                closest_idx = i

        # Buscar waypoint a lookahead_distance desde el más cercano
        target_idx = closest_idx

        for i in range(closest_idx, len(self.waypoints)):
            dist = self.distance_2d(vehicle_pos, self.waypoints[i])
            if dist >= self.lookahead_distance:
                target_idx = i
                break
        print(self.current_idx, target_idx)

        if target_idx >= len(self.waypoints):
            target_idx = len(self.waypoints) - 1

        self.current_idx = closest_idx

        return target_idx, min_dist
    
    def timer_callback(self):
        """Publica waypoint objetivo continuamente"""
        vehicle_pos = self.get_vehicle_position()
        
        if vehicle_pos is None:
            return
        
        target_idx, min_dist = self.find_target_waypoint(vehicle_pos)
        target_wp = self.waypoints[target_idx]
        
        # Crear mensaje Marker
        marker = Marker()
        marker.header.frame_id = 'map'
        marker.header.stamp = self.get_clock().now().to_msg()
        marker.type = Marker.POINTS
        marker.action = Marker.ADD
        
        pt = Point()
        pt.x = target_wp[0]
        pt.y = target_wp[1]
        pt.z = target_wp[2]
        marker.points.append(pt)
        
        marker.scale.x = 0.2
        marker.scale.y = 0.2
        marker.color.r = 1.0
        marker.color.g = 0.0
        marker.color.b = 0.0
        marker.color.a = 1.0
        
        self.publisher.publish(marker)
        
        progress = 100.0 * self.current_idx / len(self.waypoints)
        self.get_logger().info(
            f'Progreso: {progress:.1f}% ({self.current_idx}/{len(self.waypoints)}) | '
            f'Distancia al path: {min_dist:.2f}m',
            throttle_duration_sec=1.0)

        msg = Float32()
        msg.data = progress
        self.percentage_pub.publish(msg)
        
        if self.current_idx >= len(self.waypoints) - 1:
            self.get_logger().info('Path completado!', throttle_duration_sec=2.0)

    def start_new_path_callback(self, request, response):
            try:
                self.load_path(request.path)
                response.success = True
                response.message = f'Nuevo path cargado: ({request.path})'
                print('path cargado')
            except Exception as e:
                response.success = False
                response.message = str(e)
                print(str(e))

            return response

    def load_path(self, path: str):

        self.get_logger().info(
            f'Loading route: {path}'
        )
        
        if self.timer is not None:
            self.destroy_timer(self.timer)
            self.timer = None
    
        waypoints_file = path
        publish_rate = self.get_parameter('publish_rate').value

        
        self.waypoints = self.load_waypoints(waypoints_file)
        self.current_idx = 0
        
        
        timer_period = 1.0 / publish_rate
        self.timer = self.create_timer(timer_period, self.timer_callback)
        
        self.get_logger().info(f'Waypoint publisher iniciado')
        self.get_logger().info(f'Archivo: {waypoints_file}')
        self.get_logger().info(f'Waypoints cargados: {len(self.waypoints)}')
        self.get_logger().info(f'Lookahead distance: {self.lookahead_distance}m')



def main(args=None):
    rclpy.init(args=args)
    node = WaypointPublisher()
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
