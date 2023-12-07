#include <gtk/gtk.h>
#include  <gui.h>
void main(int argc, char** argv){
    // init gtk
    gtk_init(&argc, &argv);
    GtkWidget *window = init_window();
    // get button label using libX11
    int code = 30; // X11 code + 8 = uinput code
    char* label = get_label_from_keycode(code+8,0);
    // add button (test stuff remove later)
    GtkButton* b = create_button(code, label);
    gtk_container_add(GTK_CONTAINER(window), (GtkWidget*)b);
    // main event
    gtk_main();
}
