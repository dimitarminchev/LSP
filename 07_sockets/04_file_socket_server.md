## File Socket Server

Open a Unix datagram socket, on error print a message and exit the program. 
Bind the socket to file **socket.file**, exit on error. 
Receive a message from the socket, exit on error. 
Print the message, close the socket and delete the socket file.

### file-socket-server.c
```c
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>

#define SOCK_NAME "socket.file"
#define BUF_SIZE 256

int main(int argc, char ** argv)
{
  int sock = socket(AF_UNIX, SOCK_DGRAM, 0);
  if(sock < 0)
  {
    printf("Error socket,\n");
    return EXIT_FAILURE;
  }

  struct sockaddr server, client;
  server.sa_family = AF_UNIX;
  strcpy(server.sa_data, SOCK_NAME);

  if(bind(sock, &server, strlen(server.sa_data) + sizeof(server.sa_family)) < 0)
  {
    printf("Error bind.\n");
    return EXIT_FAILURE;
  }

  char buf[BUF_SIZE];
  socklen_t len = sizeof(client);
  int bytes = recvfrom(sock, buf, sizeof(buf), 0, &client, &len);
  if(bytes < 0)
  {
    printf("Error recvfrom.\n");
    return EXIT_FAILURE;
  }
  buf[bytes] = '\0';
  client.sa_data[len] = 0;
  printf("Client: %s\n", buf);

  close(sock);
  unlink(SOCK_NAME);
  return EXIT_SUCCESS;
}
```
