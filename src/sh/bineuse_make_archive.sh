#!/bin/bash

archive=~/bineuse_src/archive/bineuse

branch=$1;
echo "--- branche $branch\n"

rm -rf ~/bineuse
rm -rf ~/bineuse_src
git clone git@github.com:lemairec/bineuse.git ~/bineuse_src

cd ~/bineuse_src
git checkout origin/$branch

rm -rf $archive
rm -rf ~/bineuse_src/archive

mkdir -p ~/bineuse_src/build && cd ~/bineuse_src/build  &&  cmake .. && make -j 4

mkdir -p $archive

cp ~/bineuse_src/build/bineuse $archive
cp -r ~/bineuse_src/gui $archive
cp -r ~/bineuse_src/sound $archive

mkdir -p $archive/images
cp -r ~/bineuse_src/images/colza.jpg $archive/images/colza.jpg
cp -r ~/bineuse_src/images/ble.jpg $archive/images/ble.jpg
cp -r ~/bineuse_src/images/mais.jpg $archive/images/mais.jpg
cp -r ~/bineuse_src/images/betterave_sale.jpg $archive/images/betterave_sale.jpg
cp -r ~/bineuse_src/images/quinoa_sale.jpg $archive/images/quinoa_sale.jpg

head=$(git rev-parse HEAD)
version=$(~/bineuse_src/build/bineuse --version)
echo $version > $archive/version.txt
echo $branch >> $archive/version.txt
git rev-parse HEAD >> $archive/version.txt


cd ~/bineuse_src/archive
tar -czvf bineuse.tar.gz bineuse
cd ~/;
curl --request POST "https://cloud.lemcavision.com/binary/send_bineuse?branch=$branch&head=$head&version=$version" --form 'myfile=@"./bineuse_src/archive/bineuse.tar.gz"'

rm -rf ~/bineuse_src
