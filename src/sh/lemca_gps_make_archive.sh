#!/bin/bash

archive=~/lemca_gps_src/archive/bineuse

branch=$1;
echo "--- branche $branch\n"

rm -rf ~/lemca_gps
rm -rf ~/lemca_gps_src
git clone git@github.com:lemairec/lemca_gps.git ~/lemca_gps_src

cd ~/lemca_gps_src
git checkout origin/$branch

rm -rf $archive
rm -rf ~/lemca_gps_src/archive

mkdir -p ~/lemca_gps_src/build && cd ~/lemca_gps_src/build  &&  cmake .. && make -j 4

mkdir -p $archive

cp ~/lemca_gps_src/build/lemca $archive
cp -r ~/lemca_gps_src/gui $archive
cp -r ~/lemca_gps_src/sound $archive

head=$(git rev-parse HEAD)
version=$(~/lemca_gps_src/build/lemca_gps --version)
echo $version > $archive/version.txt
echo $branch >> $archive/version.txt
git rev-parse HEAD >> $archive/version.txt


cd ~/lemca_gps_src/archive
tar -czvf lemca_gps.tar.gz lemca_gps
cd ~/;
curl --request POST "https://cloud.lemcavision.com/binary/send_lemca_gps?branch=$branch&head=$head&version=$version" --form 'myfile=@"./bineuse_src/archive/bineuse.tar.gz"'

rm -rf ~/lemca_gps_src
