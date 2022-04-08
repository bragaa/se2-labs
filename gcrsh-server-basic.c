#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

char *address;
short port;
int ss, //the server socket (the listening socket)
    cs; //the client socket (the socket created for an established connection)

struct sockaddr_in ss_addr, cs_addr; // the client and server socket addresses
int cs_addr_len;
int result;

int main(int argc, char *argv[])
{
  //read from the command line the listening address and port
  address = (char *)argv[1];
  port = (unsigned short)strtoul(argv[2], NULL, 0);

  // setup server socket. see definition of struct sockadr_in in ip(7) manpage
  ss_addr.sin_family = AF_INET;
  inet_aton(address, &ss_addr.sin_addr);
  ss_addr.sin_port = htons(port);

  // Following are the three steps required to bring up a server socket into the listening state: create, bind, and listen. In each step, we have to check the return code for errors.
  ss = socket(AF_INET, SOCK_STREAM, 0);
  if (ss < 0)
  {
    perror("Error creating the socket");
    exit(1);
  }

  result = bind(ss, (const struct sockaddr *)&ss_addr, sizeof(ss_addr));
  if (result < 0)
  {
    perror("Error binding the socket to port and address");
    exit(2);
  }

  result = listen(ss, 1);
  if (result < 0)
  {
    perror("Error on listening");
    exit(3);
  }

  printf("Welcome, I am Server with PID=%d,  listening on port %d and address %s.\nWaiting for incoming connections...\n", getpid(), port, address);

  // Continuously accept incoming connections.
  while (1)
  {
    cs = accept(ss, (struct sockaddr *)&cs_addr, &cs_addr_len);
    if (cs < 0)
    {
      perror("Error on accepting an incoming connection");
      printf("cs %d\n", cs);
      exit(4);
    }

    printf("Connection received from %s:%d. The socket created to handle the client has a descriptor no. %d\n", inet_ntoa(cs_addr.sin_addr), ntohs(cs_addr.sin_port), cs);
  }

  printf("Server is exiting");
  exit(0);
}
