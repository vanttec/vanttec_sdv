#!/usr/bin/env python3
"""
Nodo para controlar la velocidad del SDV con el teclado.

Controles:
  ↑  Subir al siguiente nivel de velocidad
  ↓  Bajar al nivel anterior
  SPACE  Frenar (velocidad = 0.0)
  Ctrl+C Salir

Publica en: /sdv/velocity/throttle  (std_msgs/Float32)
"""

import sys
import tty
import termios
import threading

import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64


THROTTLE_LEVELS = [0.0, 0.2, 0.25, 0.30, 0.35, 0.40, 0.7, 0.8, 1.0]

KEY_UP    = '\x1b[A'
KEY_DOWN  = '\x1b[B'
KEY_SPACE = ' '
KEY_CTRL_C = '\x03'


class ThrottleKeyboardNode(Node):
    def __init__(self):
        super().__init__('throttle_keyboard_node')

        self.pub = self.create_publisher(Float64, '/sdv/velocity/throttle', 10)
        self.timer = self.create_timer(0.1, self._publish_throttle)  # 10 Hz

        self.idx = 0  # empieza en 0.0

        self.get_logger().info('=== Throttle Keyboard Node ===')
        self.get_logger().info(f'Niveles: {THROTTLE_LEVELS}')
        self.get_logger().info('↑ Subir  |  ↓ Bajar  |  SPACE Frenar  |  Ctrl+C Salir')
        self._print_status()

    # ------------------------------------------------------------------
    # Publisher

    def _publish_throttle(self):
        msg = Float64()
        msg.data = float(THROTTLE_LEVELS[self.idx])
        self.pub.publish(msg)

    # ------------------------------------------------------------------
    # Key handlers

    def key_up(self):
        if self.idx < len(THROTTLE_LEVELS) - 1:
            self.idx += 1
        self._print_status()

    def key_down(self):
        if self.idx > 0:
            self.idx -= 1
        self._print_status()

    def key_space(self):
        self.idx = 0
        self.get_logger().info('STOP  ->  velocidad = 0.0')

    # ------------------------------------------------------------------
    # Helpers

    def _print_status(self):
        val = THROTTLE_LEVELS[self.idx]
        filled = int(val / THROTTLE_LEVELS[-1] * 20)
        bar = '█' * filled + '░' * (20 - filled)
        self.get_logger().info(
            f'Velocidad: {val:.2f}  [{bar}]  '
            f'({self.idx + 1}/{len(THROTTLE_LEVELS)})'
        )


# ----------------------------------------------------------------------
# Keyboard reading (hilo separado para no bloquear el spin)

def _read_key(old_settings):
    """Lee una tecla en modo raw y restaura la terminal."""
    tty.setraw(sys.stdin.fileno())
    ch = sys.stdin.read(1)
    if ch == '\x1b':
        ch += sys.stdin.read(1)
        ch += sys.stdin.read(1)
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, old_settings)
    return ch


def _keyboard_loop(node: ThrottleKeyboardNode):
    old_settings = termios.tcgetattr(sys.stdin)
    try:
        while rclpy.ok():
            key = _read_key(old_settings)
            if key == KEY_UP:
                node.key_up()
            elif key == KEY_DOWN:
                node.key_down()
            elif key == KEY_SPACE:
                node.key_space()
            elif key == KEY_CTRL_C:
                break
    except Exception:
        pass
    finally:
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, old_settings)


# ----------------------------------------------------------------------

def main(args=None):
    rclpy.init(args=args)
    node = ThrottleKeyboardNode()

    kb_thread = threading.Thread(target=_keyboard_loop, args=(node,), daemon=True)
    kb_thread.start()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
