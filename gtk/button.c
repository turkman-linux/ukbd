#include <gtk/gtk.h>
static void button_clicked(GtkWidget *button, gpointer data) {
    int number = (int)data;
    printf("%d\n",number);
}


GtkButton* create_button(int number, char* label){
    GtkButton* ret = gtk_button_new_with_label(label);
    g_signal_connect(ret, "clicked", G_CALLBACK(button_clicked), (gpointer)number);
    gtk_widget_show(ret);
    return ret;
}
