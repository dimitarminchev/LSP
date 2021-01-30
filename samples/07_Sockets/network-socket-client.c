#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

// Buffer up to 256
#define BUF_SIZE 256

// Main Program
int main(int argc, char ** argv)
{
  // Buffer up to 256
  char buf[BUF_SIZE];

  // Arguments check
  if (argc < 3)
  {
    fprintf(stderr,"usage: %s <hostname> <port_number>\n", argv[0]);
    return EXIT_FAILURE; // -1
  }

  // Socket Descriptor
  int port = atoi(argv[2]);
  int sock_client = socket(AF_INET, SOCK_STREAM, 0); // Network Socket using TCP protocol
  if (sock_client < 0)
  {
    printf("Error Socket Initialization! Err.No: %d", errno);
    return EXIT_FAILURE; // -1
  }

  // Server Address
  struct hostent *server;
  server = gethostbyname(argv[1]);
  if (server == NULL)
  {
    printf("Error Host Not Found!\n");
    return EXIT_FAILURE; // -1
  }

  // Initialize Socket Structure
  struct sockaddr_in serv_addr;
  memset((char *) &serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  strncpy((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
  serv_addr.sin_port = htons(port);

  // Socket Connect
  if (connect(sock_client, (const struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  //if (connect(sock_client, &serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("Error Socket Connet! Err.No: %d", errno);
    return EXIT_FAILURE; // -1
  }

  // Read text from the standart input in the buffer and send in the socket
  printf("Write the message and press [Enter] to send:\n");
  memset(buf, 0, BUF_SIZE);
  fgets(buf, BUF_SIZE-1, stdin);
  write(sock_client, buf, strlen(buf));
  memset(buf, 0, BUF_SIZE);
  read(sock_client, buf, BUF_SIZE-1);
  printf("Received: %s\n",buf);
  close(sock_client);

  return EXIT_SUCCESS; // 0
}
