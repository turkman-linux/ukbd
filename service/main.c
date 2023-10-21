#include <stdio.h>
#include <linux/uinput.h>
#include <linux/types.h>
#include <keyboard.h>

int _start() {
    socket_init();
    uinput_init();
    permission_init();
    while (1) {
        char * data = socket_read();
        int status = data[0];
        int key = data[1];
        if (status == 1){
            send_key(key);
        }else if (status == 2){
            press_key(key);
        }else if (status == 3){
            release_key(key);
        }
    }
}
