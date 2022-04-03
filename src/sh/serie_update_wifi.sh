#!/bin/bash
set -e

[ ! -d ~/serie ] && git clone https://github.com/lemairec/serie.git ~/serie
cd ~/serie
mkdir -p build
git pull
cd build
cmake ..
make -j4
