#!/bin/sh
sudo ifconfig $1 txqueuelen 100000 
sudo ip link set $1 type can bitrate $2

sudo ifconfig $1 up
sudo ifconfig $1 txqueuelen 100000 