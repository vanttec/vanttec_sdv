#!/bin/sh

sudo ip link set $1 type can bitrate $2

sudo ifconfig $1 up