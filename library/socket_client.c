#include <keyboard.h>
int soc_client_fd;
struct sockaddr_un client_from;
struct sockaddr_un client_addr;

int client_init() {
    soc_client_fd = socket(PF_UNIX, SOCK_DGRAM, 0);
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sun_family = AF_UNIX;
    strncpy(client_addr.sun_path, SERVER_SOCK_FILE, sizeof(client_addr));

    bind(soc_client_fd, (struct sockaddr *) &client_addr, sizeof(client_addr));
    connect(soc_client_fd, (struct sockaddr *) &client_addr, sizeof(client_addr));

}
void client_send(char* buff){
    if (send(soc_client_fd, buff, strlen(buff) + 1, 0) == -1) {
        perror("send");
    }
}

void client_destroy() {
    unlink(SERVER_SOCK_FILE);
}
