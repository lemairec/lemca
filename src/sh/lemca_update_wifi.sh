#!/bin/bash
set -e

cd ~/lemca
git pull
rm -rf build_new
rm -rf build_old
mkdir build_new
cd build_new
cmake ..
make -j4
cd ~/lemca
mv build build_old
mv build_new build
echo 5
sleep 1
echo 4
sleep 1
echo 3
sleep 1
echo 2
sleep 1
echo 1
sleep 1
/sbin/shutdown -h now
