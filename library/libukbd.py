from ctypes import *
import os
__libukbd = CDLL("libukbd.so")
__libukbd.ukbd_send.argtypes = [c_int]
__libukbd.ukbd_event.argtypes = [c_int, c_int]
__libukbd.ukbd_press.argtypes = [c_int]
__libukbd.ukbd_release.argtypes = [c_int]

event = __libukbd.ukbd_event
send = __libukbd.ukbd_send
press = __libukbd.ukbd_press
release = __libukbd.ukbd_release
