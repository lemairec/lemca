#!/bin/bash
set -e

echo "carrier (good value 1) : "
cat /sys/class/net/enp1s0/carrier
echo "speed (good value 100) : "
cat /sys/class/net/enp1s0/speed
echo "duplex (good value full) : "
cat /sys/class/net/enp1s0/duplex
echo "errors :\n"
cat /sys/class/net/enp1s0/statistics/rx_crc_errors
cat /sys/class/net/enp1s0/statistics/rx_errors


