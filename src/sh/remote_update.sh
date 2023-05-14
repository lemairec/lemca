#!/usr/bin/expect -f
spawn ssh-copy-id -o StrictHostKeyChecking=no 5chmlLEM1cale26@remote.lemcavision.com
expect "password:"
send "test\n"
expect eof
