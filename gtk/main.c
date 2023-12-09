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

    // F row
    add_button_with_label(KEY_ESC, 0, 0, 100 / 10, "Esc");
    for (int i=1;i<=12;i++){
        char str[4] = "F";
        sprintf(str, "F%d", i);
        add_button_with_label(i+59, i, 0, 80 / 12.0, str);
    }
    add_button_with_label(KEY_DELETE, 13, 0, 100 / 10, "Del");

    // number row
    add_button(KEY_GRAVE, 0, 1, 90 / 13.0);
    add_buttons(1, 1, KEY_1, KEY_EQUAL, 90 / 13.0);
    add_button_with_label(KEY_BACKSPACE, 13, 1, 100 / 10.0, "<--");


    // first row
    add_buttons(2, 0, KEY_Q, KEY_RIGHTBRACE, 100 / 13.0);
    add_button(KEY_BACKSLASH, 14, 2, 100 / 13.0);

    // second row
    add_buttons(3, 0, KEY_A, KEY_APOSTROPHE, 90 / 11.0);
    add_button_with_label(KEY_ENTER, 13, 3, 100 / 10.0, "Enter");

    // third row
    add_buttons(4, 0, KEY_Z, KEY_SLASH, 100 / 10.0);

    // trigger resize event
    reallocate_buttons(600, 200);

    gtk_widget_show_all(window);
    
    // main event
    gtk_main();
}

