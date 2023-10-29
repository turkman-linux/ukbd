#include <gtk/gtk.h>
GtkWidget* init_window(){
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_show_all(window);
    gtk_window_set_keep_above(GTK_WINDOW(window),TRUE);
    return window;
}
