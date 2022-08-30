#!/bin/bash
set -e

cd ~/bineuse_src
mkdir -p build
git reset --hard
git pull
cd build
cmake ..
make -j4

rm -rf ~/bineuse
mkdir ~/bineuse
cp ~/bineuse_src/build/bineuse ~/bineuse
cp -r ~/bineuse_src/gui ~/bineuse
cp -r ~/bineuse_src/sound ~/bineuse
cp -r ~/bineuse_src/images ~/bineuse
