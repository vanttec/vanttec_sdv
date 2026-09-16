from PyQt5.QtWidgets import (
    QVBoxLayout,
    QLabel,
    QProgressBar,
    QFrame
)

class ProgressWidget(QFrame):

    def __init__(self, title="Camino Recorrido"):

        super().__init__()

        self.setFrameShape(QFrame.Box)

        layout = QVBoxLayout()

        self.label = QLabel(title)

        self.progress = QProgressBar()

        self.progress.setRange(0, 100)

        #self.percent_label = QLabel("0%")

        layout.addWidget(self.label)

        layout.addWidget(self.progress)

        #layout.addWidget(self.percent_label)

        self.setLayout(layout)

    def set_percentage(self, value):

        value = max(0, min(100, int(value)))
        self.progress.setValue(value)
