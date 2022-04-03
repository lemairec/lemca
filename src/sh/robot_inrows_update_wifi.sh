#!/bin/bash
set -e

cd ~/inrows
mkdir -p build
git pull
cd build
cmake ..
make -j4
