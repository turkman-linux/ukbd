#include <gtk/gtk.h>
#include  <gui.h>
void main(int argc, char** argv){
    // init gtk
    gtk_init(&argc, &argv);
    GtkWidget *window = init_window();
    // main event
    gtk_main();
}
