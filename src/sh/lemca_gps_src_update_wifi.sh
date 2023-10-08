#!/bin/bash
set -e

[ ! -d ~/lemca_gps_src ] && git clone https://github.com/lemairec/lemca_gps.git ~/lemca_gps_src
cd ~/agrigpspi
mkdir -p build
git pull
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

