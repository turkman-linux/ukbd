#include <gtk/gtk.h>
#include <gui.h>
#include <linux/uinput.h>
#include <keyboard.h>
// X11 code + 8 = uinput code
#define BUTTON(A) create_button(A, get_label_from_keycode(A + 8, 0))
// keyboard dimensin to percent
#define l(A) A*100/30.5
GtkWidget *window;

// https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h
void main(int argc, char **argv) {
    // force use X11 backend
    setenv("GDK_BACKEND", "x11", 1);
    // init gtk
    gtk_init(&argc, &argv);
    window = init_window();

    if (access( SERVER_SOCK_FILE, F_OK ) != 0 ) {
       gtk_container_add(window, gtk_label_new("Failed to connect service!"));
       gtk_widget_show_all(window);
       gtk_main();
       return 0;
    } 

    keyboardview_init(window);

    /*
    void add_buttons(
        int row,
        int offset,
        int min,
        int max,
        float percent);
    void add_button(
        int keycode,
        int row,
        int col,
        float percent);
    */

    // F row
    add_button_with_label(KEY_ESC, 0, 0, l(2.25), "Esc");
    for (int i=1;i<=10;i++){
        char str[4] = "F";
        sprintf(str, "F%d", i);
        add_button_with_label(i+58, i, 0, l(2), str);
    }
    add_button_with_label(KEY_F11, 11, 0, l(2), "F11");
    add_button_with_label(KEY_F12, 12, 0, l(2), "F12");
    add_button_with_label(KEY_SYSRQ, 13, 0, l(2), "Ptsc");
    add_button_with_label(KEY_DELETE, 14, 0, l(2.25), "Del");

    // number row
    add_button(KEY_GRAVE, 0, 1, l(2));
    add_buttons(1, 1, KEY_1, KEY_EQUAL, l(2));
    add_button_with_label(KEY_BACKSPACE, 13, 1, l(2.5), "<--");
    add_button_with_label(KEY_HOME, 14, 1, l(2), "Home");


    // first row
    add_button_with_label(KEY_TAB, 0, 2, l(2.25), "Tab");
    add_buttons(2, 1, KEY_Q, KEY_RIGHTBRACE, l(2));
    add_button(KEY_BACKSLASH, 15, 2, l(2.25));
    add_button_with_label(KEY_PAGEUP, 16, 2, l(2), "PgUp");

    // second row
    add_button_with_label(KEY_CAPSLOCK, 0, 3, l(3), "Caps");
    add_buttons(3, 1, KEY_A, KEY_APOSTROPHE, l(2));
    add_button_with_label(KEY_ENTER, 14, 3, l(3.5), "Enter");
    add_button_with_label(KEY_PAGEDOWN, 15, 3, l(2), "PgDn");

    // third row
    add_button_custom(KEY_LEFTSHIFT, 0, 4, l(3.6), create_toggle_button(KEY_LEFTSHIFT, "Shift"));
    add_buttons(4, 1, KEY_Z, KEY_SLASH, l(2));
    add_button_custom(KEY_RIGHTSHIFT, 12, 4, l(2.3), create_toggle_button(KEY_RIGHTSHIFT, "Shift"));
    add_button_with_label(KEY_UP, 13, 4, l(2.3), "Up");
    add_button_with_label(KEY_END, 14, 4, l(2.3), "End");

    // bottom row
    add_button_custom(KEY_LEFTCTRL, 0, 5, l(2.3), create_toggle_button(KEY_LEFTCTRL, "Ctrl"));
    add_button_with_label(KEY_LEFTMETA, 1, 5, l(2.3), "Lnx");
    add_button_custom(KEY_LEFTALT, 2, 5, l(2.3), create_toggle_button(KEY_LEFTALT, "Alt"));
    add_button_with_label(KEY_SPACE, 3, 5, l(12.4), "____");
    add_button_custom(KEY_RIGHTALT, 4, 5, l(2.3), create_toggle_button(KEY_RIGHTALT, "Alt"));
    add_button_custom(KEY_RIGHTCTRL, 5, 5, l(2), create_toggle_button(KEY_RIGHTCTRL, "Ctrl"));
    add_button_with_label(KEY_LEFT, 6, 5, l(2.3), "LEFT");
    add_button_with_label(KEY_DOWN, 7, 5, l(2.3), "DOWN");
    add_button_with_label(KEY_RIGHT, 8, 5, l(2.3), "RIGHT");


    gtk_widget_show_all(window);
    update_buttons();
    // trigger resize event
    reallocate_buttons(666, 222);

    // main event
    gtk_main();
}

