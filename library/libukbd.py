from ctypes import *
import os
libukbd = CDLL("libukbd.so")
libukbd.ukbd_send.argtypes = [c_int]
libukbd.ukbd_press.argtypes = [c_int]
libukbd.ukbd_release.argtypes = [c_int]

def ukbd_send(code):
    libukbd.ukbd_send(code)

def ukbd_press(code):
    libukbd.ukbd_press(code)

def ukbd_release(code):
    libukbd.ukbd_release(code)