#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

extern char* str_to_label(char* str);
Display *display;

char* get_label_from_keycode(int code, int level){
    if(display == NULL){
        display = XOpenDisplay(NULL);
        if (!display) {
            fprintf(stderr, "Unable to open display\n");
            exit(1);
        }
    }
    KeySym keysym = XkbKeycodeToKeysym(display, code, 0, level);
    char* sym = XKeysymToString(keysym);
    if(sym){
        return str_to_label(sym);
    }else{
        return "";
    }
}

bool is_capslock_enabled(){
   XKeyboardState x;
   XGetKeyboardControl(display, &x);
   if(x.led_mask & 1){
      return true;
   }
   return false;
}




