#include <atspi/atspi.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>


static void on_event (const AtspiEvent *event, void *data){
  AtspiAccessible *application = NULL;
  gchar *app_name = NULL;

  if (event->source == NULL){
    return;
  }

  /* We only care about focus/selection gain */
  if (!event->detail1){
    return;
  }

  application = atspi_accessible_get_application (event->source, NULL);
  if (application == NULL){
    return;
  }

  system("/usr/bin/ukbd-gtk &");

}

int main (int argc, gchar **argv) {
  GSettings *settings = g_settings_new("org.turkman.ukbd");
  if(!g_settings_get_boolean(settings, "atspi")){
      return 0;
  }

  AtspiEventListener *listener;
  atspi_init ();
  listener = atspi_event_listener_new (on_event, NULL, NULL);
  atspi_event_listener_register (listener, "object:state-changed:focused", NULL);
  atspi_event_main ();
  return 0;
}
