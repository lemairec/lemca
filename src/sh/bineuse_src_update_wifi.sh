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
