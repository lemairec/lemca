#!/bin/bash
if [ -e ~/.ssh/id_rsa ]
then
    echo "ok"
else
    echo "nok"
    ssh-keygen -f ~/.ssh/id_rsa -N ""
fi
