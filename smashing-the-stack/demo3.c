#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>


#include <err.h>

#include <netdb.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/socket.h>

#define portstr "12345"


struct sockaddr_in ss_addr;
struct sockaddr_in cs_addr; // the client and server socket addresses 
char* address;
int port;

void copy(char *str) {
  char buffer[128];
  strcpy(buffer, str);
  printf("%s\n", buffer);
}

int main(int argc, char **argv) {
    static char input[1024];

    int sockfd;

    address = argv[1];
	port = (unsigned short) strtoul(argv[2], NULL, 0);
    
    printf("Hello, my PID is %d\n", getpid());

	ss_addr.sin_family = AF_INET;
	inet_aton(address, &ss_addr.sin_addr);
	ss_addr.sin_port = htons(port);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err(1, "socket");
    if (bind(sockfd, (const struct sockaddr*) &ss_addr, sizeof(ss_addr)))
        err(1, "bind");
    if (listen(sockfd, 5))
        err(1, "listen");

    int cltfd = accept(sockfd, NULL, NULL);
    if (cltfd<0) {
        err(1, "accept");
    } else {
        printf("Hello!\n");
    }

    while (read(cltfd, input, 1024) > 0) {
        copy(input);
        printf("%s", input);
    }
    return 0;
}