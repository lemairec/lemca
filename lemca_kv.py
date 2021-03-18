from kivy.app import App
from kivy.config import Config 
from kivy.uix.button import Button
from kivy.uix.floatlayout import FloatLayout
from kivy.uix.boxlayout import BoxLayout
from kivy.core.window import Window
from kivy.uix.vkeyboard import VKeyboard 
from kivy.uix.popup import Popup 
from kivy.uix.textinput import TextInput 
from kivy.uix.label import Label 
from kivy.uix.image import Image 
from kivy.clock import Clock 

from mywifi import MyWifiList

import os
import subprocess 
import sys

#from wifi import Cell, Scheme
#list(Cell.all('wlan0'))

Window.clearcolor = (1, 1, 1, 1)
#Window.fullscreen = 'auto'

image_h = 0.14
image_w = 0.2
width_clavier = 1400

def call_without_print(cmdline):
    ret = subprocess.call(cmdline, shell=True)
    if ret != 0:
        print(sys.stderr, 'Running: ' + cmdline + ' failed with exit code ' + str(ret) + '!')
    return ret

def call(cmdline):
    print('Running: ' + cmdline)
    call_without_print(cmdline)


class WifiPopUp():
    def my_cancel(self, instance):
        self.popup.dismiss()

    def build(self):
        box_popup = FloatLayout(size_hint=(0.9, 0.9))
        box_popup.add_widget(VKeyboard(pos_hint={'center_x': .5, 'center_y': .45}, size=(width_clavier, width_clavier*0.3)))
        
        btn1 = Button(text = 'Ok'
            , size_hint=(0.2, 0.1), pos_hint={'center_x': .3, 'center_y': .1})
        #btn1.bind(on_press = self.say_hello) # Note: here say_hello doesn't have brackets.
        box_popup.add_widget(btn1)

        btn1 = Button(text = 'Cancel'
            , size_hint=(0.2, 0.1), pos_hint={'center_x': .7, 'center_y': .1})
        btn1.bind(on_press = self.my_cancel)
        box_popup.add_widget(btn1)
        
        self.popup = Popup(title='Wifi',
            content=box_popup,
            size_hint=(0.9, 0.9))

class ListWifiPopUp():
    def my_cancel(self, instance):
        self.popup.dismiss()

    def wifi_btn(self, instance):
        print(instance.text)

    def build(self):
        wifi = MyWifiList()
        wifis = wifi.get_list_wifis()
        box_popup2 = FloatLayout(size_hint=(0.9, 0.9))
        box_popup = BoxLayout(orientation='vertical', size_hint=(0.8, 0.7), pos_hint={'center_x': .5, 'center_y': .6})
        
        for wifi in wifis:
            btn1 = Button(text = wifi)
            btn1.bind(on_press = self.wifi_btn)
            box_popup.add_widget(btn1)
        btn1 = Button(text = 'Cancel'
            , size_hint=(0.2, 0.1), pos_hint={'center_x': .7, 'center_y': .1})
        btn1.bind(on_press = self.my_cancel)
        box_popup2.add_widget(btn1)

        box_popup2.add_widget(box_popup)
        
        self.popup = Popup(title='Liste des wifis',
            content=box_popup2,
            size_hint=(0.9, 0.9))
        

class ConsolePopUp():
    def my_cancel(self, instance):
        self.popup.dismiss()

    def my_key_up(self, i0, i1, i2, i3):
        print(i0)
        print(i1)
        print(i2)
        print(i3)
        self.textinput.text += i2

    def _keyboard_closed(self):
            self._keyboard = None


    def build(self):
        box_popup2 = FloatLayout(size_hint=(0.9, 0.9))
        self.popup = Popup(title='Liste des wifis',
            content=box_popup2,
            size_hint=(0.9, 0.9))
        box_popup = BoxLayout(orientation='vertical', size_hint=(0.8, 0.7), pos_hint={'center_x': .5, 'center_y': .6})
        
        self.textinput = TextInput(text='', multiline=False)
        box_popup.add_widget(self.textinput)
        textinput2 = TextInput(text='', multiline=False)
        box_popup.add_widget(textinput2)
        self._keyboard = Window.request_keyboard(self._keyboard_closed, self.popup)

        
        btn1 = Button(text = 'Cancel'
            , size_hint=(0.2, 0.1), pos_hint={'center_x': .7, 'center_y': .1})
        btn1.bind(on_press = self.my_cancel)
        btn1 = Button(text = 'Ok'
            , size_hint=(0.2, 0.1), pos_hint={'center_x': .3, 'center_y': .1})
        btn1.bind(on_press = self.my_cancel)
        box_popup2.add_widget(btn1)

        box_popup2.add_widget(box_popup)
        
        
        


