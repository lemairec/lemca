#!/bin/bash
set -e

rm -rf ~/.ssh/known_hosts;
expect -c 'spawn ssh-copy-id -o StrictHostKeyChecking=no 5chmlLEM1cale26@remote.lemcavision.com ; expect "password:"; send "test\r"; interact'


apt-get install -y build-essential
apt-get install -y cmake 
apt-get install -y libqt5serialport5-dev
apt-get install -y libboost-iostreams-dev
apt-get install -y libboost-system-dev
apt-get install -y libopencv-dev
apt-get install -y wget
apt-get install -y curl
apt-get install -y vim
apt-get install -y qtmultimedia5-dev
apt-get install -y libqt5multimedia5-plugins
apt-get install -y nmap
apt-get install -y x11vnc
apt-get install -y expect
apt-get install -y unclutter
apt-get install -y onboard
