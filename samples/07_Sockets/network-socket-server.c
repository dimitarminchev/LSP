#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Buffer up to 256
#define BUF_SIZE 256

// Main Program
int main(int argc, char ** argv)
{
  // Buffer up to 256
  char buf[BUF_SIZE];

  // Arguments Check
  if (argc < 2)
  {
    fprintf(stderr,"usage: %s <port_number>\n", argv[0]);
    return EXIT_FAILURE;
  }

  // Socket Initialization
  int sock_server = socket(AF_INET, SOCK_STREAM, 0); // SOCK_STREAM = TCP, SOCK+DGRAM = UDP
  if (sock_server < 0)
  {
    printf("Error creating socket! Err.No: %d\n", errno);
    return EXIT_FAILURE; // -1
  }

  // Socket Structure Initialization
  struct sockaddr_in serv_addr, cli_addr;
  memset((char *) &serv_addr, 0, sizeof(serv_addr));
  int port = atoi(argv[1]);
  serv_addr.sin_family = AF_INET; // NET
  serv_addr.sin_addr.s_addr = INADDR_ANY; // IP
  serv_addr.sin_port = htons(port); // PORT

  // Socket Binding
  if (bind(sock_server, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("Eror binding socket! Err.No: %d\n", errno);
    return EXIT_FAILURE; // -1
  }

  // Socket Listen
  listen(sock_server, 1); // Single Client
  int clen = sizeof(cli_addr);

  // Socket Accept Client Connection
  int sock_client = accept(sock_server, (struct sockaddr *) &cli_addr, &clen);
  if (sock_client < 0)
  {
    printf("Error accepting the client! Err.No: %d\n", errno);
    return EXIT_FAILURE; // -1
  }

  // Read and print the message from the Socket
  memset(buf, 0, BUF_SIZE);
  read(sock_client, buf, BUF_SIZE-1);
  buf[BUF_SIZE] = 0;
  printf("Received message: %s\n", buf);
  write(sock_client, "OK", 2);

  // Close Both Sockets
  close(sock_client);
  close(sock_server);

  return EXIT_SUCCESS; // 1
}
