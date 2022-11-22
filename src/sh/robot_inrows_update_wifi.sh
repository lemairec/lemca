#!/bin/bash
set -e
[ ! -d ~/inrows ] && git clone https://github.com/lemairec/inrows.git ~/inrows

cd ~/inrows
mkdir -p build
git pull
cd build
cmake ..
make -j4
