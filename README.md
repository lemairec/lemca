# install debian - xcfe

## 1. image

=> 10 amd64 (multiarch pour n702)

=> current => https://cdimage.debian.org/cdimage/unofficial/non-free/cd-including-firmware/archive/10.13.0-live+nonfree/amd64/iso-hybrid/
=> https://cdimage.debian.org/cdimage/unofficial/non-free/cd-including-firmware/11.3.0+nonfree/amd64/iso-dvd/

=> balenaetcher => faire le boot

=> del to boot

## 2. automatisation

`````
su

vi /etc/apt/sources.list
#remove dvd
apt-get update

apt-get install git
----

git clone https://github.com/lemairec/lemca.git
cd lemca;
sh first.sh
`````

### 2.1. autologin (automatique)

`````
/etc/lightdm/lightdm.conf
[Seat:*]
autologin-user=$USER
autologin-user-timeout=0
`````

### 2.2. lancement de lemca (automatique)

`````
`````

## 3. droit usb

`````
/usr/sbin/usermod
usermod -a -G dialout Nom_Utilisateur
usermod -a -G tty Nom_Utilisateur
`````


## 4. grub


`````
su  
cd deb10-master
make install

export $PATH=$PATH:/sbin/
plymouth-set-default-theme -R deb10


vi /etc/default/grub
GRUB_TIMEOUT=0
GRUB_DISTRIBUTOR="Lemca 22.09.11"
GRUB_CMDLINE_LINUX_DEFAULT="quiet splash"
GRUB_BACKGROUND="/home/lemca/lemca/deb10-master/logo.png"

update-grub2
reboot

(problem logo
 => convert logo.png -depth 8 logo.png
 => imagemagick)
`````

# 5. xcfe

## 5.1 alimentation

`````
=> bouton alimentation => eteindre
=> gestion de l'alimentation (never never never off)
`````

## 5.2 montage usb auto


## 5.3 unclutter

`````
su
vi /etc/default/unclutter
EXTRA_OPTS="-idle 0.01 -root"
`````

# OS X

sudo xcodebuild -license
sudo xcode-select --reset

#easy_install pip
#pip3 install image

brew install pip
brew install tcl-tk
brew install python-tk

# linux


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

## USB
`````
lsusb
`````

firmware-misc-nonfree


## clavier

onboard
(old florence)

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

## guacamole

x11vnc -ssh root@139.162.182.189:5901 -forever

https://www.linode.com/docs/guides/installing-apache-guacamole-on-ubuntu-and-debian/
ssh -o StrictHostKeyChecking=no 5chmlLEM1cale26@51.38.190.75

``````
sudo apt-get update
sudo apt install build-essential libcairo2-dev libjpeg62-turbo-dev \
    libpng-dev libtool-bin libossp-uuid-dev libvncserver-dev \
    freerdp2-dev libssh2-1-dev libtelnet-dev libwebsockets-dev \
    libpulse-dev libvorbis-dev libwebp-dev libssl-dev \
    libpango1.0-dev libswscale-dev libavcodec-dev libavutil-dev \
    libavformat-dev
``````


sudo /sbin/iptables -t nat -I PREROUTING -p tcp --dport 80 -j REDIRECT --to-port 8080

rm ~/.ssh/known_hosts; echo 4bspC3JXwgTm | ssh-copy-id  -o StrictHostKeyChecking=no debian@remote.lemcavision.com

expect -c 'spawn ssh-copy-id -o StrictHostKeyChecking=no 5chmlLEM1cale26@remote.lemcavision.com ; expect "password:"; send "test\r"; interact'



## wifi

Attention dns

`````
nano /etc/resolv.conf

nameserver 8.8.8.8
`````

## xfce

terminal => ctrl+alt+f3

### panel

..config/xfce4/xfconf/xfce-perchannel-xml/

## point hadrien

Settings Manager -> Session and Startup
Disable "Automatically save session on logout"

## robert

serveur et client guacamol
linode

vpn
connection wifi/ ethernet => map
