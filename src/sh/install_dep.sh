#!/bin/bash
set -e

apt-get update
apt-get install -y build-essential
apt-get install -y cmake 
apt-get install -y libqt5serialport5-dev
apt-get install -y libboost-iostreams-dev
apt-get install -y libboost-system-dev
apt-get install -y libopencv-dev
apt-get install -y wget
apt-get install -y curl
apt-get install -y vim
apt-get install -y florence
apt-get install -y qtmultimedia5-dev
apt-get install -y libqt5multimedia5-plugins
apt-get install -y nmap
