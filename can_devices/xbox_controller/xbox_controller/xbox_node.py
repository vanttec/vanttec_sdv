from rclpy.node import Node
from std_msgs.msg import String
import rclpy
import xbox_controller.xbox_driver as xbox_driver
from sdv_msg.msg import XboxMsg
from sdv_msg.msg import PanelMsg,ThrottleMsg,VehicleControl
from geometry_msgs.msg import Vector3
from std_msgs.msg import Int16
import can

def fmtFloat(n):
    return '{:6.3f}'.format(n)

class XboxNode(Node):
    def __init__(self):
        super().__init__('xbox_node')

        self.admin_id = 256 #hex. 100
        self.drive_mode = "Manual"
        self.prev_start_btn_state = False

        self.MAX_ANGLE = 57
        self.STEP_ANGLE = 0.9
        self.MAX_STEPS = 63
        self.STEPS_REV = 400

        self.req_steps = 0
        self.current_step = 0
        self.current_angle = 0

        self.joy_stick = xbox_driver.Joystick(50)
        self.xbox_info = XboxMsg()
        self.panel_info = PanelMsg()
        self.thottle_info = ThrottleMsg()
        self.vehicle_control = VehicleControl()
        
        self.timer = self.create_timer(0.1, self.timer_callback)
        # self.drive_mode_subs = self.create_subscription(
        #     String,
        #     '/drive_mode',
        #     self.drive_mode_callback,
        #     10
        # )

        self.encoder_sub = self.create_subscription(
            Int16,
            '/encoder',
            self.encoder_callback,
            10
        )

        # self.xbox_status_pub = self.create_publisher(XboxMsg, 'xbox_controller/status', 10)
        self.panel_xbox_pub = self.create_publisher(PanelMsg, '/sdv/xbox_controller/xbox_panel', 10) 
        self.throttle_xbox_pub = self.create_publisher(ThrottleMsg,'/sdv/xbox_controller/xbox_throttle',10)
        self.drive_mode_pub = self.create_publisher(String, '/sdv/xbox_controller/drive_mode', 10) 
        self.motor_mode_pub = self.create_publisher(String, '/sdv/xbox_controller/motor_mode', 10) 
        self.vehicle_control_pub = self.create_publisher(VehicleControl, '/sdv/manual_ctrl_cmd', 10)
        self.steering_pub = self.create_publisher(Vector3, '/steering', 10)

        self.can_manual_mode = [can.Message(arbitration_id=self.admin_id,is_extended_id=False, data=[0x1])]
        self.can_auto_mode = [can.Message(arbitration_id=self.admin_id,is_extended_id=False, data=[0x0])]
        self.bus = can.interface.Bus(bustype='socketcan', channel='can0', bitrate=100000)
        
        self.throttle_module_id = 1073 #hex 431
        self.motor_mode_id = 6 #hex 6
        self.car_mode_id = 7 #hex 7
        
    # def drive_mode_callback(self,msg):
    #     self.drive_mode = msg.data

    def encoder_callback(self,msg):
        self.current_angle = msg.data

    def panel_controller(self):
        self.panel_info.wiper.data = bool(self.xbox_info.a.data)
        self.panel_info.horn.data = bool(self.xbox_info.b.data)
        self.panel_info.right_upper_front_light.data = bool(self.xbox_info.x.data)
        self.panel_info.left_upper_front_light.data = bool(self.xbox_info.y.data)
        #self.panel_info.back.data = bool(self.xbox_info.back.data)
        self.panel_xbox_pub.publish(self.panel_info)

    def vehicle_controller(self):
        self.thottle_info.pot.data = self.xbox_info.right_trigger.data
        self.thottle_info.increase_maxvel.data = self.xbox_info.dpad_up.data
        self.thottle_info.decrease_maxvel.data =  self.xbox_info.dpad_down.data
        
        self.vehicle_control.throttle = self.xbox_info.right_trigger.data
        self.vehicle_control.steer = self.xbox_info.leftx.data

        self.throttle_xbox_pub.publish(self.thottle_info)
        self.vehicle_control_pub.publish(self.vehicle_control)

        req_angle = self.xbox_info.leftx.data * self.MAX_ANGLE
        req_steps = int((req_angle - self.current_angle)/self.STEP_ANGLE)

        if(req_steps != 0):
            dire = req_steps / abs(req_steps)
        else:
            dire = 0

        req_steps = req_steps * dire

        msg = Vector3()
        msg.x = float(dire)
        msg.y = float(req_steps)

        self.steering_pub.publish(msg)

    def publish_drive_mode(self):
        #Toggle car mode and pedal with XBOX controller
        start_btn = bool(self.joy_stick.Start())
        if not self.prev_start_btn_state and start_btn:
            motor_mode_msg = String()
            if self.motor_mode == "MotorON":
                motor_mode_msg.data = "MotorOFF"
                self.motor_mode_pub.publish(motor_mode_msg)
                self.motor_mode = "MotorOFF"
                self.bus.send(can.Message(arbitration_id=self.throttle_module_id,is_extended_id=False, data=[self.motor_mode_id,0x0]), timeout=1)
            else:
                motor_mode_msg.data = "MotorON"
                self.motor_mode_pub.publish(motor_mode_msg)
                self.motor_mode = "MotorON"
                self.bus.send(can.Message(arbitration_id=self.throttle_module_id,is_extended_id=False, data=[self.motor_mode_id,0x1]), timeout=1)
        
        self.prev_start_btn_state = start_btn

        back_btn = bool(self.joy_stick.Back())
        if not self.prev_back_btn_state and back_btn:
            drive_mode_msg = String()
            if self.drive_mode == "Autonomous":
                #Activate driver pedal
                drive_mode_msg.data = "Manual"
                self.drive_mode_pub.publish(drive_mode_msg)
                self.drive_mode = "Manual"
                self.bus.send(can.Message(arbitration_id=self.throttle_module_id,is_extended_id=False, data=[self.car_mode_id,0x0]), timeout=1)
            else:
                #Activate digital potentiometer
                drive_mode_msg.data = "Autonomous"
                self.drive_mode_pub.publish(drive_mode_msg)
                self.drive_mode = "Autonomous"     
                self.bus.send(can.Message(arbitration_id=self.throttle_module_id,is_extended_id=False, data=[self.car_mode_id,0x1]), timeout=1)       
        self.prev_back_btn_state = back_btn

    def timer_callback(self):
        if self.joy_stick.connected():
            self.publish_drive_mode()
            if self.drive_mode == "Manual":
                self.xbox_info.connected.data = self.joy_stick.connected()
                #self.xbox_info.back.data = self.joy_stick.Back()
                self.xbox_info.leftx.data = self.joy_stick.leftX()
                self.xbox_info.lefty.data = self.joy_stick.leftY()
                self.xbox_info.right_trigger.data = self.joy_stick.rightTrigger()
                self.xbox_info.a.data = self.joy_stick.A()
                self.xbox_info.b.data = self.joy_stick.B()
                self.xbox_info.x.data = self.joy_stick.X() 
                self.xbox_info.y.data = self.joy_stick.Y() 
                self.xbox_info.dpad_up.data = self.joy_stick.dpadUp()
                self.xbox_info.dpad_down.data = self.joy_stick.dpadDown()
                self.xbox_info.dpad_left.data = self.joy_stick.dpadLeft()
                self.xbox_info.dpad_right.data = self.joy_stick.dpadRight()
                #Publish Xbox information
                #self.xbox_status_pub.publish(self.xbox_info)
                self.panel_controller()
                self.vehicle_controller()
            # else:
            # self.get_logger().warn("Drive mode: " + self.drive_mode)
            # self.get_logger().info('Data: "%f"' % self.xbox_info.leftx.data)

def main(args=None):
    rclpy.init(args=args)
    xbox = XboxNode()
    xbox.get_logger().info('Xbox node started')
    while(not xbox.joy_stick.connected()):
        xbox.get_logger().warn('Xbox controller not connected')
    xbox.get_logger().info('Xbox controller connected')
    rclpy.spin(xbox)
    xbox.destroy_node()
    rclpy.shutdown()
    xbox.joy.close()

if __name__ == '__main__':
    main()