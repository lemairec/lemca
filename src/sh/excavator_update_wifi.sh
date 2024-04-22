#!/bin/bash
set -e

[ ! -d ~/serie ] && git clone https://github.com/lemairec/excavator.git ~/serie
cd ~/excavator
mkdir -p build
git pull
cd build
cmake ..
make -j4
