#!/bin/bash
set -e
[ ! -d ~/inrows ] && git clone git@github.com:lemairec/inrows.git ~/inrows

cd ~/inrows
mkdir -p build
git pull
cd build
cmake ..
make -j4
