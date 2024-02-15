#include <gtk/gtk.h>
#include <gui.h>
#include <keyboard.h>

GtkWidget *window;

extern GSettings * settings;

// https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h
void main(int argc, char **argv) {
    single_instance();
    // force use X11 backend
    setenv("GDK_BACKEND", "x11", 1);
    // force scale 1
    setenv("GDK_SCALE", "1", 1);
    setenv("GDK_DPI_SCALE", "1", 1);
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

    #define LAYOUT_FULL 0
    #define LAYOUT_MINI 1


    switch(g_settings_get_int(settings, "layout")){
        case LAYOUT_FULL:
            build_layout_full();
            break;
        case LAYOUT_MINI:
            build_layout_mini();
            break;
    }


    gtk_widget_show_all(window);
    update_buttons();
    // trigger resize event
    reallocate_buttons(666, 222);

    // main event
    gtk_main();
}

