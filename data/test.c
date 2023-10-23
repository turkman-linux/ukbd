#include <libukbd.h>
void main(){
    ukbd_send(33);
    ukbd_press(35);
    ukbd_release(35);
}