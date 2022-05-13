#!/bin/bash
set -e

rm -rf ~/bineuse.tar.gz
echo  "**** telechargement"
wget -c https://maplaine.fr/lemca/bineuse.tar.gz -O ~/bineuse.tar.gz

echo  "**** telechargement ok"
rm -rf bineuse
tar -xzvf bineuse.tar.gz

