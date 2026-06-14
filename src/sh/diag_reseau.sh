#!/bin/bash
set -e

cat /sys/class/net/enp1s0/carrier
cat /sys/class/net/enp1s0/speed
cat /sys/class/net/enp1s0/duplex

cat /sys/class/net/enp1s0/statistics/rx_crc_errors
cat /sys/class/net/enp1s0/statistics/rx_errors


