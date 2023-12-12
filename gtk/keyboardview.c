#include <gtk/gtk.h>
#include <stdbool.h>
#include <linux/uinput.h>
#include <gui.h>

#define mask_shift (masks[KEY_LEFTSHIFT] || masks[KEY_RIGHTSHIFT])
#define mask_altgr masks[KEY_RIGHTALT]

#define MIN(a,b) (((a)<(b))?(a):(b))

GtkWidget *fixed;
GtkWidget *scrolled_window;
Button buttons[1024];
int _cur = 0;
static PangoFontDescription *fontdesc;

static int num_of_row = 0;
static int num_of_col = 0;

extern int *masks;
bool is_capslock_on = false;

static float find_item_percent(int col, int row){
    float m=0;
    for(int i=0;i<_cur;i++){
        if(buttons[i].col == col){
            if (buttons[i].row < row){
                m+=buttons[i].percent;
            }
        }
    }
    return m;
}

static int find_num_of_row(){
    int m=1;
    for(int i=0;i<_cur;i++){
        if(buttons[i].row+1 > m){
            m = buttons[i].row+1;
        }
    }
    return m;
}

static int find_num_of_col(){
    int m=1;
    for(int i=0;i<_cur;i++){
        if(buttons[i].col+1 > m){
            m = buttons[i].col+1;
        }
    }
    return m;
}


static void on_window_resized(GtkWidget *widget, GdkRectangle *allocation, gpointer user_data) {
    // Get the width of the window
    int window_width = allocation->width;
    int window_height = allocation->height;
    reallocate_buttons(window_width, window_height);
}
static int old_size = 10;
#define font_step 3
void reallocate_buttons(int window_width, int window_height){
    int new_size = font_step*((MIN(window_width/3, window_height)/22) /font_step);
    for(int i=0;i<_cur;i++){
        int button_width = (int)((buttons[i].percent * window_width) / 100);
        int button_height = (int) window_height / num_of_col;
        float new_x_percent = find_item_percent(buttons[i].col, buttons[i].row);
        int new_x = (int)((new_x_percent * window_width) / 100);
        int new_y = (window_height * buttons[i].col) / num_of_col;
        // printf("%d %f %d %d \n", i, new_x_percent, new_x, new_y);
        gtk_widget_set_size_request(buttons[i].widget, button_width, button_height);
        gtk_fixed_move(fixed, buttons[i].widget, new_x , new_y);
        if (old_size != new_size){
            pango_font_description_set_size(fontdesc, new_size* PANGO_SCALE);
            gtk_widget_override_font(buttons[i].widget, fontdesc);
        }
    }
    old_size = new_size;
}

void keyboardview_init(GtkWidget *window){
    fixed = gtk_fixed_new();
    fontdesc = pango_font_description_new();
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);
    gtk_container_add(GTK_CONTAINER(scrolled_window), fixed);
    gtk_scrolled_window_set_policy(scrolled_window, GTK_POLICY_EXTERNAL, GTK_POLICY_EXTERNAL);
    g_signal_connect(window, "size-allocate", G_CALLBACK(on_window_resized), NULL);
}

void add_button(int keycode, int row, int col, float percent){
    add_button_with_label(keycode, row, col, percent, get_label_from_keycode(keycode + 8, 0));
    buttons[_cur-1].update = TRUE;
    buttons[_cur-1].keycode = keycode;
}

void update_buttons(){
    char* label;
    bool update_request = FALSE;
    is_capslock_on = is_capslock_enabled();
    for(int i=0;i<_cur;i++){
        switch (masks[buttons[i].keycode]){
            case 1:
                gtk_widget_set_name(buttons[i].widget, "key_enabled");
                break;
            case 2:
                gtk_widget_set_name(buttons[i].widget, "key_lock");
                break;
            default:
                gtk_widget_set_name(buttons[i].widget, "key_normal");
                break;
        }
        if(buttons[i].keycode == KEY_CAPSLOCK){
            if(is_capslock_on){
                gtk_widget_set_name(buttons[i].widget, "key_enabled");
            }else{
                gtk_widget_set_name(buttons[i].widget, "key_normal");
            }
    
        }
        if (buttons[i].update){
            label = NULL;
            if(is_capslock_on){
                label = get_label_from_keycode(buttons[i].keycode + 8, 1);
            }else if(mask_shift && mask_altgr){
                label = get_label_from_keycode(buttons[i].keycode + 8, 3);
            }else if(mask_altgr){
                label = get_label_from_keycode(buttons[i].keycode + 8, 2);
            }else if(mask_shift){
                label = get_label_from_keycode(buttons[i].keycode + 8, 1);
            }else{
                label = get_label_from_keycode(buttons[i].keycode + 8, 0);
            }
            if(strcmp(buttons[i].label, label)!=0){
                gtk_button_set_label(buttons[i].widget, label);
                buttons[i].label = label;
                update_request = TRUE;
            }
        }
    }
    if(update_request){
        reload_window();
    }
}

void add_button_custom(int keycode, int row, int col, float percent, GtkWidget* widget){
    Button b;
    b.widget = widget;
    b.percent = percent;
    b.col = col;
    b.row = row;
    b.keycode = keycode;
    b.update = FALSE;
    gtk_widget_override_font(b.widget, fontdesc);
    buttons[_cur] = b;
    _cur++;
    num_of_row = find_num_of_row();
    num_of_col = find_num_of_col();
    gtk_fixed_put(GTK_FIXED(fixed), b.widget, 0, 0);
}
void add_button_with_label(int keycode, int row, int col, float percent, char* label){
    add_button_custom(keycode, row, col, percent, create_button(keycode, label));
    buttons[_cur-1].label = label;
}

void add_buttons(int row, int offset, int min, int max, float percent){
    for (int i = min; i <= max; i++) {
        add_button(i, i-(min - offset), row, percent);
    }
}
