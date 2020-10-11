#!/usr/bin/env python

import sys, optparse, subprocess, os, os.path, errno, zipfile, string, json, platform, shutil, tarfile, tempfile, multiprocessing
from subprocess import Popen, PIPE
import argparse
import sys
import PIL.Image
import PIL.ImageTk

from config import Config;

config=Config()

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
    call("cd ~/agrigpspi; git reset --hard; git pull")

def teamviewer():
    call("teamviewer")

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

def my_exit():
    exit()

window = Tk()
window.title("Lemca app")
window.geometry('1400x800')

size = 150
y1 = 0.8

size2 = 80
y2 = 0.6

#btn = Button(window, text="GPS", command=clicked_gps, height = 5, width = 20)
#btn.grid(column=0, row=0)

#btn = Button(window, text="update GPS", command=install_gps, height = 5, width = 20)
#btn.grid(column=0, row=1)

#btn = Button(window, text="clean GPS", command=nettoyage_gps, height = 5, width = 20)
#btn.grid(column=0, row=2)

#btn = Button(window, text="Bineuse", command=clicked_bineuse, height = 5, width = 20)
#btn.grid(column=1, row=0)


img = PIL.Image.open("lemca/gui/logo.png")
img = img.resize((400, 400))
img = PIL.ImageTk.PhotoImage(img)



btn = Button(window, image=img, relief=FLAT, highlightthickness=0, bd=0)
btn.place(relx = 0.5, rely = 0.3, anchor = 'center')



image1 = PIL.Image.open("lemca/gui/bineuse.png")
image1 = image1.resize((size, size))
image1 = PIL.ImageTk.PhotoImage(image1)

btn = Button(window, image=image1, command=clicked_bineuse, relief=FLAT, highlightthickness=0, bd=0)
btn.place(relx = 0.2, rely = y1, anchor = 'center')

image2 = PIL.Image.open("lemca/gui/refresh.png")
image2 = image2.resize((size, size))
image2 = PIL.ImageTk.PhotoImage(image2)

btn = Button(window, image=image2, command=install_bineuse, relief=FLAT, highlightthickness=0, bd=0)
btn.place(relx = 0.4, rely = y1, anchor = 'center')

image3 = PIL.Image.open("lemca/gui/reseau.png")
image3 = image3.resize((size, size))
image3 = PIL.ImageTk.PhotoImage(image3)

btn = Button(window, image=image3, command=teamviewer, relief=FLAT, highlightthickness=0, bd=0)
btn.place(relx = 0.6, rely = y1, anchor = 'center')

image4 = PIL.Image.open("lemca/gui/off.png")
image4 = image4.resize((size, size))
image4 = PIL.ImageTk.PhotoImage(image4)

btn = Button(window, image=image4, command=my_exit, relief=FLAT, highlightthickness=0, bd=0)
btn.place(relx = 0.8, rely = y1, anchor = 'center')


if config.gps : 
    image5 = PIL.Image.open("lemca/gui/gps.png")
    image5 = image5.resize((size2, size2))
    image5 = PIL.ImageTk.PhotoImage(image5)

    btn = Button(window, image=image5, command=clicked_gps, relief=FLAT, highlightthickness=0, bd=0)
    btn.place(relx = 0.2, rely = y2, anchor = 'center')

    image6 = PIL.Image.open("lemca/gui/refresh.png")
    image6 = image6.resize((size2, size2))
    image6 = PIL.ImageTk.PhotoImage(image6)

    btn = Button(window, image=image6, command=install_gps, relief=FLAT, highlightthickness=0, bd=0)
    btn.place(relx = 0.4, rely = y2, anchor = 'center')

    image9 = PIL.Image.open("lemca/gui/refresh.png")
    image9 = image9.resize((size2, size2))
    image9 = PIL.ImageTk.PhotoImage(image9)

    btn = Button(window, image=image9, command=update_setup, relief=FLAT, highlightthickness=0, bd=0)
    btn.place(relx = 0.2, rely = 0.2, anchor = 'center')

else:
    window.attributes('-zoomed', True)  
    window.attributes('-fullscreen', True)  
    clicked_bineuse()


print("lemca")

window.mainloop()
