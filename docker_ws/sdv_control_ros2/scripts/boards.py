import rclpy
from rclpy.node import Node
from std_msgs.msg import Int16
import can
class SDVControlNode(Node):
    def __init__(self):
        super().__init__('sdv_control_node')
        # Initialize subscriber
        self.throttle_sub = self.create_subscription(
            Int16,
            'sdv/control/throttle',
            self.throttle_callback,
            10)


        # Initialize timer with a 10 Hz callback
        self.timer = self.create_timer(0.1, self.timer_callback)
        self.received_value = 0
        # *------------------* VANTTEC_IDS *------------------*
        self.admin_id = 0x401
        self.general_module_id_tx = 0x403
        self.general_module_id_rx = 0x404 
        self.throttle_module_id = 0x406
        self.steering_module_id = 0x408
        self.braking_module_id = 0x412

        self.car_messages= {
                "throttle": can.Message(arbitration_id=self.throttle_module_id,is_extended_id=False, data=[0x5,0x1]),
            }

    def throttle_callback(self, msg):
        self.received_value = msg.data

    def timer_callback(self):
        self.car_messages["throttle"].data[1] = self.received_value
        self.bus.send(self.car_messages["throttle"],timeout=1)
        


def main(args=None):
    rclpy.init(args=args)
    sdv_control_node = SDVControlNode()
    rclpy.spin(sdv_control_node)
    sdv_control_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
