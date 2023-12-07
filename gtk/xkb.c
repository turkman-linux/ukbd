#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <stdio.h>
#include <stdlib.h>

Display *display;

char* get_label_from_keycode(int code, int group){
    if(display == NULL){
        display = XOpenDisplay(NULL);
        if (!display) {
            fprintf(stderr, "Unable to open display\n");
            exit(1);
        }
    }
    KeySym keysym = XkbKeycodeToKeysym(display, code, group, 0);
    char* sym = XKeysymToString(keysym);
    if(sym){
        return sym;
    }else{
        return "";
    }
}

