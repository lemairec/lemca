#!/bin/bash
set -e

cd ~/lemca_data/bineuse/image_save;
yourfilenames=`ls ./*.jpg`
for eachfile in $yourfilenames
do
    echo $eachfile --form myfile=@"$eachfile"
    curl --request POST "https://cloud.lemcavision.com/file/send" --form myfile=@"$eachfile"
done
                           

rm -rf ~/bineuse_src
