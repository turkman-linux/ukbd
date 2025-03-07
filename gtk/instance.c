#include <sys/file.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>


void single_instance(){
int pid_file = open("/tmp/ukbd.pid", O_CREAT | O_RDWR, 0666);
if (pid_file == -1) {
    perror("Error opening pid file");
    exit(1);
}

int rc = flock(pid_file, LOCK_EX | LOCK_NB);
if (rc == -1) {
    if (errno == EWOULDBLOCK) {
        perror("Another instance is already running");
        exit(1);
    } else {
        perror("Error locking pid file");
        exit(1);
    }
}}
