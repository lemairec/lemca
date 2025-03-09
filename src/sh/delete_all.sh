#!/bin/bash
set -e

echo  "**** clean 1"

rm -rf ~/lemca_data/agrigpspi
rm -rf ~/lemca_data/inrows

echo  "**** clean lemca"
rm -f ~/lemca_data/lemca/log_cmd.txt
rm -f ~/lemca_data/lemca/log.txt

echo  "**** clean bineuse"
rm -rf ~/lemca_data/bineuse/image_save_auto
rm -f ~/lemca_data/bineuse/log.txt

echo  "**** clean lemca_gps"
rm -rf ~/lemca_data/lemca_gps/autopaths
rm -f ~/lemca_data/lemca_gps/log.txt
