#include <linux/uinput.h>
#include <gui.h>

void build_layout_mini(){
    // num row
    add_button(KEY_GRAVE, 0, 0, l(2));
    add_buttons(0, 1, KEY_1, KEY_EQUAL, l(2));
    add_button_with_label(KEY_BACKSPACE, 13, 0, l(2.5), "<--");
    add_button(KEY_DELETE, 14, 0, l(2));

    // first row
    add_button_with_label(KEY_TAB, 0, 1, l(2.25), "Tab");
    add_buttons(1, 1, KEY_Q, KEY_RIGHTBRACE, l(2));
    add_button(KEY_BACKSLASH, 15, 1, l(2.25));
    add_button_with_label(KEY_PAGEUP, 16, 1, l(2), "PgUp");

    // second row
    add_button_with_label(KEY_CAPSLOCK, 0, 2, l(3), "Caps");
    add_buttons(2, 1, KEY_A, KEY_APOSTROPHE, l(2));
    add_button_with_label(KEY_ENTER, 14, 2, l(3.5), "Enter");
    add_button_with_label(KEY_PAGEDOWN, 15, 2, l(2), "PgDn");

    // third row
    add_button_custom(KEY_LEFTSHIFT, 0, 3, l(3.6), create_toggle_button(KEY_LEFTSHIFT, "Shift"));
    add_buttons(3, 1, KEY_Z, KEY_SLASH, l(2));
    add_button_custom(KEY_RIGHTSHIFT, 12, 3, l(2.3), create_toggle_button(KEY_RIGHTSHIFT, "Shift"));
    add_button_with_label(KEY_UP, 13, 3, l(2.3), "Up");
    add_button_with_label(KEY_END, 14, 3, l(2.3), "End");

    // bottom row
    add_button_custom(KEY_LEFTCTRL, 0, 4, l(2.3), create_toggle_button(KEY_LEFTCTRL, "Ctrl"));
    add_button_with_label(KEY_LEFTMETA, 1, 4, l(2.3), "Lnx");
    add_button_custom(KEY_LEFTALT, 2, 4, l(2.3), create_toggle_button(KEY_LEFTALT, "Alt"));
    add_button_with_label(KEY_SPACE, 3, 4, l(12.4), "____");
    add_button_custom(KEY_RIGHTALT, 4, 4, l(2.3), create_toggle_button(KEY_RIGHTALT, "Alt"));
    add_button_custom(KEY_RIGHTCTRL, 5, 4, l(2), create_toggle_button(KEY_RIGHTCTRL, "Ctrl"));
    add_button_with_label(KEY_LEFT, 6, 4, l(2.3), "LEFT");
    add_button_with_label(KEY_DOWN, 7, 4, l(2.3), "DOWN");
    add_button_with_label(KEY_RIGHT, 8, 4, l(2.3), "RIGHT");
}