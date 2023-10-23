from ctypes import *
import os
libukbd = CDLL("libukbd.so")
libukbd.ukbd_send.argtypes = [c_int]
libukbd.ukbd_event.argtypes = [c_int, c_int]
libukbd.ukbd_press.argtypes = [c_int]
libukbd.ukbd_release.argtypes = [c_int]

def event(code, event):
    libukbd.ukbd_send(code, event)

def send(code):
    libukbd.ukbd_send(code)

def press(code):
    libukbd.ukbd_press(code)

def release(code):
    libukbd.ukbd_release(code)
