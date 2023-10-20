#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SERVER_SOCK_FILE "/dev/input/amogus"
int soc_fd;
struct sockaddr_un from;
struct sockaddr_un addr;
socklen_t fromlen;
int socket_init() {
	int ret;
	int ok = 1;
	int len;
	fromlen = sizeof(from);

	if ((soc_fd = socket(PF_UNIX, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		ok = 0;
	}

	if (ok) {
		memset(&addr, 0, sizeof(addr));
		addr.sun_family = AF_UNIX;
		strcpy(addr.sun_path, SERVER_SOCK_FILE);
		unlink(SERVER_SOCK_FILE);
		if (bind(soc_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
			perror("bind");
			ok = 0;
		}
	}

}
int socket_destroy() {

	if (soc_fd >= 0) {
		close(soc_fd);
	}

	return 0;
}

char* socket_read(){
    char *buff = malloc(8192*sizeof(char));
    recvfrom(soc_fd, buff, 8192, 0, (struct sockaddr *)&from, &fromlen);
    return buff;
}
