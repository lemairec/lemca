
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

## veille

parametre=>gestionnaire d'allim

`````
systemctl mask sleep.target suspend.target hibernate.target hybrid-sleep.target
`````

plymouth-set-default-theme
GRUB_BACKGROUND=/home/lemca/deb10-master/logo.jpg


