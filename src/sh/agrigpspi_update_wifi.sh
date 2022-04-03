#!/bin/bash
set -e

[ ! -d ~/agrigpspi ] && git clone https://github.com/lemairec/agrigpspi.git ~/agrigpspi
cd ~/agrigpspi
mkdir -p build
git pull
cd build
cmake ..
make -j4
