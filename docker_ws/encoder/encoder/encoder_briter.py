#!/usr/bin/env python
import can
import time
import rclpy
from rclpy.node import Node

from sdv_msgs.msg import Encoder
# import usb

class EncoderDevice(Node):

    def __init__(self, encoder_id, encoder_mode):
        super().__init__('encoder_rm')
        
        self.id = encoder_id
        self.encoder_mode = encoder_mode
        self.bus = can.interface.Bus(bustype='socketcan', channel='can0', bitrate=125000)

        self.publisher = self.create_publisher(Encoder, 'encoder_freno', 10)
        self.set_encoder_mode()

        timer_period = 1 #Seconds
        self.timer = (self.create_timer(timer_period, self.query_timer_callback) 
                        if encoder_mode == 0x00 
                        else self.create_timer(timer_period, self.automatic_timer_callback))


        self.steps = 4096 # total steps = 4096*24 = 98304
        self.degrees = 360

    def query_timer_callback(self):
        # ask for position
        self.ask_position()

        # receive message
        msg = Encoder()
        receivedMsg = self.bus.recv(0)

        # process message
        if receivedMsg is not None:
            if receivedMsg.arbitration_id == self.id:
                decoded_msg = receivedMsg.data.hex()[6:]
                hex_pos = (decoded_msg[6:7]+decoded_msg[4:6]+decoded_msg[2:4]+decoded_msg[0:2])
                absolute_pos = int(hex_pos, 16)
                # print(absolute_pos)
                step = absolute_pos%self.steps

                msg.angle = float(self.degrees*step/self.steps)
                msg.abs_angle = -1.0
                msg.turn = -1

                self.publisher.publish(msg)

    
    def automatic_timer_callback(self):

        # receive message
        msg = Encoder()
        receivedMsg = self.bus.recv(0)

        # process message
        if receivedMsg is not None:
            if receivedMsg.arbitration_id == self.id:
                decoded_msg = receivedMsg.data.hex()[6:]
                hex_pos = (decoded_msg[6:7]+decoded_msg[4:6]+decoded_msg[2:4]+decoded_msg[0:2])
                absolute_pos = int(hex_pos, 16)
                # print(absolute_pos)
                step = absolute_pos%self.steps

                msg.angle = float(self.degrees*step/self.steps)
                msg.abs_angle = -1.0
                msg.turn = -1

                self.publisher.publish(msg)

    def ask_position(self):
        msg = can.Message(arbitration_id=self.id, is_extended_id=False, data=[0x04, self.id, 0x01, 0x00])
        self.bus.send( msg, timeout=1 )

    def set_encoder_mode(self):
        # command 0x04 - set encoder mode

        msg = can.Message(arbitration_id=self.id, is_extended_id=False, data=[0x04, self.id, 0x04, self.encoder_mode])
        self.bus.send( msg, timeout=1 )

    # FUNCIONAL
    def cambiar_id(self, new_id):
        # command 0x02 - change device id
        msg = can.Message(arbitration_id=self.id, is_extended_id=False, data=[0x04, self.id, 0x02, new_id])
        self.bus.send( msg, timeout=1 )
        self.id = new_id

    # 500K; 1M; 250K; 125K; 100K
    # Cambia el baudrate de la interfaz tmb
    # FUNCIONAL
    def cambiar_baudrate(self, baud):

        if baud == 500000:
            baud = 0x00
        elif baud == 1000000:
            baud = 0x01
        elif baud == 250000:
            baud = 0x02
        elif baud == 125000:
            baud = 0x03
        elif baud == 100000:
            baud = 0x04
        else:
            raise Exception('Introduce un valor válido')

        # command 0x03 - set the encoder's baudrate
        msg = can.Message(arbitration_id=self.id, is_extended_id=False, data=[0x04, id, 0x03, baud])
        self.bus.send( msg, timeout=1 )


    # *-------------* FROM HERE AND ON METICULOUS TESTING OF FUNCTIONS IS REQUIRED *----------------------*
    # *-------------* FROM HERE AND ON METICULOUS TESTING OF FUNCTIONS IS REQUIRED *----------------------*
    # *-------------* FROM HERE AND ON METICULOUS TESTING OF FUNCTIONS IS REQUIRED *----------------------*
    # *-------------* FROM HERE AND ON METICULOUS TESTING OF FUNCTIONS IS REQUIRED *----------------------*
    # *-------------* FROM HERE AND ON METICULOUS TESTING OF FUNCTIONS IS REQUIRED *----------------------*
    # *-------------* FROM HERE AND ON METICULOUS TESTING OF FUNCTIONS IS REQUIRED *----------------------*
    # *-------------* FROM HERE AND ON METICULOUS TESTING OF FUNCTIONS IS REQUIRED *----------------------*

    # esto viene dentro del datasheet:
    # Note: After setting a too short return time, the encoder will no longer be able to set other parameters, use it with caution
    # microsegundos: 50 - 65535
    # NO FUNCIONAL
    def set_return_time(self, microsegundos):
        if microsegundos < 50 or microsegundos > 65535:
            raise Exception('Introduce un valor entre 50 y 65535 microsegundos')

        # command 0x05 - set automatic mode return interval
        microsegundos = microsegundos.to_bytes(2,'big')
        print(microsegundos)
        msg = bytearray([self.id, 0x05])
        msg.extend(microsegundos)

        print(msg)

        # msg = can.Message(arbitration_id=self.id, is_extended_id=False, data=msg)
        # self.bus.send( msg, timeout=1 )

    # NO FUNCIONAL
    # # dirección en la manesillas del reloj
    # def clockwise(self, id):
    #     # command 0x07 - set the encoder's direction
    #     msg = can.Message(arbitration_id=self.id, is_extended_id=False, data=[0x04, id, 0x07, 0x00])
    #     self.bus.send( msg, timeout=1 )
    #
    # # dirección en contra de las manesillas del reloj
    # def counter_clockwise(self, id):
    #     # command 0x07 - set the encoder's direction
    #     msg = can.Message(arbitration_id=self.id, is_extended_id=False, data=[0x04, id, 0x07, 0x01])
    #     self.bus.send( msg, timeout=1 )

    # valor de 0 a 1 (decimal)
    # NO FUNCIONAL
    def cambiar_posicion(self, id, pos):
        if pos < 0 or pos > 1:
            raise Exception('Introduce un valor entre 0 y 1')

        abspos = int(pos * 65535)

        # command 0x0D - set the encoder's position
        abspos = hex(abspos)
        contenido_msg = [self.id, 0x0D] + abspos
        contenido_msg.insert(0, len(contenido_msg) + 1)

        msg = can.Message(arbitration_id=self.id, is_extended_id=False, data=contenido_msg)
        self.bus.send( msg, timeout=1 )

    # resetea la posición a 0
    # FUNCIONAL
    def position_reset(self, id):
        msg = can.Message(arbitration_id=self.id, is_extended_id=False, data=[0x04, self.id, 0x06, 0x00])
        self.bus.send( msg, timeout=1 )
    
def main(args=None):
    rclpy.init(args=args)
    encoder_id = 0x13
    encoder_mode = 0x00 # 0x00 (Query), 0xAA (Automatic post back)

    encoder_publisher = EncoderDevice(encoder_id, encoder_mode)

    # encoder_publisher.set_encoder_mode()

    rclpy.spin(encoder_publisher)

    encoder_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()