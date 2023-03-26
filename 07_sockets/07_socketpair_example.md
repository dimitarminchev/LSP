## Пример за двойка сокети

Отворете двойка сокети, при грешка изведете съобщение и излезте от програмата. Създайте дъщерен процес. 

Родителския процес: затваря втория сокет, пише съобщение в първия сокет, чете отговора от първия сокет, опечатва полученото съобщение и затваря сокета.

Дъщерния процес: затваря първия сокет, чете съобщение от втория сокет, отпечатва получения текст, отговаря с подобаващо съобщение на втория сокет и го затваря.

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
    printf("Error sockpair.\n");
    return EXIT_FAILURE;
  }

  int pid = fork();
  if(pid < 0)
  {
    printf("Error fork.\n");
    return EXIT_FAILURE;
  }
  if(pid == 0)
  {
    write(sockets[0], MSG_HELLO, sizeof(MSG_HELLO));
    read(sockets[0], buf, sizeof(buf));
    printf("Process (pid = %i) send messagge: %s\n", getpid(), buf);
  }
  if(pid > 0)
  {
    read(sockets[1], buf, sizeof(buf));
    write(sockets[1], MSG_OK, sizeof(MSG_OK));
    printf("Process (pid = %i) send message: %s\n", getpid(), buf);
  }

  close(sockets[0]);
  close(sockets[1]);
  return EXIT_SUCCESS;
}
```
