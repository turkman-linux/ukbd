#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define iseq(A,B) strcmp(A,B)==0
static char* str_to_label(char* str);
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

#define str_check(A, B, C) if(iseq(A,B)){return C;}

static char* str_to_label(char* str){
    str_check(str, "Acircumflex", "Â");
    str_check(str, "Ccedilla", "Ç");
    str_check(str, "EuroSign", "€");
    str_check(str, "Gbreve", "Ğ");
    str_check(str, "Iabovedot", "İ");
    str_check(str, "Icircumflex", "Î");
    str_check(str, "Ocircumflex", "Ô");
    str_check(str, "Odiaeresis", "Ö");
    str_check(str, "Scedilla", "Ş");
    str_check(str, "Ucircumflex", "Û");
    str_check(str, "Udiaeresis", "Ü");
    str_check(str, "VoidSymbol", "");
    str_check(str, "acircumflex", "â");
    str_check(str, "acute", "´");
    str_check(str, "ampersand", "&");
    str_check(str, "apostrophe", "'");
    str_check(str, "asciicircum", "^");
    str_check(str, "asciitilde", "~");
    str_check(str, "asterisk", "*");
    str_check(str, "at", "@");
    str_check(str, "backslash", "\\");
    str_check(str, "bar", "|");
    str_check(str, "braceleft", "{");
    str_check(str, "braceright", "}");
    str_check(str, "bracketleft", "[");
    str_check(str, "bracketright", "]");
    str_check(str, "ccedilla", "ç");
    str_check(str, "cent", "¢");
    str_check(str, "colon", ":");
    str_check(str, "comma", ",");
    str_check(str, "copyright", "©");
    str_check(str, "copyright", "©");
    str_check(str, "dead_abovedot", "");
    str_check(str, "dead_abovering", "");
    str_check(str, "dead_acute", "");
    str_check(str, "dead_breve", "");
    str_check(str, "dead_caron", "");
    str_check(str, "dead_diaeresis", "");
    str_check(str, "dead_grave", "");
    str_check(str, "degree", "°");
    str_check(str, "division", "÷");
    str_check(str, "dollar", "$");
    str_check(str, "equal", "=");
    str_check(str, "exclamdown", "¡");
    str_check(str, "exclam", "!");
    str_check(str, "gbreve", "ğ");
    str_check(str, "grave", "`");
    str_check(str, "greater", ">");
    str_check(str, "guillemetleft", "«");
    str_check(str, "guillemetright", "»");
    str_check(str, "icircumflex", "î");
    str_check(str, "idotless", "ı");
    str_check(str, "leftdoublequotemark", "“");
    str_check(str, "less", "<");
    str_check(str, "minus", "-");
    str_check(str, "multiply", "×");
    str_check(str, "mu", "µ");
    str_check(str, "nobreakspace", " ");
    str_check(str, "notsign", "¬");
    str_check(str, "numbersign", "#");
    str_check(str, "ocircumflex", "ô");
    str_check(str, "odiaeresis", "ö");
    str_check(str, "onehalf", "½");
    str_check(str, "onequarter", "¼");
    str_check(str, "onesuperior", "¹");
    str_check(str, "paragraph", "¶");
    str_check(str, "parenleft", "(");
    str_check(str, "parenright", ")");
    str_check(str, "percent", "%");
    str_check(str, "periodcentered", "·");
    str_check(str, "period", ".");
    str_check(str, "plusminus", "±");
    str_check(str, "plus", "+");
    str_check(str, "questiondown", "¿");
    str_check(str, "question", "?");
    str_check(str, "quotedbl", "\"");
    str_check(str, "registered", "®");
    str_check(str, "rightdoublequotemark", "”");
    str_check(str, "scedilla", "ş");
    str_check(str, "schwa", "ə");
    str_check(str, "section", "§");
    str_check(str, "semicolon", ";");
    str_check(str, "slash", "/");
    str_check(str, "sterling", "£");
    str_check(str, "threeeighths", "⅜");
    str_check(str, "threequarters", "¾");
    str_check(str, "threesuperior", "³");
    str_check(str, "twosuperior", "²");
    str_check(str, "ucircumflex", "û");
    str_check(str, "udiaeresis", "ü");
    str_check(str, "underscore", "_");
    str_check(str, "yen", "¥");
   return str;
}
