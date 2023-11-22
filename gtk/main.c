#include <gtk/gtk.h>
#include  <gui.h>
void main(int argc, char** argv){
    // init gtk
    gtk_init(&argc, &argv);
    GtkWidget *window = init_window();
    // add button (test stuff remove later)
    GtkButton* b = create_button(30,"A");
    gtk_container_add(GTK_CONTAINER(window), (GtkWidget*)b);
    // main event
    gtk_main();
}
