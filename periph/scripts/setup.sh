#!/bin/bash

# Load SPIDEV0 device on /dev/ using cape manager

echo BB-SPI0-01 > /sys/devices/bone_capemgr.*/slots

ls -lh /dev/spi*

