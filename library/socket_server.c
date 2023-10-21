#include <keyboard.h>
int soc_server_fd;
struct sockaddr_un server_from;
struct sockaddr_un server_addr;
socklen_t fromlen;
int socket_init() {
    int ret;
    int ok = 1;
    int len;
    fromlen = sizeof(server_from);

    if ((soc_server_fd = socket(PF_UNIX, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        ok = 0;
    }

    bind(soc_server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    if (ok) {
        memset( & server_from, 0, sizeof(server_addr));
        server_from.sun_family = AF_UNIX;
        strcpy(server_from.sun_path, SERVER_SOCK_FILE);
        unlink(SERVER_SOCK_FILE);
        if (bind(soc_server_fd, (struct sockaddr * ) & server_from, sizeof(server_from)) < 0) {
            perror("bind");
            ok = 0;
        }
    }

}
int socket_destroy() {

    if (soc_server_fd >= 0) {
        close(soc_server_fd);
    }

    return 0;
}

char * socket_read() {
    char * buff = malloc(SOCKET_BUFFER_LENGTH * sizeof(char));
    recvfrom(soc_server_fd, buff, SOCKET_BUFFER_LENGTH, 0, (struct sockaddr * ) & server_from, & fromlen);
    return buff;
}
