#ifndef _keyboard_h
#define _keyboard_h
#include <libukbd.h>
void send_key(int code);
char* socket_read();
void press_key(int code);
void release_key(int code);
int client_init();
int socket_init();
void client_send(char* buff);
void uinput_init();
void permission_init();



#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>


    
#define SERVER_SOCK_FILE "/dev/amogus"
#define SOCKET_BUFFER_LENGTH 4
#endif
