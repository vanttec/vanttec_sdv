#!/bin/bash

# Immediately catch all errors
set -eo pipefail

# Uncomment for debugging
# set -x
# env

# Enable autocomplete for user
cp /etc/skel/.bashrc ~/

# Check if srv folder exists
# if [ -d "$ROOT_SRV" ]; then
    # Setup Nav2 web app
    for dir in "/vanttec_sdv/.devcontainer/caddy/srv/"*; do
        # Print the directory path
        echo "$dir"
        # Check if the path is a directory and create a symbolic link in the root server directory if it is
        if [ -d "$dir" ]; then
            ln -s "$dir" "$ROOT_SRV"
        fi
    done
# fi