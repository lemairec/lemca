#!/usr/bin/expect -f
echo lemca | su -c "sed -i 's|deb.debian.org|archive.debian.org|g' /etc/apt/sources.list"
echo lemca | su -c "sed -i 's|security.debian.org|archive.debian.org|g' /etc/apt/sources.list"
echo lemca | su -c "apt update"
echo lemca | su -c "apt-get install sshpass"
sshpass -p "test" ssh-copy-id -o StrictHostKeyChecking=no 5chmlLEM1cale26@remote.lemcavision.com
