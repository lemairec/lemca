#!/bin/bash
set -e

echo "usb"

/usr/sbin/usermod -a -G dialout Nom_Utilisateur
/usr/sbin/usermod -a -G tty Nom_Utilisateur
