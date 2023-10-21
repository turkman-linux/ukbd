#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include "keyboard.h"
#include <fcntl.h>

void permission_init() {
    chmod(SERVER_SOCK_FILE, S_IWUSR | S_IWGRP | S_IWOTH);
}
