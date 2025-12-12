## Network Socket Server

Check input arguments, exit on error.
Open an INET, STREAM socket, exit on error.
Initialize the **sockaddr_in** structure for the server.
Bind the socket to a port, exit on error.
Start listening, allow only one connection.
Accept a new connection, exit on error.
Read from the socket into a buffer.
Print the received message from the buffer.
Send "OK" to the socket.
Close the socket.

### network-socket-server.c
```c
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define BUF_SIZE 256
int main(int argc, char ** argv)
{
  // Arguments Check!
  if (argc != 2)
  {
    printf("Usage: %s <port_number>\n", argv[0]);
    return EXIT_FAILURE; // return -1;
  }
  
  // Socket Create
  int sock_server = socket(AF_INET, SOCK_STREAM, 0); 
  if (sock_server < 0)
  {
    printf("Socket Create Error: %d\n", errno);
    return EXIT_FAILURE; // return -1;
  }
  
  // Server Address
  struct sockaddr_in server_address;
  memset((char *) &server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET; 
  server_address.sin_addr.s_addr = htonl(INADDR_ANY); 
  server_address.sin_port = htons(atoi(argv[1])); 
  
  // Socket Bind 
  if (bind(sock_server, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
  {
    printf("Socket Bind Error: %d\n", errno);
    return EXIT_FAILURE; // return -1;
  }
  
  // Socket Listen
  if ((listen(sock_server, 5)) != 0) 
  {
        printf("Socket Listen Error: %d\n", errno);
		return EXIT_FAILURE; // return -1;
  }
  
  // Client Address
  struct sockaddr_in client_address;
  int len = sizeof(client_address);
  int sock_client = accept(sock_server, (struct sockaddr *) &client_address, &len);
  if (sock_client < 0)
  {
    printf("Accept Socket Error: %d\n", errno);
    return EXIT_FAILURE; // return -1;
  }
  
  // Socket Read/Write
  char buf[BUF_SIZE];
  memset(buf, 0, BUF_SIZE);
  read(sock_client, buf, BUF_SIZE-1);
  buf[BUF_SIZE] = '\0';
  printf("Received message: %s\n", buf);
  write(sock_client, "OK", 2);
  
  close(sock_client);
  close(sock_server);
  return EXIT_SUCCESS; // return 0;
}
```
