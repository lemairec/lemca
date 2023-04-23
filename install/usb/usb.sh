#!/bin/bash
set -e

echo "usb"

/usr/sbin/usermod -a -G dialout lemca
/usr/sbin/usermod -a -G tty lemca
