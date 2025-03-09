#!/bin/bash
set -e

echo  "**** clean 1"

rm -rf ~/agrigpspi
rm -rf ~/lemca_data/agrigpspi
rm -rf ~/lemca_data/inrows

echo  "**** clean lemca"
rm -f ~/lemca_data/lemca/log_cmd.txt
rm -f ~/lemca_data/lemca/log.txt

echo  "**** clean bineuse"
rm -rf ~/lemca_data/bineuse/image_save_auto
rm -f ~/lemca_data/bineuse/log.txt
rm -f ~/lemca_data/bineuse/log
rm -f ~/lemca_data/bineuse/image_save
rm -f ~/lemca_data/bineuse/plant

echo  "**** clean lemca_gps"
rm -rf ~/lemca_data/lemca_gps/autopaths
rm -rf ~/lemca_data/lemca_gps/job
rm -rf ~/lemca_data/lemca_gps/line
rm -rf ~/lemca_data/lemca_gps/parcelle
rm -f ~/lemca_data/lemca_gps/log.txt
rm -f ~/lemca_data/lemca_gps/tmp_cmd
