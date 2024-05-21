#!/bin/bash
sudo systemctl stop NetworkManager
source install/setup.bash
sudo ifconfig <your_interface_id> 10.66.171.20
sudo ip link set down <your_interface_id>;
sudo ip link set <your_interface_id> mtu 1500;
sudo ip link set up <your_interface_id>;
sudo systemctl start NetworkManager

