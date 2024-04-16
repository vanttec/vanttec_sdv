#!/bin/bash

echo "source /opt/ros/${ROS_DISTRO}/setup.bash" >> ~/.bashrc
echo "source /opt/ros/${ROS_DISTRO}/setup.zsh" >> ~/.zshrc
echo "eval \"\$(register-python-argcomplete3 ros2)\"" >> ~/.zshrc
echo "eval \"\$(register-python-argcomplete3 colcon)\"" >> ~/.zshrc