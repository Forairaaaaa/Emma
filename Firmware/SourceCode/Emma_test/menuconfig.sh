#!/bin/bash
### This is for lazzy shit like me to menuconfig the project

# Configs
IDF_PATH=$HOME/esp/esp-idf
SERIAL_PORT=/dev/ttyACM0


help() {
    sed -rn 's/^### ?//;T;p' "$0"
}

if [[ "$1" == "-h" ]] || [[ "$1" == "--help" ]]; then
    help
    exit 1
fi

# Get idf
. ${IDF_PATH}/export.sh

# Build and flash and monitor
idf.py menuconfig
