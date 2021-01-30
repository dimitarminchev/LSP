#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

// Messages and buffer size
#define STR1 "How are you?"
#define STR2 "I'm ok, thank you."
#define BUF_SIZE 1024

// Main Program
int main(int argc, char ** argv)
{
  // Init sockets array and buffer
  int sockets[2];
  char buf[BUF_SIZE]; // up to 1024

  // Create Socket Pairs
  if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) < 0) // TCP
  {
    perror("socketpair() failed");
    return EXIT_FAILURE; // -1
  }

  // Clonning
  int pid = fork();
  if (pid != 0)
  {
    // Parent process working
    close(sockets[1]);
    write(sockets[0], STR1, sizeof(STR1));
    read(sockets[0], buf, sizeof(buf));
    printf("%s\n", buf);
    close(sockets[0]);
  }
  else
  {
    // Child process working
    close(sockets[0]);
    read(sockets[1], buf, sizeof(buf));
    printf("%s\n", buf);
    write(sockets[1], STR2, sizeof(STR2));
    close(sockets[1]);
  }

  return EXIT_SUCCESS; // 0
}
