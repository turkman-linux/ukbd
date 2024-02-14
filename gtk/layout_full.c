#include <linux/uinput.h>
#include <gui.h>

void build_layout_full(){
    // F row
    add_button_with_image(KEY_ESC, 0, 0, l(2.25), "ukbd-esc");
    for (int i=1;i<=10;i++){
        char str[4] = "F";
        sprintf(str, "F%d", i);
        add_button_with_label(i+58, i, 0, l(2), str);
    }
    add_button_with_label(KEY_F11, 11, 0, l(2), "F11");
    add_button_with_label(KEY_F12, 12, 0, l(2), "F12");
    add_button_with_label(KEY_SYSRQ, 13, 0, l(2), "Ptsc");
    add_button_with_image(KEY_DELETE, 14, 0, l(2.25), "ukbd-del");

    // number row
    add_button(KEY_GRAVE, 0, 1, l(2));
    add_buttons(1, 1, KEY_1, KEY_EQUAL, l(2));
    add_button_with_image(KEY_BACKSPACE, 13, 1, l(2.5), "ukbd-backspace");
    add_button_with_image(KEY_HOME, 14, 1, l(2), "ukbd-home");


    // first row
    add_button_with_image(KEY_TAB, 0, 2, l(2.25), "ukbd-tab");
    add_buttons(2, 1, KEY_Q, KEY_RIGHTBRACE, l(2));
    add_button(KEY_BACKSLASH, 15, 2, l(2.25));
    add_button_with_image(KEY_PAGEUP, 16, 2, l(2), "ukbd-pgup");

    // second row
    add_button_with_label(KEY_CAPSLOCK, 0, 3, l(3), "Caps");
    add_buttons(3, 1, KEY_A, KEY_APOSTROPHE, l(2));
    add_button_with_image(KEY_ENTER, 14, 3, l(3.5), "ukbd-enter");
    add_button_with_image(KEY_PAGEDOWN, 15, 3, l(2), "ukbd-pgdn");

    // third row
    add_button_custom(KEY_LEFTSHIFT, 0, 4, l(3.6), create_toggle_button(KEY_LEFTSHIFT, "shift"));
    add_buttons(4, 1, KEY_Z, KEY_SLASH, l(2));
    add_button_custom(KEY_RIGHTSHIFT, 12, 4, l(2.3), create_toggle_button(KEY_RIGHTSHIFT, "shift"));
    add_button_with_image(KEY_UP, 13, 4, l(2.3), "ukbd-up-arrow");
    add_button_with_image(KEY_END, 14, 4, l(2.3), "ukbd-end");

    // bottom row
    add_button_custom(KEY_LEFTCTRL, 0, 5, l(2.3), create_toggle_button(KEY_LEFTCTRL, "ctrl"));
    add_button_with_label(KEY_LEFTMETA, 1, 5, l(2.3), "Lnx");
    add_button_custom(KEY_LEFTALT, 2, 5, l(2.3), create_toggle_button(KEY_LEFTALT, "alt"));
    add_button_with_label(KEY_SPACE, 3, 5, l(12.4), "____");
    add_button_custom(KEY_RIGHTALT, 4, 5, l(2.3), create_toggle_button(KEY_RIGHTALT, "alt"));
    add_button_custom(KEY_RIGHTCTRL, 5, 5, l(2), create_toggle_button(KEY_RIGHTCTRL, "ctrl"));
    add_button_with_image(KEY_LEFT, 6, 5, l(2.3), "ukbd-left-arrow");
    add_button_with_image(KEY_DOWN, 7, 5, l(2.3), "ukbd-down-arrow");
    add_button_with_image(KEY_RIGHT, 8, 5, l(2.3), "ukbd-right-arrow");
}
