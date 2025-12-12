## Socket Pair Example

Open a socket pair, on error print a message and exit the program. 

Create a child process, on error print a message and exit the program.

Parent process: waits to receive a message by reading from the first socket, then sends a response with an appropriate reply message by writing to the first socket.

Child process: sends a message by writing to the second socket and waits to receive a reply message by reading from the second socket.

Finally, close the socket pair.

### socket-pair.c
```c
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>

#define MSG_HELLO "HELLO"
#define MSG_OK "OK"
#define BUF_SIZE 256

int main(int argc, char ** argv)
{
  char buf[BUF_SIZE];

  int sockets[2];
  if(socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) < 0)
  {
    printf("Error socketpair.\n");
    return EXIT_FAILURE;
  }

  int pid = fork();
  if(pid < 0)
  {
    printf("Error fork.\n");
    return EXIT_FAILURE;
  }
  if(pid > 0)
  {
    read(sockets[0], buf, sizeof(buf));
    write(sockets[0], MSG_OK, sizeof(MSG_OK));
    printf("Process (pid = %i) send message: %s\n", getpid(), buf);
  }
  if(pid == 0)
  {
    write(sockets[1], MSG_HELLO, sizeof(MSG_HELLO));
    read(sockets[1], buf, sizeof(buf));
    printf("Process (pid = %i) send messagge: %s\n", getpid(), buf);
  }

  close(sockets[0]);
  close(sockets[1]);
  return EXIT_SUCCESS;
}
```
