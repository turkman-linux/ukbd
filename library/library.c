#include <keyboard.h>
static int library_init = 0;

void ukbd_event(int code, int status){
    if(!library_init){
        client_init();
        library_init = 1;
    }
    int buf[3];
    buf[0] = status;
    buf[1] = code;
    buf[2] = 0;
    client_send(buf);

}

void ukbd_send(int code){
    ukbd_event(code, 1);
}

void ukbd_press(int code){
    ukbd_event(code, 2);
}

void ukbd_release(int code){
    ukbd_event(code, 3);
}

