import sys
import threading

import rclpy

from PyQt5.QtWidgets import QApplication

from ros_gui.gui import MainWindow
from ros_gui.ros_node import RosInterface

from rclpy.executors import ExternalShutdownException


def spin_ros(node):

    try:
        rclpy.spin(node)

    except ExternalShutdownException:
        pass

def main():

    rclpy.init()

    ros_node = RosInterface()

    ros_thread = threading.Thread(
        target=spin_ros,
        args=(ros_node,),
        daemon=True
    )

    ros_thread.start()

    app = QApplication(sys.argv)

    window = MainWindow(ros_node)
    window.show()

    try:
        app.exec()

    finally:

        ros_node.destroy_node()

        rclpy.shutdown()

        ros_thread.join(timeout=1.0)


if __name__ == '__main__':
    main()
