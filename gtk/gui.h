GtkWidget* init_window();
GtkButton* create_button(gint num, gchar* label);
GtkButton* create_toggle_button(gint number, gchar* label);

char* get_label_from_keycode(int code, int group);

void keyboardview_init(GtkWidget *window);
void add_buttons(int row, int offset, int min, int max, float percent);
void add_button(int keycode, int row, int col, float percent);
void add_button_with_label(int keycode, int row, int col, float percent, char* label);
void add_button_custom(int row, int col, float percent, GtkWidget* widget);
