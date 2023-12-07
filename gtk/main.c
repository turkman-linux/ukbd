#include <gtk/gtk.h>
#include  <gui.h>
#define BUTTON(A) create_button(A, get_label_from_keycode(A+8, 0))

void main(int argc, char** argv){
    // init gtk
    gtk_init(&argc, &argv);
    GtkWidget *window = init_window();
    // get button label using libX11
    int code = 30; // X11 code + 8 = uinput code
    char* label = get_label_from_keycode(code+8,0);
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    int row = 0, col = 0;
    // number row
    gtk_grid_attach(GTK_GRID(grid), BUTTON(41), 0, 0, 1, 1);
    for(int i=2;i<=13;i++){
        gtk_grid_attach(GTK_GRID(grid), BUTTON(i), i-1, 0, 1, 1);
    }// first row
    for(int i=16;i<=27;i++){
        gtk_grid_attach(GTK_GRID(grid), BUTTON(i), i-16, 1, 1, 1);
    }// second row
    for(int i=30;i<=40;i++){
        gtk_grid_attach(GTK_GRID(grid), BUTTON(i), i-30, 2, 1, 1);
    }
    gtk_grid_attach(GTK_GRID(grid), BUTTON(43), 11, 2, 1, 1);
    // third row
    for(int i=44;i<=53;i++){
        gtk_grid_attach(GTK_GRID(grid), BUTTON(i), i-44, 3, 1, 1);
    }
    gtk_widget_show_all(window);
    // main event
    gtk_main();
}
