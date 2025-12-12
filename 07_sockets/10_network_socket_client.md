## Network Socket Client

Check input arguments, exit on error.
Open an INET, STREAM socket, exit on error.
Get the server host name, exit on error.
Configure and connect the socket to the server address and port, exit on error.
Display on screen that you are waiting for input and read a new text line from the keyboard.
Send the entered text to the socket.
Read a response from the socket and print it.
Close the socket.

### network-socket-client.c
```c
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#define BUF_SIZE 256
int main(int argc, char ** argv)
{
  // Arguments Check!
  if (argc != 3)
  {
    printf("Usage: %s <ip_address> <port_number>\n", argv[0]);
    return EXIT_FAILURE; // return -1;
  }

  // Socket Create
  int sock = socket(AF_INET, SOCK_STREAM, 0); 
  if (sock < 0)
  {
    printf("Socket Create Error: %d\n", errno);
    return EXIT_FAILURE; // return -1;
  }
  
  // Server IP Address
  struct in_addr addr;
  inet_aton(argv[1], &addr);
  struct hostent *server = gethostbyaddr(&addr, sizeof(addr), AF_INET);
  if (server == NULL)
  {
    printf("Host Not Found Error: %d\n", errno);
    return EXIT_FAILURE; // return -1;
  }
  
  // Server Address
  struct sockaddr_in serv_addr;
  memset((char *) &serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  strncpy((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
  serv_addr.sin_port = htons(atoi(argv[2]));
  
  // Socket Connect
  if (connect(sock, (const struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("Socket Connect Error: %d", errno);
    return EXIT_FAILURE; // -1
  }
  
  // Socket Write/Read
  printf("Write the message and press [Enter] to send:\n");
  char buf[BUF_SIZE];
  memset(buf, 0, BUF_SIZE);
  fgets(buf, BUF_SIZE-1, stdin);
  write(sock, buf, strlen(buf));
  memset(buf, 0, BUF_SIZE);
  read(sock, buf, BUF_SIZE-1);
  printf("Received: %s\n",buf);

  close(sock);
  return EXIT_SUCCESS; // return 0;
}
```
