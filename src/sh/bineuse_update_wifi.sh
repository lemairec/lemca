#!/bin/bash
set -e
branch=$1;
echo "--- branche $branch\n"

rm -rf ~/bineuse.tar.gz
echo  "**** telechargement"
wget -c https://maplaine.fr/lemca/bineuse_$branch.tar.gz -O ~/bineuse.tar.gz

echo  "**** telechargement ok"
rm -rf bineuse
tar -xzvf bineuse.tar.gz

