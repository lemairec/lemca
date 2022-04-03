#!/bin/bash
set -e

echo file $1

cp $1 ~/bineuse.tar.gz
rm -rf bineuse
tar -xzvf bineuse.tar.g

