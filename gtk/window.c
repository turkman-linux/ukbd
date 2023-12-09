#include <gtk/gtk.h>
extern GtkWidget *window;

GtkWidget* init_window(){
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_show_all(window);
    gtk_window_set_keep_above(GTK_WINDOW(window),TRUE);
    gtk_widget_set_size_request(GTK_WINDOW(window), 666,222);
    gtk_window_set_accept_focus(GTK_WINDOW(window), FALSE);
    
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    const gchar *cssData = "* { padding: 0px; margin: 0px; border-radius: 0px; }";
    gtk_css_provider_load_from_data(cssProvider, cssData, -1, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    return window;
}

void reload_window(){
    gint x, y;
    gtk_window_get_position(GTK_WINDOW(window), &x, &y);
    gtk_widget_hide(window);
    gtk_widget_show(window);
    gtk_window_move(window, x, y);
}
