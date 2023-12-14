#include <gtk/gtk.h>
#include <linux/uinput.h>
#include <stdbool.h>
#include <libukbd.h>
#include <gui.h>


int *masks;

bool update_required = false;


static void button_clicked(GtkWidget *button, gpointer data) {
    int number = (int)data;
    printf("Normal: %d\n",number);
    ukbd_send(number);
    for(int i=0;i<255;i++){
        if(masks[i] == 1){
            masks[i] = 0;
            printf("release %d\n", i);
            ukbd_release(i);
        }
    }
    if(update_required){
        update_buttons();
    }
    if(number == KEY_CAPSLOCK){
        g_timeout_add(300, update_buttons, NULL);
    }
    update_required = false;
}

GtkButton* create_button(int number, char* label){
    GtkButton* ret = gtk_button_new_with_label(label);
    g_signal_connect(ret, "clicked", G_CALLBACK(button_clicked), (gpointer)number);
    gtk_widget_show(ret);
    return ret;
}

static void toggle_button_clicked(GtkWidget *button, gpointer data) {
    int number = (int)data;
    /*
      0 = off
      1 = on
      2 =  always on
    */
    switch(masks[number]){
        case 0:
            masks[number] = 1;
            printf("press %d\n", number);
            ukbd_press(number);
            break;
        case 1:
            masks[number] = 2;
            printf("press %d\n", number);
            ukbd_press(number);
            break;
        default:
            masks[number] = 0;
            printf("release %d\n", number);
            ukbd_release(number);
            break;
    }
    update_buttons();
    update_required = true;
}


GtkButton* create_toggle_button(int number, char* label){
    if(masks == NULL){
        masks = (int*)calloc(255, sizeof(int));
    }
    GtkButton* ret = gtk_button_new_with_label(label);
    g_signal_connect(ret, "clicked", G_CALLBACK(toggle_button_clicked), (gpointer)number);
    gtk_widget_show(ret);
    return ret;
}


