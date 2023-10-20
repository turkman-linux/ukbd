#include <stdio.h>
#include <linux/uinput.h>
#include <linux/types.h>
#include "keyboard.h"
int main(){
    socket_init();
    uinput_init();
    permission_init();
    while(1){
        char* data = socket_read();
      	printf ("DEBUG: %s\n", data);
      	for(int i=0;data[i];i++){
  	      	send_key((__u16)data[i]);
      	}
    }
}
