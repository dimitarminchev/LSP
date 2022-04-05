## Файл сокет клиент

Отворете Unix сокет за дейтаграми, при грешка изведете съобщение и излезте от програмата. Настройте структурата за името на сървъра на сокета към **socket.file**. Изпратете съобщение до сървъра. Затворете сокета. 

### file-socket-client.c
```c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#define SOCK_NAME "socket.file"
#define BUF_SIZE 256
int main(int argc, char ** argv)
{
  char buf[BUF_SIZE];
  int sock = socket(AF_UNIX, SOCK_DGRAM, 0); // UDP
  if (sock < 0)
  {
    perror("socket failed");
    return EXIT_FAILURE; // -1
  }
  struct sockaddr srvr_name;
  srvr_name.sa_family = AF_UNIX;
  strcpy(srvr_name.sa_data, SOCK_NAME);
  strcpy(buf, "Hello, Unix file sockets!");
  sendto(sock, buf, strlen(buf), 0, &srvr_name,
  strlen(srvr_name.sa_data) + sizeof(srvr_name.sa_family));
  close(sock);
  return EXIT_SUCCESS; // 1
}
```