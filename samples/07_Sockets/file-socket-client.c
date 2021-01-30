#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

// Unix File Socket
#define SOCK_NAME "socket.soc"
#define BUF_SIZE 256

// Main Program
int main(int argc, char ** argv)
{
  // Buffer up to 356
  char buf[BUF_SIZE];

  // Create Socket
  int sock = socket(AF_UNIX, SOCK_DGRAM, 0); // UDP
  if (sock < 0)
  {
    perror("socket failed");
    return EXIT_FAILURE; // -1
  }

  // Socket Inititialization
  struct sockaddr srvr_name;
  srvr_name.sa_family = AF_UNIX;
  strcpy(srvr_name.sa_data, SOCK_NAME);
  strcpy(buf, "Hello, Unix file sockets!");

  // Send the buffer and close the socket
  sendto(sock, buf, strlen(buf), 0, &srvr_name,
  strlen(srvr_name.sa_data) + sizeof(srvr_name.sa_family));
  close(sock);

  return EXIT_SUCCESS; // 1
}
