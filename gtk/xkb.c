#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define iseq(A,B) strcmp(A,B)==0
static char* str_to_label(char* str);
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
        return str_to_label(sym);
    }else{
        return "";
    }
}

static char* str_to_label(char* str){
    if(iseq(str,"grave")){
        return "`";
    }else if(iseq(str,"minus")){
        return "-";
    }else if(iseq(str,"equal")){
        return "=";
    }else if(iseq(str,"bracketleft")){
        return "[";
    }else if(iseq(str,"bracketright")){
        return "]";
    }else if(iseq(str,"semicolon")){
        return ";";
    }else if(iseq(str,"apostrophe")){
        return "'";
    }else if(iseq(str,"backslash")){
        return "\\";
    }else if(iseq(str,"comma")){
        return ",";
    }else if(iseq(str,"period")){
        return ".";
    }else if(iseq(str,"slash")){
        return "/";
    }else if(iseq(str,"quotedbl")){
        return "\"";
    }else if(iseq(str,"asterisk")){
        return "*";
    }else if(iseq(str,"idotless")){
        return "ı";
    }else if(iseq(str,"gbreve")){
        return "ğ";
    }else if(iseq(str,"udiaeresis")){
        return "ü";
    }else if(iseq(str,"scedilla")){
        return "ş";
    }else if(iseq(str,"odiaeresis")){
        return "ö";
    }else if(iseq(str,"ccedilla")){
        return "ç";
    }else if(iseq(str,"schwa")){
        return "ə";
    }else{
        return str;
    }
}
