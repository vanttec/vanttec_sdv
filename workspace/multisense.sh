#!/bin/bash
sudo systemctl stop NetworkManager
source install/setup.bash
sudo ifconfig enx00e04c6801e1 10.66.171.20
sudo ip link set down enx00e04c6801e1;
sudo ip link set enx00e04c6801e1 mtu 1500;
sudo ip link set up enx00e04c6801e1;
sudo systemctl start NetworkManager

