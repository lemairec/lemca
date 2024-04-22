#!/bin/bash
set -e

[ ! -d ~/lemca_excavator ] && git clone git@github.com:lemairec/lemca_excavator.git ~/lemca_excavator
cd ~/lemca_excavator
mkdir -p build
git pull
cd build
cmake ..
make -j4
