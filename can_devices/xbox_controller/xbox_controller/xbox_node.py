from rclpy.node import Node
from std_msgs.msg import String
import rclpy
import xbox_controller.xbox_driver as xbox_driver
from sdv_msg.msg import XboxMsg
from sdv_msg.msg import PanelMsg
import can
def fmtFloat(n):
    return '{:6.3f}'.format(n)
class XboxNode(Node):
    def __init__(self):
        super().__init__('xbox_node')
        self.car_mode = self.create_subscription(
            String,
            'car_mode',
            self.car_mode_callback,
            10
        )
        self.car_mode = ""
        timer_period = 0.1 #Seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.joy = xbox_driver.Joystick()
        self.xbox_info = XboxMsg()
        self.panel_info = PanelMsg()
        self.pub_xbox_status = self.create_publisher(XboxMsg, 'xbox_controller/status', 10)
        self.pub_panel_xbox = self.create_publisher(PanelMsg, 'xbox_panel/control', 10) 
        self.pub_car_mode = self.create_publisher(String, 'car_mode', 10) 
        self.old_car_mode = 0
        self.inverse_car = 0
    def car_mode_callback(self,msg):
        self.car_mode = msg.data
    def panel_controller(self):
        self.panel_info.wiper.data = bool(self.xbox_info.a.data)
        self.panel_info.horn.data = bool(self.xbox_info.b.data)
        self.panel_info.right_upper_front_light.data = bool(self.xbox_info.x.data)
        self.panel_info.left_upper_front_light.data = bool(self.xbox_info.y.data)
        self.panel_info.back.data = bool(self.xbox_info.back.data)
        self.pub_panel_xbox.publish(self.panel_info)
    def car_mode_pub(self):
        start = self.joy.Start()
        if self.old_car_mode == 0 and bool(start):
            msg = String()
            
            self.old_car_mode = bool(start)
            if self.inverse_car:
                self.inverse_car=0
                msg.data = "Manual"
                self.pub_car_mode.publish(msg)  
            else:
                self.inverse_car=1
                msg.data = "Automatic"
                self.pub_car_mode.publish(msg)
        else:
            self.old_car_mode =bool(start)
    def timer_callback(self):
        if self.joy.connected():
            self.car_mode_pub()
        if self.car_mode =="Manual":
            if self.joy.connected():
                self.xbox_info.connected.data =self.joy.connected()
                self.xbox_info.back.data =self.joy.Back()
                self.xbox_info.leftx.data =self.joy.leftX()
                self.xbox_info.lefty.data =self.joy.leftY()
                self.xbox_info.right_trigger.data =self.joy.rightTrigger()
                self.xbox_info.a.data =self.joy.A()
                self.xbox_info.b.data =self.joy.B()
                self.xbox_info.x.data =self.joy.X() 
                self.xbox_info.y.data =self.joy.Y() 
                self.xbox_info.dpad_up.data =self.joy.dpadUp()
                self.xbox_info.dpad_down.data =self.joy.dpadDown()
                self.xbox_info.dpad_left.data =self.joy.dpadLeft()
                self.xbox_info.dpad_right.data =self.joy.dpadRight()
                #Publish Xbox information
                #self.pub_xbox_status.publish(self.xbox_info)
                self.panel_controller()
            else:
                self.get_logger().warn('Xbox controller not connected ')
        else:
            self.get_logger().warn('Manual Mode not activated')


def main(args=None):
    rclpy.init(args=args)
    xbox = XboxNode()
    xbox.get_logger().info('Xbox node started')
    rclpy.spin(xbox)
    xbox.destroy_node()
    rclpy.shutdown()
    xbox.joy.close()

if __name__ == '__main__':
    main()
