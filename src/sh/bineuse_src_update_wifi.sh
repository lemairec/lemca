#!/bin/bash
set -e

cd ~/bineuse_src
mkdir -p build
git pull
cd build
cmake ..
make -j4
