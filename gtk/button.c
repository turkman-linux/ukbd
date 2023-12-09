#include <gtk/gtk.h>
#include <linux/uinput.h>
#include <stdbool.h>

static void button_clicked(GtkWidget *button, gpointer data) {
    int number = (int)data;
    printf("Normal: %d\n",number);
}
bool ctrl_mask = FALSE;

GtkButton* create_button(int number, char* label){
    GtkButton* ret = gtk_button_new_with_label(label);
    g_signal_connect(ret, "clicked", G_CALLBACK(button_clicked), (gpointer)number);
    gtk_widget_show(ret);
    return ret;
}


static void toggle_button_clicked(GtkWidget *button, gpointer data) {
    int number = (int)data;
    if(number == KEY_LEFTCTRL){
        ctrl_mask = ! ctrl_mask;
    }
    printf("Toggle: %d\n",number);
}


GtkButton* create_toggle_button(int number, char* label){
    GtkButton* ret = gtk_button_new_with_label(label);
    g_signal_connect(ret, "clicked", G_CALLBACK(toggle_button_clicked), (gpointer)number);
    gtk_widget_show(ret);
    return ret;
}


