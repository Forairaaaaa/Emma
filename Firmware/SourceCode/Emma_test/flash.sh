#!/bin/bash
# This is a Build-Flash-Monitor script for WSl
# Firstly, use command < usbipd wsl attach -a -b [BUSID] > on PowerShell to auto attach the board

# Serial port
SERIAL_PORT=/dev/ttyACM0

echo "Build and flash to ${SERIAL_PORT}..."

# Get serial port permission
sudo chmod 777 ${SERIAL_PORT}
 
# Get idf
. $HOME/esp/esp-idf/export.sh

# Build and flash and monitor
# idf.py -p ${SERIAL_PORT} flash monitor
idf.py -p ${SERIAL_PORT} flash -b 115200 monitor

