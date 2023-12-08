#include <gtk/gtk.h>
#include <gui.h>
#include <linux/uinput.h>
// X11 code + 8 = uinput code
#define BUTTON(A) create_button(A, get_label_from_keycode(A + 8, 0))

// https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h
void main(int argc, char **argv)
{
    // init gtk
    gtk_init(&argc, &argv);
    GtkWidget *window = init_window();

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

    // number row
    add_button(KEY_GRAVE, 0, 0, 100 / 13.0);
    add_buttons(0, 1, KEY_1, KEY_EQUAL, 100 / 13.0);
    // first row
    add_buttons(1, 0, KEY_Q, KEY_RIGHTBRACE, 100 / 12.0);
    // second row
    add_buttons(2, 0, KEY_A, KEY_APOSTROPHE, 100 / 12.0);
    add_button(KEY_BACKSLASH, 14, 2, 100 / 12.0);

    // third row
    add_buttons(3, 0, KEY_Z, KEY_SLASH, 100 / 10.0);

    gtk_widget_show_all(window);

    // main event
    gtk_main();
}

