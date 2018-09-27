#!/bin/bash

# Load SPIDEV0 device on /dev/ using cape manager

echo SPIDEV0 > /sys/devices/bone_capemgr.*/slots

