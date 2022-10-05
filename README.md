# install debian - xcfe

## 1. image

=> 10 amd64 (multiarch pour n702)

=> current => https://cdimage.debian.org/cdimage/unofficial/non-free/cd-including-firmware/archive/10.13.0-live+nonfree/amd64/iso-hybrid/


=> next => https://cdimage.debian.org/cdimage/unofficial/non-free/cd-including-firmware/11.3.0+nonfree/amd64/iso-dvd/

=> balenaetcher => faire le boot (ou rufus)

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
.config/autostart
`````

### 2.3. droit usb (automatique)

`````
su
/usr/sbin/usermod
usermod -a -G dialout Nom_Utilisateur
usermod -a -G tty Nom_Utilisateur
`````


## 3. grub


`````
su  
cd deb10-master
make install

export PATH=$PATH:/sbin/
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

# 4. xcfe

## 4.1 alimentation

`````
=> gestionnaire d'alimentation
=> bouton alimentation => eteindre
=> gestion de l'alimentation (never never never off)
`````

## 4.2 montage usb auto

`````
disque et media amovible
monter/monter
`````


## 4.3 unclutter

`````
su
vi /etc/default/unclutter
EXTRA_OPTS="-idle 0.01 -root"
`````

## 4.4 reseau

tout supprimer
parametre ipv4
manuel
192.168.1.1 24
Serveur dns 8.8.8.8

# OS X

sudo xcodebuild -license
sudo xcode-select --reset

#easy_install pip
#pip3 install image

brew install pip
brew install tcl-tk
brew install python-tk

# linux


nmcli dev wifi
               connect lemaire pzssword toto

x11vnc -ssh root@139.162.182.189:5901 -forever



//imu
http://ave.dee.isep.ipp.pt/~lbf/PINSFUSION/CaDuPoVa06.pdf

https://github.com/chennuo0125-HIT/imu_gps_fusion/blob/main/include/imu_gps_fusion.h

export PATH=$PATH:/usr/sbin

## USB
`````
lsusb
`````


## clavier

onboard
(old florence)

## run cmd

``````
echo <password> | sudo -S <command>
``````

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

# clonezilla

## 1. image

download image 

=> balenaetcher => faire le boot (ou rufus)

=> del to boot


## 2. cloner

`````
clonezilla live vga 800x600
start_clonezilla
device-image
local_dev
savedisk
z1p
`````

## 3. restaurer

`````
clonezilla live vga 800x600
start_clonezilla
device-image
local_dev
restoredisk
`````

# nouveau panel

## licence

## camera

Video
=> resolution 1024
=> h 265
=> frzme rate 25
=> quality //40
=> bitrate 4096
=> cbr
=> 50

Video mode
PAL/50hz

Day/Night
CDS
disable led

OSD
disable all

Zone
rien

image adustemet
50 partout

white balance
auto-outdoor

wdr
disable

dnr
3d / dynammic / 50

deflog
disable



## idee

https://stackoverflow.com/questions/65848953/how-to-create-an-automated-and-unattended-clonezilla-restore-solutions

gnome-disk-utility
gnome-disk