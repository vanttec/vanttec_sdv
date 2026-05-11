#!/bin/bash

install_tinyspline() {
    local REPO_DIR="$1"
    local SUDO_CMD="${2:-}"
    local BUILD_DIR="$DEPS_DIR/tinyspline"

    if [ -d "$REPO_DIR/tinyspline" ]; then
        echo "[tinyspline] Already exist, skip."
        return
    fi

    echo "[tinyspline] Cloning y compilation in $BUILD_DIR..."
    git clone https://github.com/msteinbeck/tinyspline.git "$BUILD_DIR"
    mkdir -p "$BUILD_DIR/build"
    cd "$BUILD_DIR/build"
    cmake ..
    cmake --build .
    $SUDO_CMD cmake --install .
    cd - > /dev/null
}
