#!/bin/bash

sudo chmod 666 /dev/ttyUSB0
sudo ip link set down can2
sudo ip link set can2 type can bitrate 125000
sudo ip link set up can2

source /opt/ros/humble/setup.bash
cd workspace
source install/setup.bash

# Create a new tmux session
session_name="vtec_sdv$(date +%s)"
tmux new-session -d -s $session_name

# Top row: split pane 0 horizontally into two (pane 0 and pane 1)
tmux select-pane -t 0
tmux split-window -h -p 50

# Top row: split the right top pane (pane 1) horizontally into two (pane 1 and pane 2)
tmux select-pane -t 1
tmux split-window -h -p 50

# Top row: split the right top pane (pane 2) horizontally into two (pane 2 and pane 3)
tmux select-pane -t 2
tmux split-window -h -p 50

# Split the window vertically into top (pane 0) and bottom (pane 4)
tmux select-pane -t 0
tmux split-window -v -p 50

# Split the window vertically into top (pane 1) and bottom (pane 5)
tmux select-pane -t 1
tmux split-window -v -p 50

# Split the window vertically into top (pane 2) and bottom (pane 6)
tmux select-pane -t 2
tmux split-window -v -p 50

# Split the window vertically into top (pane 3) and bottom (pane 7)
tmux select-pane -t 3
tmux split-window -v -p 50

# Split the window vertically into top (pane 8) and bottom (pane 8)
tmux select-pane -t 7
tmux split-window -v -p 50

tmux select-pane -t 7
tmux split-window -h -p 50

tmux select-layout tiled

# Assign commands to each pane with a 5-second delay between each

# Pane 0: Start localization
tmux select-pane -t 0
tmux send-keys "ros2 launch vanttec_sdv/workspace/src/localization_modules/launch/localization.launch.py" Enter
sleep 1

# Pane 1: Launch ROS2 clustering
tmux select-pane -t 1
tmux send-keys "ros2 launch sensors_launch lidar_imu.launch.py" Enter
sleep 1

# Pane 2: Start ROS2 control
tmux select-pane -t 2
tmux send-keys "ros2 launch sdv_control control_launch.py" Enter
sleep 1

# Pane 3: Launch traduction_control
tmux select-pane -t 3
tmux send-keys "cd src" Enter
tmux send-keys "ros2 run sdv_velocity velocity_node" Enter
sleep 1

# Pane 4: Launch traduction_steering
tmux select-pane -t 4
tmux send-keys "cd src" Enter
tmux send-keys "ros2 launch pointcloud_clustering_KDTree pointcloud_clustering.launch.py" Enter
#tmux send-keys "ros2 launch vanttec_sdv/workspace/src/path_planning/launch/planning_obstacles.launch.py" Enter
sleep 1

# Pane 5: Launch velocity
tmux select-pane -t 5
tmux send-keys "ros2 run sdv_can sdv_can_node" Enter
sleep 1

# Pane 6: Launch path planning dynamic
tmux select-pane -t 6
tmux send-keys "ros2 run sdv_control waypoint_publisher_node.py " Enter
sleep 1 

# Pane 7: Launch ROS2 CAN
tmux select-pane -t 7
tmux send-keys "jtop" Enter
sleep 1

#Pane 8: Launch service activate and sensor stack
tmux select-pane -t 8
tmux send-keys "cd src" Enter
tmux send-keys 'ros2 service call /sdv/steering/set_mode sdv_msgs/srv/Uint8 "{data: 1}"' Enter
tmux send-keys 'ros2 service call /sdv/steering/reset_encoder std_srvs/srv/Empty' Enter

# tmux select-pane -t 9
# tmux send-keys 'ros2 launch tcp_gateway jetson1_server.launch.py' Enter




# Optional: Add key bindings to cycle through panes
tmux bind-key -n C-a select-pane -t :.+ 
tmux bind-key -n C-s select-pane -t :.-

# Attach to the tmux session
tmux -2 attach-session -t $session_name

cd ..
sudo ip link set down can2

