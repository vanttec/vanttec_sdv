#!/bin/bash

REPO_DIR="${1:-/workspace}"
SYNC="${2:-false}"
SHELL_TYPE="${3:-bash}"
DEPS_DIR="/opt/vanttec_deps" 

SETUP_FILE="install/setup.$SHELL_TYPE"

source "$REPO_DIR/scripts/lib/clone_deps.sh"
source "$REPO_DIR/scripts/lib/install_tinyspline.sh"
source "$REPO_DIR/scripts/lib/build_workspace.sh"

echo "=== 🐳 Setup: Docker ==="

clone_deps         "$DEPS_DIR" "$REPO_DIR" "$SYNC"
install_tinyspline "/opt" ""    
build_workspace "$REPO_DIR/workspace" "$SHELL_TYPE"