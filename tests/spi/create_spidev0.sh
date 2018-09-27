#!/bin/bash

# For the SPI where are going to use serbus library
# wich is basically a wrapper of the standard SPI-ioctl

# Enable SPI0 on uEnv.txt

# Reset the BBB

# Load SPIDEV0 device on /dev/ using cape manager

echo SPIDEV0 > /sys/devices/bone_capemgr.*/slots


