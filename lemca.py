#!/usr/bin/env python

import sys, optparse, subprocess, urllib2, os, os.path, errno, zipfile, string, json, platform, shutil, tarfile, urlparse, tempfile, multiprocessing
from subprocess import Popen, PIPE
import argparse
import sys

try:
    # for Python2
    from Tkinter import * ## notice capitalized T in Tkinter 
except ImportError:
    # for Python3
    from tkinter  import *

PATH = os.getcwd()

def call_without_print(cmdline):
    ret = subprocess.call(cmdline, shell=True)
    if ret != 0:
        print(sys.stderr, 'Running: ' + cmdline + ' failed with exit code ' + str(ret) + '!')
    return ret

def call(cmdline):
    print('Running: ' + cmdline)
    call_without_print(cmdline)


def clicked_gps():
    call("~/agrigpspi/agrigpspi.py run")

def install_gps():
    print(PATH + "/agrigpspi")
    if os.path.exists(PATH + "/agrigpspi"):
        call("cd ~/agrigpspi; git reset --hard; git pull")
    else:
        call("git clone https://github.com/lemairec/agrigpspi.git ~/agrigpspi; ~/agrigpspi/agrigpspi.py install")

def nettoyage_gps():
    call("rm -rf ~/agrigpspi/build; mkdir ~/agrigpspi/build")

def update_setup():
   call("cd ~/lemca; git pull;")
   exit();

def clicked_bineuse():
    call(" mkdir -p ~/bineuse/build; ~/bineuse/bineuse.py run")

def install_bineuse():
    print(PATH + "/bineuse")
    if os.path.exists(PATH + "/bineuse"):
        call("cd ~/bineuse; git reset --hard; git pull")
    else:
        call("git clone git@github.com:lemairec/bineuse.git ~/bineuse; ~/bineuse/bineuse.py install")

def nettoyage_bineuse():
    call("rm -rf ~/bineuse/build; mkdir ~/bineuse/build")

def clicked_master():
    call("cd ~/bineuse; git checkout master; rm -rf ~/bineuse/build;")

def clicked_dev():
    call("cd ~/bineuse; git checkout dev; rm -rf ~/bineuse/build;")
   
window = Tk()
window.title("Lemca app")
window.geometry('800x600')


btn = Button(window, text="GPS", command=clicked_gps, height = 5, width = 20)
btn.grid(column=0, row=0)

btn = Button(window, text="update GPS", command=install_gps, height = 5, width = 20)
btn.grid(column=0, row=1)

btn = Button(window, text="clean GPS", command=nettoyage_gps, height = 5, width = 20)
btn.grid(column=0, row=2)

btn = Button(window, text="Bineuse", command=clicked_bineuse, height = 5, width = 20)
btn.grid(column=1, row=0)

btn = Button(window, text="update Bineuse", command=install_bineuse, height = 5, width = 20)
btn.grid(column=1, row=1)

btn = Button(window, text="clean Bineuse", command=nettoyage_bineuse, height = 5, width = 20)
btn.grid(column=1, row=2)

btn = Button(window, text="checkout Master", command=clicked_master, height = 5, width = 20)
btn.grid(column=1, row=3)


btn = Button(window, text="checkout Dev", command=clicked_dev, height = 5, width = 20)
btn.grid(column=1, row=4)




btn = Button(window, text="update lemca", command=update_setup)
btn.grid(column=3, row=5)


window.mainloop()
