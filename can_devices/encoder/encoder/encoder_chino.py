#!/usr/bin/env python
import can
import time
import rclpy
from rclpy.node import Node
from std_msgs.msg import Int32, Int16, Float64

# import usb

class EncoderPublisher(Node):

    def __init__(self):
        super().__init__('encoder_rm')
        self.publisher_absolute_pos = self.create_publisher(Int32, 'encoder/abs_pos', 10)
        # self.publisher_turn_number = self.create_publisher(Int16, 'encoder/turn_num', 10)
        self.publisher_angle = self.create_publisher(Float64, 'encoder/angle', 10)
        timer_period = 0.01 #Seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.bus = can.interface.Bus(bustype='socketcan', channel='can0', bitrate=125000)

        # self.dev = usb.core.find(idVendor=0x1D50, idProduct=0x606F)
        # self.bus = can.Bus(
        #     interface="gs_usb",
        #     channel=self.dev.product,
        #     bus=self.dev.bus,
        #     address=self.dev.address,
        #     bitrate=125000,
        # )

        self.sendMsg = can.Message(arbitration_id=1, is_extended_id=False, data=[0x04, 0x01, 0x01, 0x00])

        self.steps = 4096
        self.degrees = 360

    def timer_callback(self):
        absPos = Int32()
        # turNum = Int16()
        angle = Float64()
        self.bus.send(self.sendMsg, timeout=1)
        receivedMsg = self.bus.recv(1)

        if receivedMsg is not None:
            if receivedMsg.is_rx:

                d = int( (receivedMsg.data.hex()[6:])[::-1], 16)
                absPos.data = d
                
                decimal = d / 65535 # 0 - 1
                angle.data = decimal * self.degrees # 0 - 360
                
                self.publisher_absolute_pos.publish(absPos)
                # self.publisher_turn_number.publish(turNum)
                self.publisher_angle.publish(angle)

    # def read(self):
    #     # self.bus.send(self.sendMsg, timeout=1)
    #
    #     receivedMsg = self.bus.recv(0)
    #     if receivedMsg is not None:
    #         if receivedMsg.is_rx:
    #             # return int( (receivedMsg.data.hex()[6:])[::-1], 16)
    #             return receivedMsg.data.hex()

    # FUNCIONAL
    def cambiar_id(self, id, new):
        # command 0x02 - change device id
        msg = can.Message(arbitration_id=id, is_extended_id=False, data=[0x04, id, 0x02, new])
        self.bus.send( msg, timeout=1 )

    # FUNCIONAL
    def query_mode(self, id):
        # command 0x04 - set encoder to query mode
        msg = can.Message(arbitration_id=id, is_extended_id=False, data=[0x04, id, 0x04, 0x00])
        self.bus.send( msg, timeout=1 )

    # esto viene dentro del datasheet:
    # Note: After setting a too short return time, the encoder will no longer be able to set other parameters, use it with caution
    # microsegundos: 50 - 65535
    # FUNCIONAL
    def automatic_mode(self, id, microsegundos):
        if microsegundos < 50 or microsegundos > 65535:
            raise Exception('Introduce un valor entre 50 y 65535 microsegundos')

        # command 0x04 - set encoder to automatic mode
        msg = can.Message(arbitration_id=id, is_extended_id=False, data=[0x04, id, 0x04, 0xAA])
        self.bus.send( msg, timeout=1 )

        # command 0x05 - set automatic mode return interval
        microsegundos = self.int2hex(microsegundos)
        contenido_msg = [id, 0x05] + microsegundos
        contenido_msg.insert(0, len(contenido_msg) + 1)

        print(contenido_msg)

        msg = can.Message(arbitration_id=id, is_extended_id=False, data=contenido_msg)
        self.bus.send( msg, timeout=1 )

    # NO FUNCIONAL
    # # dirección en la manesillas del reloj
    # def clockwise(self, id):
    #     # command 0x07 - set the encoder's direction
    #     msg = can.Message(arbitration_id=id, is_extended_id=False, data=[0x04, id, 0x07, 0x00])
    #     self.bus.send( msg, timeout=1 )
    #
    # # dirección en contra de las manesillas del reloj
    # def counter_clockwise(self, id):
    #     # command 0x07 - set the encoder's direction
    #     msg = can.Message(arbitration_id=id, is_extended_id=False, data=[0x04, id, 0x07, 0x01])
    #     self.bus.send( msg, timeout=1 )

    # valor de 0 a 1 (decimal)
    # FUNCIONAL
    def cambiar_posicion(self, id, pos):
        abspos = int(pos * 65535)

        # command 0x0D - set the encoder's position
        abspos = self.int2hex(abspos)
        contenido_msg = [id, 0x0D] + abspos
        contenido_msg.insert(0, len(contenido_msg) + 1)

        msg = can.Message(arbitration_id=id, is_extended_id=False, data=contenido_msg)
        self.bus.send( msg, timeout=1 )

    # resetea la posición a 0
    # FUNCIONAL
    def position_reset(self, id):
        msg = can.Message(arbitration_id=id, is_extended_id=False, data=[0x04, id, 0x06, 0x00])
        self.bus.send( msg, timeout=1 )

    # 500K; 1M; 250K; 125K; 100K
    # Cambia el baudrate de la interfaz tmb
    # FUNCIONAL
    def cambiar_baudrate(self, id, baud):

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
        msg = can.Message(arbitration_id=id, is_extended_id=False, data=[0x04, id, 0x03, baud])
        self.bus.send( msg, timeout=1 )


    def int2hex(self, n):
        h = format(n, 'x')
        
        if len(h) % 2 != 0:
            leading = len(h)+1
            h = h.zfill(leading)

        return list(bytearray.fromhex(h)[::-1])
    
def main(args=None):
    rclpy.init(args=args)

    encoder_publisher = EncoderPublisher()

    encoder_publisher.query_mode(1)

    rclpy.spin(encoder_publisher)

    encoder_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()
