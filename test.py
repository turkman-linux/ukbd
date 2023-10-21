import sys, os
sys.path.append("library")

from libukbd import *
ukbd_send(33)
ukbd_press(35)
ukbd_release(35)

