#!/bin/bash

archive=~/bineuse_src/archive/bineuse

rm -rf ~/bineuse
rm -rf ~/bineuse_src
git clone git@github.com:lemairec/bineuse.git ~/bineuse_src
rm -rf $archive
rm -rf ~/bineuse_src/archive

mkdir -p ~/bineuse_src/build && cd ~/bineuse_src/build  &&  cmake .. && make -j 4

mkdir -p $archive

cp ~/bineuse_src/build/bineuse $archive
cp -r ~/bineuse_src/gui $archive
cp -r ~/bineuse_src/sound $archive

cd ~/bineuse_src/archive
tar -czvf bineuse.tar.gz bineuse


cd ~/;

curl --request POST 'https://maplaine.fr/lemca/send_file' --form 'myfile=@"./bineuse_src/archive/bineuse.tar.gz"'

rm -rf ~/bineuse_src
