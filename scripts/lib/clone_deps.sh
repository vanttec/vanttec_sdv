#!/bin/bash

clone_deps() {
    local DEPS_DIR="$1"
    local REPO_DIR="$1"
    local SYNC="${2:-false}" 

    local NAVPILOT_DIR="$REPO_DIR/navpilot-framework"

    if [ ! -d "$NAVPILOT_DIR" ]; then
        echo "[clone_deps] Clonaning navpilot-framework..."
        git clone https://github.com/armando-genis/navpilot-framework.git "$NAVPILOT_DIR"
    elif [ "$SYNC" = "true" ]; then
        echo "[clone_deps] Updating navpilot-framework..."
        git -C "$NAVPILOT_DIR" pull
    else
        echo "[clone_deps] navpilot-framework already exist, skip. (use --sync for update)"
    fi

    local NAVPILOT_DIR="$DEPS_DIR/navpilot-framework"

    _clone_or_pull() {
        local DIR="$1"
        local URL="$2"
        shift 2
        local EXTRA_ARGS=("$@")   # ej. -b ros2

        if [ ! -d "$DIR" ]; then
        git clone "${EXTRA_ARGS[@]}" "$URL" "$DIR"
        elif [ "$SYNC" = "true" ]; then
        echo "[sync] $DIR"
        git -C "$DIR" pull
        fi
    }

    _clone_or_pull "$SRC/sensor_stack/velodyne"                        https://github.com/ros-drivers/velodyne.git
    _clone_or_pull "$SRC/sensor_stack/vectornav"                       https://github.com/dawonn/vectornav.git                    -b ros2
    _clone_or_pull "$SRC/mapping_modules/LIO-SAM"                      https://github.com/TixiaoShan/LIO-SAM.git                  -b ros2
    _clone_or_pull "$SRC/localization_modules/ndt_omp_ros2"            https://github.com/rsasaki0109/ndt_omp_ros2
    _clone_or_pull "$SRC/localization_modules/lidar_localization_ros2" https://github.com/rsasaki0109/lidar_localization_ros2.git
    _clone_or_pull "$SRC/mrt_cmake_modules"                            https://github.com/KIT-MRT/mrt_cmake_modules.git

    if [ ! -d "$REPO_DIR/workspace/src/mrt_cmake_modules" ] || [ "$SYNC" = "true" ]; then
        echo "[clone_deps] Copy packages to workspace/src..."
         cp -r "$SRC/"* "$REPO_DIR/workspace/src/"
    fi
}