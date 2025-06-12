#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>

#include <linux/uinput.h>

#include <libukbd.h>
#include <gui.h>

static gboolean on_button_release(GtkWidget *widget, GdkEventButton *event, gpointer user_data) {
    (void)user_data;
    if (event->type == GDK_BUTTON_RELEASE) {
        // Get mouse position
        int x = (int)event->x_root;
        int y = (int)event->y_root;

        printf("%d %d\n", x, y);

        // Hide the window
        gtk_widget_hide(widget);
        ukbd_send(BTN_RIGHT); 
    }
    return FALSE;
}

static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
    (void)widget;
    (void)data;
    // Set the background to half transparent
    cairo_set_source_rgba(cr, 0.31, 0, 0, 0);
    cairo_paint(cr);
    return FALSE;
}

static GtkWidget *window;

static void do_right_click(GtkWidget *widget, gpointer data){
    (void)widget;
    (void)data;
    // Create a new top-level window
    if(window == NULL){
        window = gtk_window_new(GTK_WINDOW_POPUP);
        gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
        gtk_window_set_type_hint(GTK_WINDOW(window), GDK_WINDOW_TYPE_HINT_DIALOG);
        gtk_window_set_keep_above(GTK_WINDOW(window), TRUE);
        gtk_window_set_default_size(GTK_WINDOW(window), gdk_screen_width(), gdk_screen_height());

        // Set the window to be transparent
        gtk_widget_set_app_paintable(window, TRUE);
        g_signal_connect(window, "draw", G_CALLBACK(on_draw), NULL);

        // Connect the button release event
        g_signal_connect(window, "button-release-event", G_CALLBACK(on_button_release), NULL);

        // Get the default screen
        GdkScreen *screen = gdk_screen_get_default();
        if (screen) {
            // Get the RGBA visual
            GdkVisual *visual = gdk_screen_get_rgba_visual(screen);
            if (visual != NULL && gdk_screen_is_composited(screen)) {
                // Set the visual for the window
                gtk_widget_set_visual(window, visual);
            }
        }

        
    }

    // Show the window
    gtk_widget_show_all(window);
}

GtkButton *mouse_selector(){
    GtkButton *but = (GtkButton*)gtk_button_new();
    GtkImage* img = (GtkImage*)gtk_image_new_from_icon_name("ukbd-mouse", GTK_ICON_SIZE_BUTTON);
    gtk_container_add((GtkContainer*)but, (GtkWidget*)img);
    g_signal_connect(but, "clicked", G_CALLBACK(do_right_click), NULL);
    return but;
}
