#!/bin/bash


if [ $(id -u) != 0 ]; then
   echo "This script requires root permissions"
   sudo "$0" "$@"
   exit
fi

## This script enables spi chipselect 0 on bus 1

BASEDIR=$(dirname $0)

# Compile .dtbo for configuring pins
sudo apt-get purge device-tree-compiler
wget -c https://raw.githubusercontent.com/RobertCNelson/tools/master/pkgs/dtc.sh
chmod +x dtc.sh
./dtc.sh
dtc -O dtb -o ${BASEDIR}/BB-SPI0-01-00A0.dtbo -b 0 -@ ${BASEDIR}/BB-SPI0-01-00A0.dts 

cp ${BASEDIR}/BB-SPI0-01-00A0.dtbo /lib/firmware/


# Enable SPI0 on uEnv.txt
echo \#\#Enable SPI0 >> /boot/uEnv.txt
echo optargs=quiet drm.debug=7 >> /boot/uEnv.txt
echo cape_disable=bone_capemgr.disable_partno=BB-BONELT-HDMI,BB-BONELT-HDMIN
echo cape_enable=bone_capemgr.enable_partno=BB-SPI0-01
echo capemgr.disable_partno=BB-BONELT-HDMI,BB-BONELT-HDMIN >> /boot/uEnv.txt
echo capemgr.enable_partno=BB-SPI0-01 >> /boot/uEnv.txt

# Reset the BBB ?


#enable device tree overlay

echo BB-SPI0-01 > /sys/devices/bone_capemgr.*/slots

#should output spi devices
ls -lh /dev/spi* | grep --color spidev1.0

chmod a+x ${BASEDIR}/bootstrap.sh

# Absolute path to this script.
SCRIPT=$(readlink -f "$0")
# Absolute path this script is IN.
SCRIPTPATH=$(dirname "$SCRIPT")

echo "$SCRIPTPATH"

line="@reboot $SCRIPTPATH/bootstrap.sh"
(crontab -l; echo "$line" ) | crontab -


