#!/bin/bash
set -e
branch=$1;
constructeur=$2;
panel=$3;
echo "--- branche $branch\n"
echo "--- constructeur $constructeur\n"
echo "--- panel $panel\n"

rm -rf ~/bineuse.tar.gz
echo  "**** telechargement"
echo "https://cloud.lemcavision.com/binary/bineuse?branch=$branch&constructeur=$constructeur&panel=$panel\n"

wget -c https://cloud.lemcavision.com/binary/bineuse?branch=$branch&constructeur=$constructeur&panel=$panel -o ~/bineuse.tar.gz

echo  "**** telechargement ok"
rm -rf bineuse
tar -xzvf bineuse.tar.gz

