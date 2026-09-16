from PyQt5.QtWidgets import (
    QWidget,
    QVBoxLayout,
    QHBoxLayout,
    QProgressBar,
    QPushButton,
    QLabel,
    QFrame
)

from PyQt5.QtCore import Qt, pyqtSignal


class VelocityControlWidget(QFrame):
    
    # Signal
    speed_change_signal = pyqtSignal(int)

    def __init__(self):
        super().__init__()


        self.THROTTLE_LEVELS = [0.0, 0.2, 0.25, 0.30, 0.35, 0.40, 0.7, 0.8, 1.0]
        self.idx = 0

        self.setFrameShape(QFrame.Box)
        main_layout = QVBoxLayout()


        # title
        title = QLabel("Velocidad")
        title.setAlignment(Qt.AlignCenter)

        # progress bar
        self.progress = QProgressBar()
        self.progress.setRange(0, 100)

        # buttons layout
        buttons_layout = QHBoxLayout()

        self.up_button = QPushButton("↑")
        self.down_button = QPushButton("↓")

        self.up_button.setFixedSize(80, 80)
        self.down_button.setFixedSize(80, 80)

        buttons_layout.addWidget(self.up_button)
        buttons_layout.addWidget(self.down_button)


        self.stop_button = QPushButton("Parar coche (Espacio)")
        
        main_layout.addWidget(title)
        main_layout.addWidget(self.progress)
        main_layout.addLayout(buttons_layout)
        main_layout.addWidget(self.stop_button)

        self.setLayout(main_layout)

        # keyboard shortcuts
        self.up_button.setShortcut(Qt.Key_Up)
        self.down_button.setShortcut(Qt.Key_Down)
        self.stop_button.setShortcut(Qt.Key_Space)

        # callbacks
        self.up_button.clicked.connect(
            self.speed_up
        )

        self.down_button.clicked.connect(
            self.speed_down
        )

        self.stop_button.clicked.connect(
            self.stop
        )

    def speed_up(self):
        print("speed up")
        if self.idx < len(self.THROTTLE_LEVELS) - 1:
            self.idx += 1

        self.speed_change_signal.emit(self.idx)
        self.progress.setValue(int((self.idx / 8) * 100))


    def speed_down(self):
        print("speed down")
        if self.idx > 0:
            self.idx -= 1
        self.speed_change_signal.emit(self.idx)
        self.progress.setValue(int((self.idx / 8) * 100))

    def stop(self):
        print("stop signal")
        self.idx = 0
        self.speed_change_signal.emit(0)
        self.progress.setValue(int((self.idx / 8) * 100))

