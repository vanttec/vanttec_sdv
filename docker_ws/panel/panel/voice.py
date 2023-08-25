#!/usr/bin/env python
import rclpy
import subprocess
from rclpy.node import Node
from ament_index_python.packages import get_package_share_directory
from std_msgs.msg import String

class Indicators(Node):

    def __init__(self, dev_name):
        super().__init__("indicators")
        self.get_logger().info("Indicators Node Started")

        # Name and address of the bluetooth device
        self.device_name = dev_name
        self.device_address = None

        # 
        self.audio_connected = False

        # List of requested audios
        self.audio_queue = []

        # Last requested audio
        self.last_audio = None
        
        # Dictionary of possible messages
        self.audios = {"modo_autonomo" : "/audios/autonomous_mode.wav", 
                       "modo_manual" : "/audios/manual_mode.wav",
                        "joke" : "/audios/joke.wav",
                        "distant_object" : "/audios/distant_object.wav",
                        "nearby_object" : "/audios/nearby_object.wav",
                        "stop_signal" : "/audios/stop_signal.wav",
                        "pedestrian_crossing" : "/audios/pedestrian_crossing.wav",
                        "pedestrian_signal" : "/audios/pedestrian_signal.wav",
                        "pedestrian_around" : "/audios/pedestrian_around.wav",
                        "on" : "/audios/on.wav",
                        "off" : "/audios/off.wav",   
                        "good_morning_sir": "/audios/good_morning_sir.wav",  
                       }

        # Get the package path
        package_name = "panel"
        self.package_path = get_package_share_directory(package_name).replace("/share/" + package_name, "").replace("install", "src")

        timer_period = 5
        self.timer = self.create_timer(timer_period, self.timer_callback)

        self.audio_name_subscription = self.create_subscription(String, '/sdv/panel/audio', self.audio_name_callback, 10)


    def audio_name_callback(self, msg):
        if msg.data != self.last_audio:
            self.last_audio = msg.data
            self.audio_queue.append(msg.data)


    def timer_callback(self):
        # Check device bluetooth state and connect
        self.get_logger().info(f"Trying to connect to: {self.device_name}")

        if not self.check_if_paired(self.device_name):
            if self.bluetooth_device_pair_connect(self.device_name):
                self.get_logger().info(f"Successfully paired and connected to {self.device_name}")
                self.audio_connected = True
            else:
                self.get_logger().info(f"Could not find {self.device_name} in nearby devices")
                self.audio_connected = False
        else:
            if not self.check_if_connected(self.device_address):
                if not self.bluetooth_device_connect(self.device_address):
                    self.get_logger().info(f"Successfully connected to {self.device_name}")
                    self.audio_connected = True
                else:
                    self.get_logger().info(f"Could not connect to {self.device_name}")
                    self.audio_connected = False
            else:
                self.get_logger().info(f"Already connected to {self.device_name}")
                self.audio_connected = True

        
        if self.audio_connected and len(self.audio_queue):
            self.play_audio(self.package_path + self.audios[self.audio_queue.pop(0)])
        

    def bluetooth_device_pair_connect(self, device_name):
        # Get a list of nearby Bluetooth devices
        devices = subprocess.check_output(['hcitool', 'scan']).decode('utf-8').splitlines()

        # Find the device address based on its name
        for device in devices:
            if device_name in device:
                self.device_address = device.split()[0]
                break

        if self.device_address:
            # Pair and connect to the Bluetooth device
            subprocess.run(['bluetoothctl', 'trust', self.device_address], stdout=subprocess.DEVNULL)
            subprocess.run(['bluetoothctl', 'connect', self.device_address], stdout=subprocess.DEVNULL)
            return True
        else:
            return False


    def check_if_paired(self, device_name):
        devices = subprocess.check_output(['bluetoothctl', 'paired-devices']).decode('utf-8').splitlines()

        for device in devices:
            if device_name in device:
                self.device_address = device.split()[1]
                return True
        return False
    
    def check_if_connected(self, device_address):
        info = subprocess.check_output(['bluetoothctl', 'info', device_address]).decode('utf-8').splitlines()

        for i in info:
            if i.split()[0] == 'Connected:' and i.split()[1] == 'yes':
                return True
        return False

    def bluetooth_device_connect(self, device_address):
        return not subprocess.run(['bluetoothctl', 'connect', device_address], stdout=subprocess.DEVNULL).returncode

    def play_audio(self, file_path):
        # Use aplay to play audio through the audio output
        subprocess.run(['aplay', file_path], stdout=subprocess.DEVNULL)

def main(args=None):
    rclpy.init(args=args)
    
    node = Indicators('JAM Rave Plus')
    #node = Indicators('WH-CH710')
    rclpy.spin(node)
    
    rclpy.shutdown()


if __name__ == '__main__':
    main()