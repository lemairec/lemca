
## USB
`````
lsusb
`````

firmware-misc-nonfree

## OS X

sudo xcodebuild -license
sudo xcode-select --reset

#easy_install pip
#pip3 install image

brew install pip
brew install tcl-tk
brew install python-tk

# linux

sudo apt-get install python-imaging-tk


`````
apt-get install wireless-tools
# pas sur apt-get update && apt-get install wpasupplicant wireless-tools 

sudo apt-get install libsdl2-image-dev
#pip3 install kivy
#pip3 install pillow
`````

nmcli dev wifi
               connect lemaire pzssword toto

x11vnc -ssh root@139.162.182.189:5901 -forever


#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

14pin Tyco Ampseal


//imu
http://ave.dee.isep.ipp.pt/~lbf/PINSFUSION/CaDuPoVa06.pdf

https://github.com/chennuo0125-HIT/imu_gps_fusion/blob/main/include/imu_gps_fusion.h

export PATH=$PATH:/usr/sbin


## autologin

`````
/etc/lightdm/lightdm.conf
[Seat:*]
autologin-user=$USER
autologin-user-timeout=0
`````

## clavier

florence

## run cmd

``````
echo <password> | sudo -S <command>
``````

## veille

parametre=>gestionnaire d'allim

`````
systemctl mask sleep.target suspend.target hibernate.target hybrid-sleep.target
`````

plymouth-set-default-theme
GRUB_BACKGROUND=/home/lemca/deb10-master/logo.jpg


## reseau

``````
nmap 192.168.1.0/24
ping -b 192.168.1.255
/sbin/arp -a
``````

## robert

serveur et client guacamol
linode

vpn
connection wifi/ ethernet => map


## guacamole

x11vnc -ssh root@139.162.182.189:5901 -forever

https://www.linode.com/docs/guides/installing-apache-guacamole-on-ubuntu-and-debian/

sudo /sbin/iptables -t nat -I PREROUTING -p tcp --dport 80 -j REDIRECT --to-port 8080

ssh-copy-id remote@remote.lemcavision.com

## debian
=> 11 amd64 (multiarch pour n702)
=> https://cdimage.debian.org/cdimage/unofficial/non-free/cd-including-firmware/11.3.0+nonfree/amd64/iso-dvd/
=> del to boot
=> nano /etc/default/grub
    GRUB_CMDLINE_LINUX_DEFAULT="quiet splash pci=noaer"
    sudo update-grub
    reboot
=> balenaetcher => faire le boot

# droit usb

`````
/usr/sbin/usermod
usermod -a -G dialout Nom_Utilisateur
usermod -a -G tty Nom_Utilisateur
`````


## point hadrien

- guacamole
    => 
- debian (i386 amd64) 
   
- guillaume debar
- yocto project / buildroot

sudo apt install build-essential libcairo2-dev libjpeg62-turbo-dev \
    libpng-dev libtool-bin libossp-uuid-dev libvncserver-dev \
    freerdp2-dev libssh2-1-dev libtelnet-dev libwebsockets-dev \
    libpulse-dev libvorbis-dev libwebp-dev libssl-dev \
    libpango1.0-dev libswscale-dev libavcodec-dev libavutil-dev \
    libavformat-dev