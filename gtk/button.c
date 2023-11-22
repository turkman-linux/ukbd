#include <gtk/gtk.h>
typedef struct _b_dat {
    int num;
} button_data;



void button_event(GtkButton* w, gpointer f){
    button_data* dat = f;
    g_print("%d\n", dat->num);
    dat->num++;
}

GtkButton* create_button(int number, char* label){
    GtkButton* ret = gtk_button_new_with_label(label);
    button_data dat;
    g_print("%p\n", dat.num);
    g_signal_connect(ret, "clicked", G_CALLBACK(button_event), &dat);
    dat.num = number;
    gtk_widget_show(ret);
    return ret;
}
