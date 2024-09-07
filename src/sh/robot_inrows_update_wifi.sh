#!/bin/bash
set -e
[ ! -d ~/robot ] && git clone git@github.com:lemairec/robot.git ~/robot

cd ~/robot
mkdir -p build
git pull
cd build
cmake ..
make -j4
