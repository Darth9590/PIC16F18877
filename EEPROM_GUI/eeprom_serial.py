#!/usr/bin/env python3
from kivy.app import App
from kivy.lang import Builder
from kivy.core.window import Window
from kivy.uix.screenmanager import ScreenManager, Screen
from kivymd.app import MDApp

from bitstring import Bits

import serial
import time
import os
#==========================================================================#
#*************************** Configurations *******************************#
#==========================================================================#

# Configure the serial port used for communications
ser = serial.Serial(
    port='/dev/ttyUSB0',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    bytesize=serial.EIGHTBITS,
    stopbits=serial.STOPBITS_ONE)


#==========================================================================#
#****************************** Functions *********************************#
#==========================================================================#
class Serial:

    def serial_write(self, command):
        print(command)
        ser.write(command)

    def serial_read(self):
        text = ser.readline()
        new_string = text.replace(b'\n', b'')
        return new_string

#==========================================================================#
#******************************* Classes **********************************#
#==========================================================================#


class MainWindow(Screen):

    def close_app(self):
        #close application
        App.get_running_app().stop()
        #remove window
        Window.close()
        pass

    def send1(self):
       Serial.serial_write('1')
       out = Serial.serial_read(self)
       print(out)

class ByteWrite(Screen):

    def serial_writebyte(self):
        Serial.serial_write(self, b'1')

        baddr1 = bytearray(self.ids.addr1.text, 'utf-8')
        baddr2 = bytearray(self.ids.addr2.text, 'utf-8')
        bdata = bytearray(self.ids.data.text, 'utf-8')
        Serial.serial_write(self, baddr1)
        Serial.serial_write(self, baddr2)
        Serial.serial_write(self, bdata)
        text1 = str(bdata, 'utf-8')
        text2 = str(baddr1, 'utf-8')
        text3 = str(baddr2, 'utf-8')


        self.ids.result.text = ("Wrote " + "0x" + text1 + " to " + "0x" + text2 + text3)

    def serial_readbyte(self):
        Serial.serial_write(self, b'4')
        baddr1 = bytearray(self.ids.addr1.text, 'utf-8')
        baddr2 = bytearray(self.ids.addr2.text, 'utf-8')
        Serial.serial_write(self, baddr1)
        Serial.serial_write(self, baddr2)

        text1 = str(baddr1, 'utf-8 ')
        text2 = str(baddr2, 'utf-8')
        text3 = Serial.serial_read(self)

        self.ids.result.text =("Read 0x0" + text1 + text2 + " 0x" + str(text3, 'UTF-8'))

    def clear_text(self):

        self.ids.addr1.text = ""
        self.ids.addr2.text = ""
        self.ids.data.text = ""

class PageWrite(Screen):
   def serial_writebytes(self):

        a = 0

        Serial.serial_write(self, b'2')
        baddr1 = bytearray(self.ids.addr1.text, 'utf-8')
        baddr2 = bytearray(self.ids.addr2.text, 'utf-8')
        data = bytearray(self.ids.data.text, 'utf-8')
        loop = bytearray(self.ids.loops.text, 'utf-8')
        Serial.serial_write(self, baddr1)
        Serial.serial_write(self, baddr2)
        Serial.serial_write(self, data)
        Serial.serial_write(self, loop)
        loops = int(loop)
        while a < loops:
            b = 0
            while b < 32 :

                time.sleep(0.01);

                b += 1
            a += 1

        self.ids.result.text = "ALL DONE"

   def clear_text(self):

       self.ids.addr1.text = ""
       self.ids.addr2.text = ""
       self.ids.data.text = ""
       self.ids.loops.text = ""
       self.ids.result.text = ""

   def writing(self):
       self.ids.result.text = "Writing"

class CurrentAddr(Screen):
    pass

class RandomRead(Screen):
    pass

class SequentialRead(Screen):

     def serial_readbyte(self):

        a = 0


        Serial.serial_write(self, b'3')
        baddr1 = bytearray(self.ids.addr1.text, 'utf-8')
        baddr2 = bytearray(self.ids.addr2.text, 'utf-8')
        loop = bytearray(self.ids.loops.text, 'utf-8')
        Serial.serial_write(self, baddr1)
        Serial.serial_write(self, baddr2)
        Serial.serial_write(self, loop)
        loops = int(loop)

        f = open('read.txt', 'w')
        f.close()
        f = open('read.txt', 'a')
        while a < loops:
            b = 0
            while b < 32 :

                data = str(Serial.serial_read(self), 'utf-8')
                f.write(data)
                b += 1
            a += 1
        f.close()
        self.ids.result.text = ("File created")

     def clear_text(self):

        self.ids.addr1.text = ""
        self.ids.addr2.text = ""
        self.ids.loops.text = ""
        self.ids.result.text = ""

     def button_press(self):
        self.ids.result.text = ("Writing to file")

 
class WindowManager(ScreenManager):
    pass



class MyApp(MDApp):
    def build(self):
        self.theme_cls.theme_style="Dark"
        kv = Builder.load_file('gui.kv')
        return kv



if __name__ == '__main__':

    MyApp().run()
