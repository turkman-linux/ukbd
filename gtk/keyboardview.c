#include <gtk/gtk.h>
#include <stdbool.h>
#include <gui.h>

typedef struct _object {
    GtkWidget *widget;
    int keycode;
    int col;
    int row;
    float percent;
    bool update;
} Button;

GtkWidget *fixed;
static Button buttons[1024];
static int _cur = 0;

static int num_of_row = 0;
static int num_of_col = 0;


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

void reallocate_buttons(int window_width, int window_height){
    for(int i=0;i<_cur;i++){
        int button_width = (int)((buttons[i].percent * window_width) / 100);
        int button_height = (int) window_height / num_of_col;
        float new_x_percent = find_item_percent(buttons[i].col, buttons[i].row);
        int new_x = (int)((new_x_percent * window_width) / 100);
        int new_y = (window_height * buttons[i].col) / num_of_col;
        // printf("%d %f %d %d \n", i, new_x_percent, new_x, new_y);
        gtk_widget_set_size_request(buttons[i].widget, button_width, button_height);
        gtk_fixed_move(fixed, buttons[i].widget, new_x , new_y);
    }
}

void keyboardview_init(GtkWidget *window){
    fixed = gtk_fixed_new();
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);
    gtk_container_add(GTK_CONTAINER(scrolled_window), fixed);
    g_signal_connect(window, "size-allocate", G_CALLBACK(on_window_resized), NULL);
}

void add_button(int keycode, int row, int col, float percent){
    add_button_with_label(keycode, row, col, percent, get_label_from_keycode(keycode + 8, 0));
    buttons[_cur-1].update = TRUE;
}

void add_button_custom(int row, int col, float percent, GtkWidget* widget){
    Button b;
    b.widget = widget;
    b.percent = percent;
    b.col = col;
    b.row = row;
    b.update = FALSE;
    buttons[_cur] = b;
    _cur++;
    num_of_row = find_num_of_row();
    num_of_col = find_num_of_col();
    gtk_fixed_put(GTK_FIXED(fixed), b.widget, 0, 0);
}
void add_button_with_label(int keycode, int row, int col, float percent, char* label){
    add_button_custom(row, col, percent, create_button(keycode, label));
}

void add_buttons(int row, int offset, int min, int max, float percent){
    for (int i = min; i <= max; i++) {
        add_button(i, i-(min - offset), row, percent);
    }
}
