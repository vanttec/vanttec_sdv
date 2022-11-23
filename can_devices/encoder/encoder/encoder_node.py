import rclpy
from rclpy.node import Node
import can
from std_msgs.msg import Int64


class Encoder(Node):

    def __init__(self):
        super().__init__('encoder_node')
        self.publisher_ = self.create_publisher(Int64, 'encoder_position', 10)
        timer_period = 0.5  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.sendMsg = can.Message(arbitration_id=1568,is_extended_id=False, data=[0x43, 0x04, 0x60, 0x0])
        filters = [
            {"can_id": 1440, "can_mask": 0xFFFF, "extended": False},
        ]
        self.bus = can.interface.Bus(bustype='socketcan', channel='can1', bitrate=500000, can_filters=filters)

    def timer_callback(self):
        msg = Int64()
        self.bus.send(self.sendMsg, timeout=1)
        #while True:
        receivedMsg = self.bus.recv()
            # a= receivedMsg.arbitration_id & 1440
            # if a == 1440:
            #     break
        if receivedMsg is not None:
            codedMsg = receivedMsg.data
            decodedMsg = codedMsg.hex()
            hexaPos = (decodedMsg[14:16]+decodedMsg[12:14]+decodedMsg[10:12]+decodedMsg[8:10])
            decimalPos = int(hexaPos, 16)
            msg.data = decimalPos
            self.publisher_.publish(msg)
        self.get_logger().info('Publishing: "%s"' % receivedMsg)
        # self.get_logger().warn('arbitration_id: "%s"' % receivedMsg.arbitration_id)
        # self.get_logger().warn('error: "%s"' % receivedMsg.is_error_frame)
        # self.get_logger().warn('data: "%s"' % receivedMsg.data)
        # self.get_logger().warn('extended_id: "%s"' % receivedMsg.is_extended_id)
        


def main(args=None):
    rclpy.init(args=args)

    encoder_node = Encoder()

    rclpy.spin(encoder_node)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    encoder_node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()