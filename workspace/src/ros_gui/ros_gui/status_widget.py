from PyQt5.QtWidgets import (
    QWidget,
    QLabel,
    QHBoxLayout
)


class StatusWidget(QWidget):

    def __init__(self, label="Localization"):

        super().__init__()

        layout = QHBoxLayout(self)

        self.name_label = QLabel(label)

        self.status_label = QLabel("OFF")

        self.status_label.setMinimumWidth(50)

        self.set_off()

        layout.addWidget(self.name_label)
        layout.addStretch()
        layout.addWidget(self.status_label)

    def set_on(self):

        self.status_label.setText("ON")

        self.status_label.setStyleSheet("""
            QLabel {
                background-color: green;
                color: white;
                border-radius: 5px;
                padding: 4px;
            }
        """)

    def set_off(self):

        self.status_label.setText("OFF")

        self.status_label.setStyleSheet("""
            QLabel {
                background-color: red;
                color: white;
                border-radius: 5px;
                padding: 4px;
            }
        """)

    def set_status(self, value: bool):

        if value:
            self.set_on()
        else:
            self.set_off()
