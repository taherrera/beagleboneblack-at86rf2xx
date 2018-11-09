#!/bin/bash

if [ $(id -u) != 0 ]; then
   echo "This script requires root permissions"
   sudo "$0" "$@"
   exit
fi

# Absolute path to this script.
SCRIPT=$(readlink -f "$0")
# Absolute path this script is IN.
SCRIPTPATH=$(dirname "$SCRIPT")

echo "$SCRIPTPATH"

line="@reboot $SCRIPTPATH/bootstrap.sh"
(crontab -l; echo "$line" ) | crontab -

