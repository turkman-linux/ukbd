#include <gtk/gtk.h>
extern GtkWidget *window;
extern GtkWidget *scrolled_window;
GSettings *settings;

gboolean window_quit(GtkWidget* self, GdkEvent* event, gpointer user_data) {
    int new_width, new_height, new_x, new_y;
    gtk_window_get_size (window, &new_width, &new_height);
    gtk_window_get_position(window, &new_x, &new_y);
    g_settings_set_int(settings, "width", new_width);
    g_settings_set_int(settings, "height", new_height);
    g_settings_set_int(settings, "x", new_x);
    g_settings_set_int(settings, "y", new_y);
    return FALSE;
}


GtkWidget* init_window(){
    settings = g_settings_new("org.turkman.ukbd");
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_show_all(window);
    gtk_window_set_keep_above(GTK_WINDOW(window),TRUE);
    gtk_widget_set_size_request(GTK_WINDOW(window), 666,222);
    gtk_window_resize(window,
        g_settings_get_int(settings, "width"),
        g_settings_get_int(settings, "height")
    );
    gtk_window_move(window,
        g_settings_get_int(settings, "x"),
        g_settings_get_int(settings, "y")
    );
    gtk_window_set_accept_focus(GTK_WINDOW(window), FALSE);
    gtk_window_set_icon_name(window, "ukbd");

    g_signal_connect(window, "destroy", gtk_main_quit, NULL);
    g_signal_connect(window, "delete-event", G_CALLBACK(window_quit), NULL);
    
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    const gchar *cssData = " *, *>* { \
         padding: 0px; \
         margin: 0px; \
      }\
      window {\
         background: #1b1b1b; \
      }\
      #key_enabled { \
         background: #8e0000; \
         color: #ffffff; \
      } \
      #key_normal { \
         background: rgba(255, 255, 255, 0.2); \
         border: none; \
         color: #ffffff; \
      } \
      #key_lock { \
          background: #00008e; \
          color: #ffffff; \
      }";
    gtk_css_provider_load_from_data(cssProvider, cssData, -1, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    return window;
}

void reload_window(){
    gtk_widget_hide(scrolled_window);
    gtk_widget_show(scrolled_window);
}
