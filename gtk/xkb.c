#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

extern char* str_to_label(char* str);
char* unicodeToString(const char* unicodeString);
Display *display;

static int i, j;
int startswith(const char* data, const char* f) {
    i = strlen(data);
    j = strlen(f);

    if (i < j) {
        return 0;
    }

    return strncmp(data, f, j) == 0;
}

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
        if(startswith(sym,"dead_")){
            return "";
        }else if (0 == strcmp(sym,"VoidSymbol")){
            return "";
        }else if(strlen(sym) > 3 && startswith(sym,"U")){
            return unicodeToString(sym);
        }
        return str_to_label(sym);
    }else{
        return "";
    }
}

char* unicodeToString(const char* unicodeString) {
    // Convert the Unicode string to an integer
    unsigned int unicodeValue = (unsigned int)strtol(unicodeString + 1, NULL, 16);

    // Allocate memory for the string representation of the Unicode character
    char* result = (char*)malloc(5); // Sufficient for the UTF-8 encoding of a single character

    // Convert the Unicode value to a string and store it in the result
    sprintf(result, "%lc", (int8_t)unicodeValue);

    return result;
}

bool is_capslock_enabled(){
   XKeyboardState x;
   XGetKeyboardControl(display, &x);
   if(x.led_mask & 1){
      return true;
   }
   return false;
}


