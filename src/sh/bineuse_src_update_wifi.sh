#!/bin/bash
set -e
branch=$1;

echo "--- branche $branch\n"

[ ! -d ~/bineuse_src ] && git clone git@github.com:lemairec/bineuse.git ~/bineuse_src

cd ~/bineuse_src

git fetch origin
git reset --hard
git checkout origin/$branch

mkdir -p build
cd build
cmake ..
make -j4

rm -rf ~/bineuse
mkdir ~/bineuse

archive=~/bineuse
cp ~/bineuse_src/build/bineuse $archive
cp -r ~/bineuse_src/gui $archive
cp -r ~/bineuse_src/sound $archive

mkdir -p $archive/images
cp -r ~/bineuse_src/images/colza.jpg $archive/images/colza.jpg
cp -r ~/bineuse_src/images/ble.jpg $archive/images/ble.jpg
cp -r ~/bineuse_src/images/mais.jpg $archive/images/mais.jpg
cp -r ~/bineuse_src/images/betterave_sale.jpg $archive/images/betterave_sale.jpg
cp -r ~/bineuse_src/images/quinoa_sale.jpg $archive/images/quinoa_sale.jpg

mkdir -p $archive/images
