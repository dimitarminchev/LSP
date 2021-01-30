#include <stdlib.h>
#include <unistd.h>
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
  // Buffer up to 256
  char buf[BUF_SIZE];

  // Create Socket
  int sock = socket(AF_UNIX, SOCK_DGRAM, 0);
  if (sock < 0)
  {
    perror("socket failed");
    return EXIT_FAILURE; // -1
  }

  // Socket Structure Initialization
  struct sockaddr srvr_name, rcvr_name;
  srvr_name.sa_family = AF_UNIX;
  strcpy(srvr_name.sa_data, SOCK_NAME);

  // Binding Socket
  if (bind(sock, &srvr_name, strlen(srvr_name.sa_data) + sizeof(srvr_name.sa_family)) < 0)
  {
    perror("bind failed");
    return EXIT_FAILURE; // -1
  }

  // Read from the Socket
  socklen_t namelen = sizeof(srvr_name);
  int bytes = recvfrom(sock, buf, sizeof(buf), 0, &rcvr_name, &namelen);
  if (bytes < 0)
  {
    perror("recvfrom failed");
    return EXIT_FAILURE; // -1
  }

  // Print the received Buffer
  buf[bytes] = 0;
  rcvr_name.sa_data[namelen] = 0;
  printf("Client sent: %s\n", buf);

  // Close the socket and remove the file
  close(sock);
  unlink(SOCK_NAME);

  return EXIT_SUCCESS; // 0
}
