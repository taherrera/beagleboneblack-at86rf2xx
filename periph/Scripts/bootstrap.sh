#!/bin/bash

BASEDIR=$(dirname $0)

# Compile .dtbo for configuring pins

dtc -O dtb -o ${BASEDIR}/BB-SPI1-01-00A0.dtbo -b 0 -@ ${BASEDIR}/BB-SPI1-01-00A0.dts 

cp ${BASEDIR}/BB-SPI1-01-00A0.dtbo /lib/firmware/

#enable device tree overlay

echo BB-SPI1-01 > /sys/devices/bone_capemgr.*/slots

# Enable SPI0 on uEnv.txt

echo optargs=quiet drm.debug=7 capemgr.disable_partno=BB-BONELT-HDMI,BB-BONELT-HDMIN >> /boot/uEnv.txt

echo capemgr.enable_partno=BB-SPI1-01 >> /boot/uEnv.txt

# Reset the BBB

reboot


