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

    // get button label using libX11
    GtkWidget *box_main = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box_main);

    // number row
    GtkWidget *box_num = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(box_num), BUTTON(41), TRUE, TRUE, 0);
    for (int i = 2; i <= 13; i++) {
        gtk_box_pack_start(GTK_BOX(box_num), BUTTON(i), TRUE, TRUE, 0);
    }
    gtk_box_pack_start(GTK_BOX(box_main), box_num, TRUE, TRUE, 0);

    // first row
    GtkWidget *box_first = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    for (int i = 16; i <= 27; i++) {
        gtk_box_pack_start(GTK_BOX(box_first), BUTTON(i), TRUE, TRUE, 0);
    }
    gtk_box_pack_start(GTK_BOX(box_main), box_first, TRUE, TRUE, 0);

    // second row
    GtkWidget *box_second = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    for (int i = 30; i <= 40; i++) {
        gtk_box_pack_start(GTK_BOX(box_second), BUTTON(i), TRUE, TRUE, 0);
    }
    gtk_box_pack_start(GTK_BOX(box_second), BUTTON(43), TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box_main), box_second, TRUE, TRUE, 0);

    // third row
    GtkWidget *box_third = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    for (int i = 44; i <= 53; i++) {
        gtk_box_pack_start(GTK_BOX(box_third), BUTTON(i), TRUE, TRUE, 0);
    }
    gtk_box_pack_start(GTK_BOX(box_main), box_third, TRUE, TRUE, 0);

    gtk_widget_show_all(window);

    // main event
    gtk_main();
}

