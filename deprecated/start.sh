#!/bin/bash
container_name="sdv_dev_container"

start_bash_in_container() {
    if docker ps --format '{{.Names}}' | grep -q "^$container_name$"; then
        docker exec -it "$container_name" bash
    else
        echo "Error: Container '$container_name' is not running."
    fi
}

if docker ps --format '{{.Names}}' | grep -q "^$container_name$"; then
    echo "Container '$container_name' is running. Spawning new shell in container."
    start_bash_in_container
else
    echo "Container '$container_name' is not running. Starting container"
    workspace/src/isaac_ros_common/scripts/run_dev.sh $(pwd)/workspace
    start_bash_in_container
fi
