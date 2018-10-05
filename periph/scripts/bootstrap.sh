#!/bin/bash

## This script enables spi chipselect 0 on bus 1

BASEDIR=$(dirname $0)

# Compile .dtbo for configuring pins

dtc -O dtb -o ${BASEDIR}/BB-SPI0-01-00A0.dtbo -b 0 -@ ${BASEDIR}/BB-SPI0-01-00A0.dts 

cp ${BASEDIR}/BB-SPI0-01-00A0.dtbo /lib/firmware/

#enable device tree overlay

echo BB-SPI0-01 > /sys/devices/bone_capemgr.*/slots

# Enable SPI0 on uEnv.txt
echo \#\#Enable SPI0 >> /boot/uEnv.txt
echo optargs=quiet drm.debug=7 >> /boot/uEnv.txt
echo capemgr.enable_partno=BB-SPI0-01 >> /boot/uEnv.txt

# Reset the BBB
#reboot


