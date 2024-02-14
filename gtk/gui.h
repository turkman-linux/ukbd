#include <stdbool.h>
#include <gtk/gtk.h>

GtkWidget* init_window();
GtkButton* create_button(gint num, gchar* label);
GtkButton* create_toggle_button(gint number, gchar* label);

char* get_label_from_keycode(int code, int group);
bool is_capslock_enabled();

typedef struct _object {
    GtkWidget *widget;
    GtkWidget *image;
    int keycode;
    int col;
    int row;
    char* label;
    float percent;
    bool update;
} Button;

void keyboardview_init(GtkWidget *window);
void button_clicked(GtkWidget *button, gpointer data);

void add_buttons(int row, int offset, int min, int max, float percent);
void add_button(int keycode, int row, int col, float percent);
void add_button_with_label(int keycode, int row, int col, float percent, char* label);
void add_button_with_image(int keycode, int row, int col, float percent, char* name);
void add_button_custom(int keycode, int row, int col, float percent, GtkWidget* widget);

void reload_window();
void update_buttons();

void single_instance();

// X11 code + 8 = uinput code
#define BUTTON(A) create_button(A, get_label_from_keycode(A + 8, 0))
// keyboard dimensin to percent
#define l(A) A*100/30.5
