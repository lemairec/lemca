#!/usr/bin/expect -f

spawn ssh-copy-id -o StrictHostKeyChecking=no 5chmlLEM1cale26@remote.lemcavision.com
expect "password:" { send "test\n" }

spawn ssh 5chmlLEM1cale26@remote.lemcavision.com "sh new_connection.sh"
expect "password:" { send "test\n" }