class FreePosApp(App):
    def update_wifi(self, instance):
        hostname = "google.com" #example
        response = os.system("ping -c 1 " + hostname)

        #and then check the response...
        if response == 0:
            print(hostname, 'is up!')
            self.btn_internet.background_color = [0, 2, 0, 1]
        else:
            print(hostname, 'is down!')
            self.btn_internet.background_color = [1, 1, 1, 1]

        print("verify")

    def open_wifi(self, instance):
        self.consolePopUp.popup.open()


    def say_hello(self, instance):
        self.data = 1
        self.btn_wifi.background_color = [255, 0, 0, 1]
        
    def my_exit(self, instance):
        call("/sbin/shutdown -h now")

    def build(self):
        self.title = 'Free Positioning'
        self.wifiPopUp = ListWifiPopUp()
        self.wifiPopUp.build()

        self.consolePopUp = ConsolePopUp()
        self.consolePopUp.build()

        box = FloatLayout()

        logo = Image(source='gui/logo.png', size_hint=(0.4, 0.7), allow_stretch=True, pos_hint={'center_x': .5, 'center_y': .7})
        box.add_widget(logo)

        btn1 = Button(background_normal = 'lemca/gui/bineuse.png'
                     , size_hint=(image_h, image_w), pos_hint={'center_x': .2, 'center_y': .25})
        btn1.bind(on_press = self.say_hello) # Note: here say_hello doesn't have brackets.
        box.add_widget(Label(text="bineuse",pos_hint={'center_x': .2, 'center_y': .15}, color=[0,0,0,1]))
        box.add_widget(btn1)
        
        
        btn2 = Button(background_normal = 'lemca/gui/refresh.png'
                     , size_hint=(image_h, image_w), pos_hint={'center_x': .4, 'center_y': .25})
        btn2.bind(on_press = self.say_hello) # Note: here say_hello doesn't have brackets.
        box.add_widget(Label(text="reinstall",pos_hint={'center_x': .4, 'center_y': .15}, color=[0,0,0,1]))
        box.add_widget(btn2)

        btn3 = Button(background_normal = 'lemca/gui/reseau.png'
                     , size_hint=(image_h, image_w), pos_hint={'center_x': .6, 'center_y': .25})
        btn3.bind(on_press = self.say_hello) # Note: here say_hello doesn't have brackets.
        box.add_widget(Label(text="teamviewer",pos_hint={'center_x': .6, 'center_y': .15}, color=[0,0,0,1]))
        box.add_widget(btn3)

        btn3 = Button(background_normal = 'lemca/gui/off.png'
                     , size_hint=(image_h, image_w), pos_hint={'center_x': .8, 'center_y': .25})
        btn3.bind(on_press = self.my_exit) # Note: here say_hello doesn't have brackets.
        box.add_widget(Label(text="bineuse",pos_hint={'center_x': .2, 'center_y': .15}, color=[0,0,0,1]))
        box.add_widget(btn3)

        if(True):
            btn3 = Button(background_normal = 'lemca/gui/gps.png'
                     , size_hint=(image_h*0.8, image_w*0.8), pos_hint={'center_x': .2, 'center_y': .45})
            btn3.bind(on_press = self.say_hello) # Note: here say_hello doesn't have brackets.
            box.add_widget(Label(text="gps",pos_hint={'center_x': .2, 'center_y': .4}, color=[0,0,0,1]))
            box.add_widget(btn3)

            btn3 = Button(background_normal = 'lemca/gui/refresh.png'
                     , size_hint=(image_h*0.8, image_w*0.8), pos_hint={'center_x': .4, 'center_y': .45})
            btn3.bind(on_press = self.say_hello) # Note: here say_hello doesn't have brackets.
            box.add_widget(Label(text="reinstall",pos_hint={'center_x': .4, 'center_y': .4}, color=[0,0,0,1]))
            box.add_widget(btn3)

            btn3 = Button(background_normal = 'lemca/gui/save.png'
                     , size_hint=(image_h*0.8, image_w*0.8), pos_hint={'center_x': .6, 'center_y': .45})
            btn3.bind(on_press = self.say_hello) # Note: here say_hello doesn't have brackets.
            box.add_widget(Label(text="save",pos_hint={'center_x': .6, 'center_y': .4}, color=[0,0,0,1]))
            box.add_widget(btn3)

            
        

        self.btn_wifi = Button(text="wifi"
                     , size_hint=(0.1, 0.1), pos_hint={'center_x': .9, 'center_y': .9})
        self.btn_wifi.bind(on_press = self.open_wifi)
        box.add_widget(self.btn_wifi)
        
        self.btn_internet = Button(text="internet"
                     , size_hint=(0.1, 0.1), pos_hint={'center_x': .8, 'center_y': .9})
        box.add_widget(self.btn_internet)
        
        Clock.schedule_interval(self.update_wifi, 2.0)
        
        return box

#Config.set('graphics', 'fullscreen', 'auto')
#Config.set('graphics', 'window_state', 'maximized')
Config.set('kivy', 'keyboard_mode', 'systemanddock')
Config.set('kivy', 'keyboard_mode', 'systemandmulti')
Config.write()

FreePosApp().run()
