#include <stdio.h>
#include <linux/uinput.h>
#include <linux/types.h>
#include <keyboard.h>

int _start() {
    if(getuid() != 0){
        puts("You must be root!");
        exit(1);
    }
    if (access("/dev/uinput", F_OK ) != 0 ) {
        puts("Please enable uinput kernel module!");
        exit(2);
    }
    socket_init();
    uinput_init();
    while (1) {
        int* data = socket_read();
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
