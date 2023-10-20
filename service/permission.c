#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include "keyboard.h"
#include <fcntl.h>

void permission_init(){
    struct group  *grp;
    grp = getgrnam("input");
    if (chown(SERVER_SOCK_FILE, 0, grp->gr_gid) == -1) {
        fprintf(stderr,"%s\n","Failed to set permissions!");
        exit(1);
    }
    chmod(SERVER_SOCK_FILE, S_IWUSR | S_IWGRP | S_IWOTH);
}
