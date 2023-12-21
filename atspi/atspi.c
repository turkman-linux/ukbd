#include <atspi/atspi.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static void on_event (const AtspiEvent *event, void *data) {
  system("ukbd-gtk &");
}

int main (int argc, gchar **argv) {
  AtspiEventListener *listener;
  atspi_init ();
  listener = atspi_event_listener_new (on_event, NULL, NULL);
  atspi_event_listener_register (listener, "object:state-changed:focused", NULL);
  atspi_event_main ();
  return 0;
}
