#!/bin/bash
set -e

[ ! -d ~/bineuse_src ] && git clone git@github.com:lemairec/bineuse.git ~/bineuse_src
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

mkdir -p $archive/images
cp -r ~/bineuse_src/images/colza.jpg $archive/images/colza.jpg
cp -r ~/bineuse_src/images/ble.jpg $archive/images/ble.jpg
cp -r ~/bineuse_src/images/mais.jpg $archive/images/mais.jpg
cp -r ~/bineuse_src/images/betterave_sale.jpg $archive/images/betterave_sale.jpg
cp -r ~/bineuse_src/images/quinoa_sale.jpg $archive/images/quinoa_sale.jpg
