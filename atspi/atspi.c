#include <atspi/atspi.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>

GSettings *settings;

static void on_event(const AtspiEvent *event, void *data) {
    if (event == NULL || event->source == NULL) {
        return;
    }

    if (!event->detail1) {
        return;
    }

    AtspiAccessible *application = atspi_accessible_get_application(event->source, NULL);
    if (application == NULL) {
        fprintf(stderr, "Failed to get application from event source\n");
        return;
    }
    // https://docs.gtk.org/atspi2/enum.Role.html
    AtspiRole role = atspi_accessible_get_role(event->source, NULL);
    if (!(role == ATSPI_ROLE_PASSWORD_TEXT ||
          role == ATSPI_ROLE_TEXT ||
          role == ATSPI_ROLE_ENTRY ||
          role == ATSPI_ROLE_FORM)){
        return;
    }

    if (!settings || !g_settings_get_boolean(settings, "atspi")) {
        fprintf(stderr, "AT-SPI integration not enabled or settings not found\n");
        return;
    }

    // Check if the event is focus change event
    if (strcmp(event->type, "object:state-changed:focused") == 0) {
        if (fork() == 0) {
            // Execute the virtual keyboard program
            execl("/usr/bin/ukbd-gtk", "ukbd-gtk", NULL);
            exit(0);
        }
    }
}

int main(int argc, gchar **argv) {
    settings = g_settings_new("org.turkman.ukbd");

    atspi_init();
    AtspiEventListener *listener = atspi_event_listener_new(on_event, NULL, NULL);
    if (!listener) {
        fprintf(stderr, "Failed to create event listener\n");
        g_object_unref(settings);
        return 1;
    }

    // Register for focus and selection change events
    atspi_event_listener_register(listener, "object:state-changed:focused", NULL);

    // Enter the main event loop
    atspi_event_main();

    g_object_unref(settings);
    return 0;
}

