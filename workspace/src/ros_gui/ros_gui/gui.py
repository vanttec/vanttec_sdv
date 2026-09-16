from PyQt5.QtWidgets import (
    QWidget,
    QVBoxLayout,
    QHBoxLayout,
    QPushButton,
    QTextEdit,
    QComboBox
)

from PyQt5.QtCore import pyqtSignal

from ros_gui.status_widget import StatusWidget
from ros_gui.progress_widget import ProgressWidget
from ros_gui.velocity_widget import VelocityControlWidget
import sys
import os



class MainWindow(QWidget):

    def __init__(self, ros_node):
        super().__init__()

        self.ros_node = ros_node

        self.setWindowTitle("ROS GUI")

        layout = QVBoxLayout()
        auto_layout = QHBoxLayout()

        # successfully disabled autonomous mode (for the route change)
        self.disabled_success = False

        # buttons
        self.disable_button = QPushButton(
            "Apagar Modo Autonomo"
        )
        self.disable_button.clicked.connect(
            lambda: self.change_mode(0)
        )
        
        self.auto_button = QPushButton(
            "Encender Modo Autonomo"
        )
        self.auto_button.clicked.connect(
            lambda: self.change_mode(1)
        )

        self.load_route_button = QPushButton(
            "Load Route"
        )
        self.load_route_button.clicked.connect(
            self.load_selected_route
        )
        self.load_route_button.setEnabled(True)


        # waypoint dropdown
        self.route_dropdown = QComboBox()
        routes_dir = "/home/vanttec/vanttec_sdv/workspace/src/sdv_control/config/rutas"

        for file in os.listdir(routes_dir):
            if file.endswith(".yaml"):
                full_path = os.path.join(
                    routes_dir,
                    file
                )

                label = file.replace(".yaml", "")
                self.route_dropdown.addItem(
                    label,
                    full_path
                )

        # widgets
        self.localization_status = StatusWidget("Localization")
        self.localization_status.set_status(True)
        self.progress = ProgressWidget()
        self.velocity = VelocityControlWidget()


        self.logs = QTextEdit()
        self.logs.setReadOnly(True)

        # layout
        layout.addWidget(self.localization_status)
        layout.addWidget(self.progress)
        layout.addWidget(self.logs)
        
        auto_layout.addWidget(self.auto_button)
        auto_layout.addWidget(self.disable_button)

        layout.addLayout(auto_layout)
        layout.addWidget(self.route_dropdown)
        layout.addWidget(self.load_route_button)
        layout.addWidget(self.velocity)

        self.setLayout(layout)

        #Connect Ros Node Signal
        ros_node.signals.localization.connect(
            self.on_loc_status
        )

        ros_node.signals.progress.connect(
            self.on_progress_update
        )

        ros_node.signals.disabled.connect(
            self.on_disabled
        )

        # Speed signal
        self.velocity.speed_change_signal.connect(
            self.on_speed_change
        )

    def on_loc_status(self, status):
        self.logs.append(str(status))

        if status:
            self.localization_status.set_status(True)
        else:
            self.localization_status.set_status(False)

    def on_progress_update(self, msg):
        self.progress.set_percentage(msg)

        # # Check if progress is at threshold
        # if (msg > 30 and self.disabled_success):
        #     self.load_route_button.setEnabled(True)
        # else:
        #     self.load_route_button.setEnabled(False)
        
    def change_mode(self, mode: int):
        self.ros_node.set_steering_mode(mode)

        if mode == 0:
            self.logs.append(
                "Modo autonomo deshabilitado. Ahora puedes cargar una nueva ruta."
            )
        elif mode == 1:
            self.logs.append(
                "Modo autonomo habilitado."
            )

    def load_selected_route(self):

        route = self.route_dropdown.currentData()

        self.logs.append(
            f"Cargando ruta: {route}"
        )

        self.ros_node.load_route(route)

    def on_disabled(self, msg):
        self.disabled_success = msg

    def on_speed_change(self, msg):
        print(f"speed change: {msg}")
        self.ros_node.change_velocity(msg)
