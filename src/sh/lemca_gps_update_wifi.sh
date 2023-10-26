#!/bin/bash
set -e
branch=$1;
constructeur=$2;
panel=$3;
echo "--- branche $branch\n"
echo "--- constructeur $constructeur\n"
echo "--- panel $panel\n"

rm -rf ~/lemca_gps.tar.gz
echo  "**** telechargement"
echo "https://cloud.lemcavision.com/binary/lemca_gps?branch=$branch&constructeur=$constructeur&panel=$panel\n"

wget -c https://cloud.lemcavision.com/binary/lemca_gps?branch=$branch\&constructeur=$constructeur\&panel=$panel -O ~/lemca_gps.tar.gz

echo  "**** telechargement ok"
rm -rf lemca_gps
tar -xzvf lemca_gps.tar.gz

