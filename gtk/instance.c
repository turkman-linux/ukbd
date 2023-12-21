#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

int locked=0;
void single_instance(){
    if(locked){
        return;
    }
    int pid_file = open("/tmp/ukbd.pid", O_CREAT | O_RDWR, 0666);
    int rc = flock(pid_file, LOCK_EX | LOCK_NB);
    locked = 1;
    if(rc) {
        if(EWOULDBLOCK == errno){
            puts("Another instance is already running");
            exit(1);
        }
    }
}
