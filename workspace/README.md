# Multisense Setup

We use a bash script [multisense.sh](https://github.com/vanttec/vanttec_sdv/blob/features/vision/workspace/multisense.sh) that configures the network interface where the Multisense Ethernet is connected (Jetson, personal laptop, etc) with the ```camera IP address 10.66.171.20```.

This guide provides step-by-step instructions on how to connect a Multisense camera to a PC.

## Prerequisites

Before you begin, ensure you have the following:

- The Multisense camera
- A PC with a compatible operating system (Linux recommended)
- Administrative (sudo) access to the PC
- Ethernet cable to connect the camera to the PC

### 1. Navigate to the Script Directory

First, navigate to the directory where the script `multisense.sh` is located. Assuming the script is in `vanttec_sdv/workspace`:

```bash
cd vanttec_sdv/workspace
```

### 2. Edit the Script to Set the Correct Interface ID

The identifier (ID) of the network interface may vary depending on the specific device. 

Ensure that you have connected the Ethernet in your PC.

You can determine the correct ID by using the `ifconfig` command. Look for the ID associated with your Ethernet connection.


```bash
ifconfig
```


Edit the bash script to replace the placeholder interface ID with the one specific to your PC.

```bash
#!/bin/bash
sudo systemctl stop NetworkManager
source install/setup.bash
# Replace <your_interface_id> with your network interface ID
sudo ifconfig <your_interface_id> 10.66.171.20
sudo ip link set down <your_interface_id>
sudo ip link set <your_interface_id> mtu 1500
sudo ip link set up <your_interface_id>
sudo systemctl start NetworkManager
```
### 3. Run the Script

After editing the script, run it to apply the network configurations:

```bash
sudo multisense.sh
```

If everything goes well, there should be no messages output to the terminal.

## Troubleshooting

If you encounter any issues, verify the following:

- Ensure the network interface ID is correct using `ifconfig`.
- Check that the IP address assigned does not conflict with other devices on the network.
- Confirm the Multisense camera is powered on and properly connected to the PC.
