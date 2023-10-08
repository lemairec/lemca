#!/bin/bash
set -e
branch=$1;

echo "--- branche $branch\n"

[ ! -d ~/lemca_gps_src ] && git clone git@github.com:lemairec/lemca_gps.git ~/lemca_gps_src
cd ~/lemca_gps
git fetch origin
git reset --hard
git checkout origin/$branch

mkdir -p build
cd build
cmake ..
make -j4

rm -rf ~/lemca_gps
mkdir ~/lemca_gps

archive=~/lemca_gps
cp ~/lemca_gps_src/build/lemca_gps $archive
cp -r ~/lemca_gps_src/gui $archive
cp -r ~/lemca_gps_src/sound $archive

~/lemca_gps/lemca_gps --stats

