# Encoders

Configuration scripts and ROS2 node drivers for the encoders:

* 1 x [IFM RM8004](https://www.ifm.com/mx/es/product/RM8004?tab=documents) - Absolute Multiturn Encoder
    * 4096 revolutions, 24-bit resolution
* 2 x [Briter](https://briterencoder.com/product/canbus-multi-turn-absolute-rotary-encoder/) CANbus Multi-turn Absolute Rotary Encoder
    * 24 revolutions, 10-bit resolution

## IFM RM8004

This encoder has a preoperational and operational mode. The preoperational mode is used to load and save parameters to the encoder by
sending CAN frames to the device. Once the configuration is complete, the operational mode must be enabled to actually use the device.

The encoder node number is 1Fh + 1h = 20h.

### Pre-operational mode
On connection to the supply, the encoder automatically enters to the preoperational mode, which is indicated by the LED in green (no flashing).

Here is a frame template to read/write objects to the encoder:

``` 
cansend can0 ID # COMMAND INDEX SUBID DATA

```

ID: 600h + NODE NUMBER
COMMAND: (1 byte)
INDEX: (2 bytes, big endian) object index
SUBID: (1 byte)
DATA: (4 bytes, big endian)

The COMMAND byte is chosen accordingly to a read/write operation. Check the next table:
| COMMAND | DATA LENGTH | DATA TYPE | FUNCTION |
|---------|-------------|-----------|----------|
| 43h     | 4           | u32       | read     |
| 47h     | 3           | u24       | read     |
| 4Bh     | 2           | u16       | read     |
| 4Fh     | 1           | u8        | read     |
| 23h     | 4           | u32       | write    |
| 27h     | 3           | u24       | write    |
| 2Bh     | 2           | u16       | write    |
| 2Fh     | 1           | u8        | write    |

The object, index, sub index, and data depends on the what is required. For example, to check the current encoder position, one must send (check datasheet for details):

``` 
cansend can0 620#43046000

``` 
And to store all parameters:

``` 
cansend can0 620#2310100173617665

``` 
Check datasheet on how to change baud rates or the cyclic timer.


### Operational mode
To enter the operational mode, the 2 bytes must be send 01h 00h, with the 00h identifier. If using socketCAN through the terminal, the next command
must be used:

``` 
cansend can0 000#0100 

```

Once the operational mode is entered, the LED will start flashing each second.
To go back to the pre-operational mode, the next command must be used:

``` 
cansend can0 000#8000 

```

In the operational mode the first transmit PDO (1A0h) is used to send the current position value without any request by the host. The cycle time can be programmed in milliseconds for values between 1 ms and 65536 ms (this must be configured in the pre-operational mode).

To set cyclic time to 100ms (check datasheet for details):

``` 
cansend can0 620#2B00620064000000

```

Don't forget to store parameters.