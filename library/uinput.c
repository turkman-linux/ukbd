#include <linux/uinput.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define O_RDONLY 00
#define O_WRONLY 01
#define O_RDWR 02

void emit(int fd, int type, int code, int val) {
    struct input_event ie;

    ie.type = type;
    ie.code = code;
    ie.value = val;
    ie.time.tv_sec = 0;
    ie.time.tv_usec = 0;

    ssize_t r = write(fd, & ie, sizeof(ie));
    printf("type: %d code: %d value: %d\n", type, code, val);
    if(r<0){
        perror("failed to write uinput");
    }
}

int fd;

void press_key(int code) {
    ioctl(fd, UI_SET_KEYBIT, code);
    emit(fd, EV_KEY, code, 1);
    emit(fd, EV_SYN, SYN_REPORT, 0);
}

void release_key(int code) {
    ioctl(fd, UI_SET_KEYBIT, code);
    emit(fd, EV_KEY, code, 0);
    emit(fd, EV_SYN, SYN_REPORT, 0);
}
void send_key(int code) {
    press_key(code);
    release_key(code);
}
void uinput_init(void) {
    struct uinput_setup usetup;

    fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    ioctl(fd, UI_SET_EVBIT, EV_KEY);
    ioctl(fd, UI_SET_KEYBIT, BTN_LEFT);
    ioctl(fd, UI_SET_KEYBIT, BTN_RIGHT);

    for (int i = 1; i <= 245; i++) {
        ioctl(fd, UI_SET_KEYBIT, i);
    }

    memset( & usetup, 0, sizeof(usetup));
    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x3131;
    usetup.id.product = 0x3131;
    usetup.id.version = 31;
    strcpy(usetup.name, "Amogus Keyboard");

    ioctl(fd, UI_DEV_SETUP, & usetup);
    ioctl(fd, UI_DEV_CREATE);

    sleep(1);
}
int uinput_destroy(void) {
    ioctl(fd, UI_DEV_DESTROY);
    close(fd);

    return 0;
}
