#!/bin/bash
set -e

echo "1. install deps";
echo lemca | su -c "sh /home/lemca/lemca/src/sh/install_dep.sh"



echo "2. make/cmake";
mkdir -p /home/lemca/lemca/build;
cd /home/lemca/lemca/build; cmake ..; make -j4;

echo "3. autologin"
echo lemca | su -c "sh /home/lemca/lemca/install/autologin/install_su.sh"

echo "4. autostart"
sh /home/lemca/lemca/install/autostart/install.sh

