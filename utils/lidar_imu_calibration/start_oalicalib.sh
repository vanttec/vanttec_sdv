#!/bin/bash
REPO_PATH="$(pwd)/OA-LICalib"
git_root_dir=$(git rev-parse --show-toplevel)

docker build -t oalicalib OA-LICalib/docker
docker run -it --env="DISPLAY" --volume="$HOME/.Xauthority:/root/.Xauthority:rw" --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" --volume="$REPO_PATH:/root/catkin_oa_calib/src/OA-LICalib" --volume="$git_root_dir/workspace:/workspace" --volume="$REPO_PATH:/ros1_ws/src/OA-LICalib" oalicalib bash

