#!/usr/bin/expect -f
echo lemca | su -c "apt-get install sshpass"
sshpass -p "PASSWORD" ssh-copy-id -o StrictHostKeyChecking=no 5chmlLEM1cale26@remote.lemcavision.com
