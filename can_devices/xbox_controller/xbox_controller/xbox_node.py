import rclpy
from rclpy.node import Node
import can

import xbox_controller.xbox_driver as xbox_driver
from std_msgs.msg import String, Int16, Float32
from geometry_msgs.msg import Vector3
from sdv_msg.msg import XboxMsg, PanelMsg, ThrottleMsg, VehicleControl, Encoder

def fmtFloat(n):
    return '{:6.3f}'.format(n)

class XboxNode(Node):
    def __init__(self):
        super().__init__('xbox_node')

        self.admin_id = 0x401
        self.drive_mode = "Manual"
        self.prev_start_btn_state = False

        self.controller_connected = False
        self.controller_stop = True

        self.joy_stick = xbox_driver.Joystick(50)
        
        timer_period = 0.1 #1 second
        self.timer=self.create_timer(timer_period,self.xbox_timer)

        self.bus = can.interface.Bus(bustype='socketcan', channel='can0', bitrate=125000)

        # *------------------* STEERING *------------------*
        # self.MAX_ANGLE = 57
        # self.STEP_ANGLE = 0.9
        # self.MAX_STEPS = 63
        # self.STEPS_REV = 400
        # self.req_steps = 0
        # self.current_step = 0
        # self.stepper_to_wheel_ratio = 1.5

        self.steering_wheel_angle = 0
        # max steering = (wheel turns to max steer = 1.7) * (stepper to wheel ratio = 1.5) * 360 degrees
        self.max_steering = 918 # degrees
        
        self.steering_module_id = 0x408
        self.dir_id = 0x10

        # *------------------* THROTTLE *------------------*
        self.safe_velocity=200 # % of safe_pot  
        self.safe_pot = 170
        self.old_maxvel = self.safe_velocity
        self.temp_pot= 1
        self.new_maxvel = self.safe_velocity
        self.old_increase_maxvel = 0 
        self.increase_maxvel = 0 
        self.old_decrease_maxvel = 0 
        self.decrease_maxvel = 0
        self.new_pot = 0
        self.old_pot = 0 
        self.limit_pot = self.safe_velocity
        self.timer=self.create_timer(timer_period,self.throttle_timer)

        self.throttle_module_id = 0x406
        #Send WiperPot position
        self.pot_id = 0x5
        #Send Max velocity
        self.max_id = 0x8

        # *------------------* ROS MESSAGES *------------------*
        self.xbox_info = XboxMsg()
        self.panel_info = PanelMsg()
        self.thottle_info = ThrottleMsg()
        self.vehicle_control = VehicleControl()

        # *------------------* SUBSCRIBERS *------------------*
        self.encoder_sub = self.create_subscription(
            Encoder,
            '/ifm_encoder',
            self.encoder_callback,
            10
        )

        # *------------------* PUBLISHERS *------------------*
        #self.xbox_status_pub = self.create_publisher(XboxMsg, 'xbox_controller/status', 10)
        self.panel_xbox_pub = self.create_publisher(PanelMsg, '/sdv/xbox_controller/xbox_panel', 10) 
        self.drive_mode_pub = self.create_publisher(String, '/sdv/xbox_controller/drive_mode', 10) 
        self.motor_mode_pub = self.create_publisher(String, '/sdv/xbox_controller/motor_mode', 10) 
        self.vehicle_control_pub = self.create_publisher(VehicleControl, '/sdv/manual_ctrl_cmd', 10)
        self.steering_pub = self.create_publisher(Vector3, '/steering_brake', 10)
        # self.pub_throttle_status = self.create_publisher(ThrottleMsg, 'throttle/status', 10)

        self.drive_mode_dict = {
            "manual": can.Message(arbitration_id=self.admin_id,is_extended_id=False, data=[0x2,0x0]),
            "auto": can.Message(arbitration_id=self.admin_id,is_extended_id=False, data=[0x2,0x1])
        }
        self.bus = can.interface.Bus(bustype='socketcan', channel='can0', bitrate=125000)
        
        self.throttle_module_id = 1030 #hex 406
        self.motor_mode_id = 6 #hex 6
        self.car_mode_id = 7 #hex 7
        
    # def drive_mode_callback(self,msg):
    #     self.drive_mode = msg.data

    def encoder_callback(self,msg):
        self.steering_wheel_angle = msg.abs_angle

    def panel_controller(self):
        self.panel_info.wiper.data = bool(self.xbox_info.a.data)
        self.panel_info.horn.data = bool(self.xbox_info.b.data)
        self.panel_info.right_upper_front_light.data = bool(self.xbox_info.x.data)
        self.panel_info.left_upper_front_light.data = bool(self.xbox_info.y.data)
        #self.panel_info.back.data = bool(self.xbox_info.back.data)
        self.panel_info.xboxcontrol.data = [bool(self.xbox_info.a.data),bool(self.xbox_info.b.data),bool(self.xbox_info.x.data),bool(self.xbox_info.y.data)]
        self.panel_xbox_pub.publish(self.panel_info)

    def longitudinal_control(self):
        self.thottle_info.pot.data = self.xbox_info.right_trigger.data
        self.thottle_info.increase_maxvel.data = self.xbox_info.dpad_up.data
        self.thottle_info.decrease_maxvel.data =  self.xbox_info.dpad_down.data

        #Detect down bottom to decrease velocity
        #Change max velocity
        if bool(self.thottle_info.increase_maxvel.data):
            if self.new_maxvel<=self.safe_velocity-5:
                self.new_maxvel+=5
        if bool(self.thottle_info.decrease_maxvel.data):
            if self.new_maxvel>=5:
                self.new_maxvel-=5
        if self.old_maxvel != self.new_maxvel:
            self.limit_pot = interp(self.new_maxvel, [0,100], [0,self.safe_pot])
            self.old_maxvel=self.new_maxvel
            self.get_logger().info('New max velocity: '+ str(self.new_maxvel)+" %")
            self.get_logger().info('Pot Position: '+ str(self.limit_pot))
            self.bus.send(can.Message(arbitration_id=self.throttle_module_id,is_extended_id=False, data=[self.max_id,int(self.limit_pot)]), timeout=1)
        #Change pot position
        self.new_pot = self.thottle_info.pot.data

    def lateral_control(self):
        msg = Vector3()
        
        brake_data = self.xbox_info.right_trigger.data
        self.vehicle_control.steer = self.xbox_info.leftx.data
        # self.vehicle_control_pub.publish(self.vehicle_control)
        joystick = self.xbox_info.leftx.data
        # self.get_logger().info("Joystick pos: %d" %joystick)
        # self.get_logger().info("Wheel angle: %f" %self.steering_wheel_angle)
        
        if(joystick != 0):
            dire = joystick / abs(joystick)
        else:
            dire = 0

        if dire > 0:
            if(self.max_steering - self.steering_wheel_angle > 0):
                msg.x = float(dire)
        else:
            if dire < 0:
                if(-self.max_steering - self.steering_wheel_angle < 0):
                    msg.x = float(dire)
            else:
                msg.x = 0.0
        
        msg.z = brake_data

        if msg.x > 0:
            dir = 1     # Normal -> CW:0, CCW:1, but inverted due to gears
        elif msg.x < 0:
            dir = 0
        else:
            dir = 2

        # self.steering_pub.publish(msg)
        self.bus.send(can.Message(arbitration_id=self.steering_module_id,is_extended_id=False, data=[self.dir_id,int(dir)]), timeout=1)

    def publish_drive_mode(self):
        #Toggle car mode and pedal with XBOX controller   
        start_btn = bool(self.joy_stick.Start())
        if not self.prev_start_btn_state and start_btn:
            drive_mode_msg = String()
            if self.drive_mode == "Manual":
                #Activate driver pedal
                drive_mode_msg.data = "Controller"
                self.drive_mode_pub.publish(drive_mode_msg)
                self.drive_mode = "Controller"
                self.bus.send(self.drive_mode_dict["auto"],timeout=1)
                # self.bus.send(can.Message(arbitration_id=self.throttle_module_id,is_extended_id=False, data=[self.car_mode_id,0x1]), timeout=1)
                # self.bus.send(can.Message(arbitration_id=self.throttle_module_id,is_extended_id=False, data=[self.motor_mode_id,0x1]), timeout=1)
            else:
                #Activate digital potentiometer
                drive_mode_msg.data = "Manual"
                self.drive_mode_pub.publish(drive_mode_msg)
                self.drive_mode = "Manual"     
                self.bus.send(self.drive_mode_dict["manual"],timeout=1)
                # self.bus.send(can.Message(arbitration_id=self.throttle_module_id,is_extended_id=False, data=[self.car_mode_id,0x0]), timeout=1) 
                # self.bus.send(can.Message(arbitration_id=self.throttle_module_id,is_extended_id=False, data=[self.motor_mode_id,0x0]), timeout=1)      
        self.prev_start_btn_state = start_btn

    def xbox_timer(self):
        if self.joy_stick.connected():
            self.publish_drive_mode()
            if self.drive_mode == "Controller":
                self.lateral_control()
                self.longitudinal_control()
                self.xbox_info.connected.data = self.joy_stick.connected()
                self.xbox_info.back.data = self.joy_stick.Back()
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
                #self.panel_controller()
            # else:
            # self.get_logger().warn("Drive mode: " + self.drive_mode)
            # self.get_logger().info('Data: "%f"' % self.xbox_info.leftx.data)

    def throttle_timer(self):
        #Modo 2 (0-100%) en 100 segundos
        if int(self.new_pot)>0:
            self.temp_pot=100 if self.temp_pot>=100 else self.temp_pot+5
            temp_pos = interp(self.temp_pot, [0,100], [1,self.limit_pot]) 
            self.get_logger().info('Vel position: '+ str(self.temp_pot))
            self.get_logger().info('Pot position: '+ str(temp_pos))
            self.bus.send(can.Message(arbitration_id=self.throttle_module_id,is_extended_id=False,  data=[self.pot_id,int(temp_pos)]), timeout=1)
        else:
            self.temp_pot=0 if self.temp_pot<=0 else self.temp_pot-15
            temp_pos = interp(self.temp_pot, [0,100], [1,self.limit_pot]) 
            self.get_logger().info('Vel position: '+ str(self.temp_pot))
            self.get_logger().info('Pot position: '+ str(temp_pos))
            self.bus.send(can.Message(arbitration_id=self.throttle_module_id,is_extended_id=False,  data=[self.pot_id,int(temp_pos)]), timeout=1)

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