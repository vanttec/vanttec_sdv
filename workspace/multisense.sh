#!/bin/bash
sudo systemctl stop NetworkManager
source install/setup.bash
sudo ifconfig enx00e04c3619be 10.66.171.20
sudo ip link set down enx00e04c3619be;
sudo ip link set enx00e04c3619be mtu 1500;
sudo ip link set up enx00e04c3619be;
sudo systemctl start NetworkManager
