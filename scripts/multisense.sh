#!/bin/bash
sudo systemctl stop NetworkManager
source install/setup.bash
sudo ifconfig enx207bd26d9c4e 10.66.171.20
sudo ip link set down enx207bd26d9c4e;
sudo ip link set enx207bd26d9c4e mtu 1500;
sudo ip link set up enx207bd26d9c4e;
sudo systemctl start NetworkManager
