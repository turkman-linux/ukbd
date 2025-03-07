#include <gtk/gtk.h>
#include <linux/uinput.h>
#include <stdbool.h>
#include <libukbd.h>
#include <gui.h>


int *masks;

bool update_required = false;


void button_clicked(GtkWidget *button, gpointer data) {
    int number = (int)data;
    // printf("Normal: %d\n",number);
    for(int i=0;i<255;i++){
        if(masks[i] > 0){
            // printf("release %d\n", i);
            ukbd_press(i);
        }
    }
    ukbd_press(number);
    for(int i=0;i<255;i++){
        if(masks[i] == 1){
            masks[i] = 0;
            // printf("release %d\n", i);
            ukbd_release(i);
        }
    }
    ukbd_release(number);
    if(update_required){
        update_buttons();
    }
    if(number == KEY_CAPSLOCK){
        g_timeout_add(300, (GSourceFunc)update_buttons, NULL);
    }
    update_required = false;
}

void button_pressed(GtkWidget *button, gpointer data) {
    gtk_widget_set_name(button, "key_active");
    button_clicked(button, data);
}

void button_released_event(gpointer *data) {
    gtk_widget_set_name((GtkWidget*)data, "key_normal");
}
void button_released(GtkWidget *button, gpointer data) {
        g_timeout_add(300, (GSourceFunc)button_released_event, button);
}

GtkButton* create_button(int number, char* label){
    GtkButton* ret = (GtkButton*) gtk_button_new_with_label(label);
    g_signal_connect(ret, "pressed", G_CALLBACK(button_pressed), (gpointer)number);
    g_signal_connect(ret, "released", G_CALLBACK(button_released), (gpointer)number);
    gtk_widget_show((GtkWidget*)ret);
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
            //printf("press %d\n", number);
            break;
        case 1:
            masks[number] = 2;
            //printf("press %d\n", number);
            break;
        default:
            masks[number] = 0;
            ukbd_release(number);
            //printf("release %d\n", number);
            break;
    }
    update_buttons();
    update_required = true;
}


GtkButton* create_toggle_button(int number, char* label){
    if(masks == NULL){
        masks = (int*)calloc(255, sizeof(int));
    }
    GtkButton* ret = (GtkButton*) gtk_button_new_with_label(label);
    g_signal_connect(ret, "clicked", G_CALLBACK(toggle_button_clicked), (gpointer)number);
    gtk_widget_show((GtkWidget*)ret);
    return ret;
}


