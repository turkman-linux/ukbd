#include <gtk/gtk.h>
#include <gui.h>

// X11 code + 8 = uinput code
#define BUTTON(A) create_button(A, get_label_from_keycode(A + 8, 0))

// https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h
void main(int argc, char **argv)
{
    // init gtk
    gtk_init(&argc, &argv);
    GtkWidget *window = init_window();

    keyboardview_init(window);

    // number row
    add_button(41, 0, 0, 100 / 13.0);
    for (int i = 2; i <= 13; i++) {
        add_button(i, i-1, 0, 100 / 13.0);
    }
    
    // first row
    for (int i = 16; i <= 27; i++) {
        add_button(i, i-15, 1, 100 / 12.0);
    }

    // second row
    for (int i = 30; i <= 40; i++) {
       add_button(i, i-29, 2, 100 / 12.0);
    }
    add_button(43, 14, 2, 100 / 12.0);

    // third row
    for (int i = 44; i <= 53; i++) {
       add_button(i, i-43, 3, 100 / 10.0);
    }

    gtk_widget_show_all(window);

    // main event
    gtk_main();
}

