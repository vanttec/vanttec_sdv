#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

usage() {
  echo "Use: source setup.sh --target <local|docker>  [--shell <bash|zsh>] [--sync]"
  return 1 2>/dev/null || exit 1
}

TARGET=""
SYNC="false"
SHELL_TYPE="bash"   # default

while [[ $# -gt 0 ]]; do
  case "$1" in
    --target) TARGET="$2"; shift 2 ;;
    --shell)  SHELL_TYPE="$2"; shift 2 ;;
    --sync)   SYNC="true";     shift   ;;
    *) usage; return 1 2>/dev/null || exit 1 ;;
  esac
done

if [ -z "$TARGET" ]; then
  usage
  return 1 2>/dev/null || exit 1
fi

TARGET_SCRIPT="$SCRIPT_DIR/scripts/targets/$TARGET.sh"

if [ ! -f "$TARGET_SCRIPT" ]; then
  echo "[error] Target '$TARGET' doesn't exist. Options: local, docker"
  return 1 2>/dev/null || exit 1
fi

source "$TARGET_SCRIPT" "$SCRIPT_DIR" "$SYNC" "$SHELL_TYPE"