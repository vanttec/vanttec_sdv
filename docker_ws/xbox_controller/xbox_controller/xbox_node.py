import rclpy
from rclpy.node import Node
import can
import struct
from numpy import interp

import xbox_controller.xbox_driver as xbox_driver
from std_msgs.msg import String, UInt8, Float32
from geometry_msgs.msg import Vector3
from sdv_msgs.msg import Encoder, PanelMsg#, XboxMsg, ThrottleMsg, VehicleControl 

class XboxNode(Node):
    def __init__(self):
        super().__init__('xbox_node')

        self.drive_mode = "No_Xbox_Controller"
        self.prev_start_btn_state = False

        self.controller_connected = False
        self.controller_stop = True

        self.joy_stick = xbox_driver.Joystick(50)
        

        self.bus = can.interface.Bus(bustype='socketcan', channel='can0', bitrate=125000)

        self.motor_mode_id = 0x6
        self.car_mode_id = 0x7

        self.drive_mode_sent = False

        # *------------------* VANTTEC_IDS *------------------*
        self.admin_id = 0x401
        self.general_module_id_tx = 0x403
        self.general_module_id_rx = 0x404 
        self.throttle_module_id = 0x406
        self.steering_module_id = 0x408
        self.braking_module_id = 0x412

        # *------------------* GENERAL *------------------*
        self.ask_status_general = False
        self.drive_mode_dict = {
                "manual": can.Message(arbitration_id=self.admin_id,is_extended_id=False, data=[0x2,0x0]),
                "auto": can.Message(arbitration_id=self.admin_id,is_extended_id=False, data=[0x2,0x1]),
                "status_general": can.Message(arbitration_id=self.general_module_id_tx,is_extended_id=False, data=[0x5,0x1])
            }
        self.general_msg = 0
        self.prev_general_msg = 0
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
    
        self.dir_id = 0x10

        self.brake_task_id = 0x8

        # *------------------* THROTTLE *------------------*
        self.safe_velocity=200 # % of safe_pot  
        self.safe_pot = 170
        self.old_maxvel = self.safe_velocity
        self.temp_pot= 1
        self.new_maxvel = self.safe_velocity 
        self.limit_pot = self.safe_velocity
        self.velocity_control = False
        # self.timer=self.create_timer(timer_period,self.throttle_timer)

        self.pot_data = 0
        self.increase_maxvel_data = 0
        self.decrease_maxvel_data = 0

        #Send WiperPot position
        self.pot_id = 0x5
        #Send Max velocity
        self.max_id = 0x8

        # *------------------* ROS MESSAGES *------------------*
        # self.xbox_info = XboxMsg()
        self.panel_info = PanelMsg()

        # *------------------* SUBSCRIBERS *------------------*
        self.encoder_sub = self.create_subscription(
            Encoder,
            '/ifm_encoder',
            self.encoder_callback,
            10
        )

        # USE THIS SUBSCRIBER ONLY WHEN CHARACTERIZATION OF THE VEHICLE IS REQUIRED.
        # COMMENT IT OUT OTHERWISE. DO NOT USE THIS METHOD TO CONTROL THE CAR.
        self.encoder_sub = self.create_subscription(
            UInt8,
            '/potentiometer_step',
            self.pot_callback,
            1
        )
        self.step_zero_sent = False

        # *------------------* PUBLISHERS *------------------*
        #self.xbox_status_pub = self.create_publisher(XboxMsg, 'xbox_controller/status', 10)
        self.panel_xbox_pub = self.create_publisher(PanelMsg, '/sdv/xbox_controller/xbox_panel', 10) 
        self.drive_mode_pub = self.create_publisher(String, '/sdv/xbox_controller/drive_mode', 10) 
        self.motor_mode_pub = self.create_publisher(String, '/sdv/xbox_controller/motor_mode', 10) 
        self.steering_pub = self.create_publisher(Vector3, '/steering_brake', 10)

        # *------------------* TIMER_CALLBACKS *------------------*
        timer_period = 0.1 #1 second
        self.timer=self.create_timer(timer_period,self.xbox_timer)

    # def drive_mode_callback(self,msg):
    #     self.drive_mode = msg.data

    def encoder_callback(self,msg):
        self.steering_wheel_angle = msg.abs_angle

    # USE THIS CALLBACK ONLY WHEN CHARACTERIZATION OF THE VEHICLE IS REQUIRED.
    # COMMENT IT OUT OTHERWISE. DO NOT USE THIS METHOD TO CONTROL THE CAR.
    def pot_callback(self, msg):
        if self.drive_mode == "Xbox_Controller":
            if self.limit_pot != msg.data:
                self.limit_pot = msg.data
                self.get_logger().info('Pot: '+ str(self.limit_pot))
                self.bus.send(can.Message(arbitration_id=self.throttle_module_id,is_extended_id=False, data=[self.pot_id,int(self.limit_pot)]), timeout=1)
                self.step_zero_sent = False
        else:
            if not self.step_zero_sent:
                self.bus.send(can.Message(arbitration_id=self.throttle_module_id,is_extended_id=False, data=[self.pot_id,int(0)]), timeout=1)
                self.step_zero_sent = True

    def longitudinal_control(self):
        self.pot_data = self.joy_stick.rightTrigger()
        self.increase_maxvel_data = self.joy_stick.dpadUp()
        self.decrease_maxvel_data =  self.joy_stick.dpadDown()
        #Detect down bottom to decrease velocity
        #Change max velocity
        if bool(self.increase_maxvel_data):
            if self.new_maxvel<=self.safe_velocity-5:
                self.new_maxvel+=5
        if bool(self.decrease_maxvel_data):
            if self.new_maxvel>=5:
                self.new_maxvel-=5
        if self.old_maxvel != self.new_maxvel:
            self.limit_pot = interp(self.new_maxvel, [0,100], [0,self.safe_pot])
            self.old_maxvel=self.new_maxvel
            # self.get_logger().info('New max velocity: '+ str(self.new_maxvel)+" %")
            # self.get_logger().info('Pot Position: '+ str(self.limit_pot))
            self.bus.send(can.Message(arbitration_id=self.throttle_module_id,is_extended_id=False, data=[self.max_id,int(self.limit_pot)]), timeout=1)
        #Change pot position
        #Modo 2 (0-100%) en 20 segundos
        if int(self.pot_data)>0:
            self.temp_pot=100 if self.temp_pot>=100 else self.temp_pot+5
            temp_pos = interp(self.temp_pot, [0,100], [1,self.limit_pot]) 
            # self.get_logger().info('Vel position: '+ str(self.temp_pot))
            # self.get_logger().info('Pot position: '+ str(temp_pos))
            self.bus.send(can.Message(arbitration_id=self.throttle_module_id,is_extended_id=False,  data=[self.pot_id,int(temp_pos)]), timeout=1)
        else:
            self.temp_pot=0 if self.temp_pot<=0 else self.temp_pot-15
            temp_pos = interp(self.temp_pot, [0,100], [1,self.limit_pot]) 
            # self.get_logger().info('Vel position: '+ str(self.temp_pot))
            # self.get_logger().info('Pot position: '+ str(temp_pos))
            self.bus.send(can.Message(arbitration_id=self.throttle_module_id,is_extended_id=False,  data=[self.pot_id,int(temp_pos)]), timeout=1)
        self.braking_control()

    def braking_control(self):
        brake_data = self.joy_stick.leftTrigger()
        # self.get_logger().info('Left trigger pos: ' + str(brake_data))
        brake_data = bytearray(struct.pack("f", brake_data))
        #Invert ieee74 floating point so it can be received correctly by STM32
        brake_data = brake_data[::-1]
        #Insert ID so it can select the proper STM32 Task
        brake_data = brake_data.insert(0,self.brake_task_id)
        # self.get_logger().info('Brake data: ' + str(brake_data))
        self.bus.send(can.Message(arbitration_id=self.braking_module_id,is_extended_id=False, data=brake_data), timeout=1)

    def lateral_control(self):
        joystick = self.joy_stick.leftX()
        # self.get_logger().info("Joystick pos: %d" %joystick)
        # self.get_logger().info("Wheel angle: %f" %self.steering_wheel_angle)
        
        if(joystick != 0):
            dire = joystick / abs(joystick)
        else:
            dire = 0

        if dire > 0:
            if(self.max_steering - self.steering_wheel_angle <= 0):
                dire = 0
        elif dire < 0:
            if(-self.max_steering - self.steering_wheel_angle >= 0):
                dire = 0
        
        if dire > 0:
            dir = 1     # Normal -> CW:0, CCW:1, but inverted due to gears
        elif dire < 0:
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
            if self.drive_mode == "No_Xbox_Controller":
                #Activate driver pedal
                drive_mode_msg.data = "Xbox_Controller"
                self.drive_mode_pub.publish(drive_mode_msg)
                self.drive_mode = "Xbox_Controller"
                #self.bus.send(self.drive_mode_dict["auto"],timeout=1)
            else:
                #Activate digital potentiometer
                drive_mode_msg.data = "No_Xbox_Controller"
                self.drive_mode_pub.publish(drive_mode_msg)
                self.drive_mode = "No_Xbox_Controller"     
                #self.bus.send(self.drive_mode_dict["manual"],timeout=1)
            self.drive_mode_sent = False 
            self.ask_status_general = True
        self.prev_start_btn_state = start_btn
        self.get_logger().info(self.drive_mode)

        
    def uint8_to_bool_list(self, num):
        # Convert the number to binary representation and remove the '0b' prefix
        binary_string = bin(num)[2:]
        # Pad the binary string with leading zeros to ensure a length of 8
        binary_string = binary_string.zfill(8)
        # Convert each character in the binary string to a boolean value
        bool_list = [bit == '1' for bit in binary_string]
        return bool_list
    
    def analyse_drive_mode(self):
        # The general module control mode Manual/Auto
        # If the user want to use Xbox controller, the drive mode buttons has to be turned on, so it is in Auto mode.
        # Else the system has to inform the user what to do if he wants to use auto mode.
        # If the emergency stops are activated, all the modules will enter manual mode, the system has to inform the user the following steps to reactivate auto mode.
        #  - Turned off Emergency stop, turned off the drivemode buttons if it is in auto mode and again turn on if he wants to activate auto mode .
        #  - Display a string message with topic name "sdv/drive_mode/logs"
        if self.ask_status_general :
            if not self.drive_mode_sent:
                self.bus.send(self.drive_mode_dict["status_general"],timeout=1)
                self.drive_mode_sent = True
            msg = self.bus.recv(0.05)
            if msg is not None:
                if msg.arbitration_id == self.general_module_id_rx:
                    self.general_msg = msg.data
                    self.ask_status_general = False

        if self.prev_general_msg != self.general_msg:

            if self.drive_mode=="Xbox_Controller" :
                #See Status of buttons general module and inform User if neccessary
                status_buttons  = self.uint8_to_bool_list(self.general_msg)
                main_dr, aux_dr, main_es, aux_es = status_buttons[7], status_buttons[6], status_buttons[5], status_buttons[4]
       
        self.prev_general_msg = self.general_msg

    def xbox_timer(self):
        if self.joy_stick.connected():
            self.publish_drive_mode()
            self.analyse_drive_mode()
            if self.drive_mode == "Xbox_Controller":
                # UNCOMMENT FOR NORMAL CAR OPERATION. COMMENT WHEN PERFORMING CHARACTERIZATION TESTS
                # self.lateral_control()
                # self.longitudinal_control()
                pass

  
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