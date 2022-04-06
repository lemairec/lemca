#!/bin/bash
set -e

rm -rf ~/bineuse.tar.gz
wget -c https://maplaine.fr/lemca/bineuse.tar.gz ~/bineuse.tar.gz
rm -rf bineuse
tar -xzvf bineuse.tar.g

