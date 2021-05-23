#!/usr/bin/env python

import sys, optparse, subprocess, os, os.path, errno, zipfile, string, json, platform, shutil, tarfile, tempfile, multiprocessing
from subprocess import Popen, PIPE
import argparse
import sys
import PIL.Image
import PIL.ImageTk
import requests
import json


import configparser, os

config = configparser.ConfigParser()
config.readfp(open('lemca/lemca.cfg.example'))
config.read(['lemca/lemca.cfg'])

cfg_advanced=config.getboolean('lemca', 'advanced')
user_email=config.get('lemca', 'user_email')
cfg_bineuse_code_source=config.getboolean('lemca', 'bineuse_code_source')

print("config------")
print("advanced          "+str(cfg_advanced))
print("user_email   "+str(user_email))
print("code source          "+str(cfg_bineuse_code_source))

try:
    # for Python2
    from Tkinter import * ## notice capitalized T in Tkinter 
except ImportError:
    # for Python3
    from tkinter  import *

PATH = os.getcwd()


class LemcaGui:
    def call_without_print(self, cmdline):
        ret = subprocess.call(cmdline, shell=True)
        if ret != 0:
            print(sys.stderr, 'Running: ' + cmdline + ' failed with exit code ' + str(ret) + '!')
        return ret

    def call(self, cmdline):
        print('Running: ' + cmdline)
        self.call_without_print(cmdline)

    def gps_prod(self):
        self.call("cd ~/agrigpspi; git reset --hard; git pull")

    def clicked_gps(self):
        self.call("~/agrigpspi/agrigpspi.py run")

    def install_gps(self):
        self.call("cd ~/agrigpspi; git reset --hard; git pull; rm -rf ~/agrigpspi")

    def teamviewer(self):
        self.call("teamviewer &")

    def update_setup(self):
        self.call("cd ~/lemca; git pull;")
        exit()

    def clicked_bineuse(self):
        if(self.bineuse_code_source):
            self.call("mkdir -p ~/bineuse_src/build; ~/bineuse_src/bineuse.py run")
        else:
            self.call("~/bineuse/bineuse")
        

    def install_bineuse(self):
        if(self.bineuse_code_source):
            self.call("cd ~/bineuse_src; git reset --hard; git pull")
        else:
            self.call("rm -rf ~/bineuse.tar.gz && wget -c https://maplaine.fr/lemca/bineuse.tar.gz && rm -rf bineuse && tar -xzvf bineuse.tar.gz")

    def wifi(self):
        self.call("nm-connection-editor & onboard &")

    def my_exit(self):
        self.call("/sbin/shutdown -h now")

    def my_exit2(self):
        exit() 
        

    def save_gps(self):
        my_dir = "agrigpspi/build/job/"
        url = "https://maplaine.fr/api/job_gps"
        
        #my_dir = "agrigpspi/build/job/"
        #url = "http://localhost:4000/api/job_gps"
        
        dirs = os.listdir(my_dir)

        for file_info in dirs:
            if(file_info.endswith(".info")):
                file_info = my_dir+file_info
                file_job = file_info.replace(".info", ".job")
                file_debug = file_info.replace(".info", ".debug")
                print(file_info)
                print(file_job)
                print(file_debug)

                
                ok_text = ""
                debug = ""
                with open(file_debug) as f:
                    debug = f.read()

                with open(file_info) as f:
                    read_data = f.read()
                    mydata = json.loads(read_data)
                    with open(file_job) as f_job:
                        mydata_job = f_job.read()

                        mydata["job"]=mydata_job
                        mydata["debug"]=debug
                        mydata["user_email"]=user_email
                        print(mydata)

                        r=requests.post(url,data=mydata)
                        
                        ok_text = r.text

                if(ok_text == "\"ok\""):
                    os.remove(file_info)
                    os.remove(file_job)
                    os.remove(file_debug)
                else:
                    print("not_ok")
                    print(ok_text)

    def logo(self):
        self.logo_i += 1
        if(self.logo_i>5):
            self.add_advanced_buttons()

    def add_advanced_buttons(self):
        size2 = 80
        y2 = 0.6
        if self.advanced:
            print("advanced2")
            self.advanced = True
            self.image5 = PIL.Image.open("lemca/gui/gps.png")
            self.image5 = self.image5.resize((size2, size2))
            self.image5 = PIL.ImageTk.PhotoImage(self.image5)

            btn = Button(window, image=self.image5, command=self.clicked_gps, relief=FLAT, highlightthickness=0, bd=0)
            btn.place(relx = 0.2, rely = y2, anchor = 'center')

            self.image6 = PIL.Image.open("lemca/gui/refresh.png")
            self.image6 = self.image6.resize((size2, size2))
            self.image6 = PIL.ImageTk.PhotoImage(self.image6)

            btn = Button(window, image=self.image6, command=self.install_gps, relief=FLAT, highlightthickness=0, bd=0)
            btn.place(relx = 0.4, rely = y2, anchor = 'center')

            self.image7 = PIL.Image.open("lemca/gui/save.png")
            self.image7 = self.image7.resize((size2, size2))
            self.image7 = PIL.ImageTk.PhotoImage(self.image7)

            btn = Button(window, image=self.image7, command=self.save_gps, relief=FLAT, highlightthickness=0, bd=0)
            btn.place(relx = 0.6, rely = y2, anchor = 'center')


            self.image9 = PIL.Image.open("lemca/gui/refresh.png")
            self.image9 = self.image9.resize((size2, size2))
            self.image9 = PIL.ImageTk.PhotoImage(self.image9)

            btn = Button(window, image=self.image9, command=self.update_setup, relief=FLAT, highlightthickness=0, bd=0)
            btn.place(relx = 0.2, rely = 0.2, anchor = 'center')
            
        window.attributes('-fullscreen', False)  


    def run(self):
        
        size = 150
        y1 = 0.8

        self.logo_i = 0
        self.bineuse_code_source = cfg_bineuse_code_source
        self.advanced = cfg_advanced

        print("--config------")
        if(self.advanced):
            print("-----advanced")
        if(self.bineuse_code_source):
            print("-----bineuse_code_source")


        self.img = PIL.Image.open("lemca/gui/logo.png")
        self.img = self.img.resize((400, 400))
        self.img = PIL.ImageTk.PhotoImage(self.img)



        btn = Button(window, image=self.img, command=self.logo, relief=FLAT, highlightthickness=0, bd=0)
        btn.place(relx = 0.5, rely = 0.3, anchor = 'center')



        self.image1 = PIL.Image.open("lemca/gui/bineuse.png")
        self.image1 = self.image1.resize((size, size))
        self.image1 = PIL.ImageTk.PhotoImage(self.image1)

        btn = Button(window, image=self.image1, command=self.clicked_bineuse, relief=FLAT, highlightthickness=0, bd=0)
        btn.place(relx = 0.2, rely = y1, anchor = 'center')

        self.image2 = PIL.Image.open("lemca/gui/refresh.png")
        self.image2 = self.image2.resize((size, size))
        self.image2 = PIL.ImageTk.PhotoImage(self.image2)

        btn = Button(window, image=self.image2, command=self.install_bineuse, relief=FLAT, highlightthickness=0, bd=0)
        btn.place(relx = 0.4, rely = y1, anchor = 'center')

        self.image3 = PIL.Image.open("lemca/gui/reseau.png")
        self.image3 = self.image3.resize((size, size))
        self.image3 = PIL.ImageTk.PhotoImage(self.image3)

        btn = Button(window, image=self.image3, command=self.teamviewer, relief=FLAT, highlightthickness=0, bd=0)
        btn.place(relx = 0.6, rely = y1, anchor = 'center')

        self.image4 = PIL.Image.open("lemca/gui/off.png")
        self.image4 = self.image4.resize((size, size))
        self.image4 = PIL.ImageTk.PhotoImage(self.image4)

        btn = Button(window, image=self.image4, command=self.my_exit, relief=FLAT, highlightthickness=0, bd=0)
        btn.place(relx = 0.8, rely = y1, anchor = 'center')
        
        self.image10 = PIL.Image.open("lemca/gui/wifi.png")
        self.image10 = self.image10.resize((size, size))
        self.image10 = PIL.ImageTk.PhotoImage(self.image10)

        btn = Button(window, image=self.image10, command=self.wifi, relief=FLAT, highlightthickness=0, bd=0)
        btn.place(relx = 0.8, rely = 0.2, anchor = 'center')

        if(self.advanced):
            print("advanced1")
            self.add_advanced_buttons()
            #window.attributes('-zoomed', True)  

        else:
            window.attributes('-fullscreen', True)  
            #clicked_bineuse()
            


print("lemca")
window = Tk()
window.title("Lemca app")
window.geometry('1400x800')
l = LemcaGui()
l.run()

window.mainloop()

