#!/bin/bash
set -e

echo file $1

cp $1 ~/lemca.zip

echo "#### REMOVE OLD";
rm -rf lemca
echo "#### UNZIP";
unzip lemca.zip

echo "#### MAKE BUILD";
rm -rf ~/lemca/build
mkdir ~/lemca/build
echo "#### COMPIL";
cd ~/lemca/build && cmake .. && make

