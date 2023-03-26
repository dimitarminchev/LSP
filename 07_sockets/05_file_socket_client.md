## Файл сокет клиент

Отворете Unix сокет за дейтаграми, при грешка изведете съобщение и излезте от програмата. 
Настройте структурата за името на сървъра на сокета към **socket.file**. 
Изпратете съобщение до сървъра и затворете сокета. 

### file-socket-client.c
```c
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>

#define SOCK_NAME "socket.file"
#define BUF_SIZE 256

int main(int argc, char ** argv)
{
  int sock = socket(AF_UNIX, SOCK_DGRAM, 0);
  if(sock < 0)
  {
    printf("Error socket.\n");
    return EXIT_FAILURE;
  }

  struct sockaddr server;
  server.sa_family = AF_UNIX;
  strcpy(server.sa_data, SOCK_NAME);

  char buf[BUF_SIZE];
  strcpy(buf, "HELLO");
  sendto(sock, buf, strlen(buf), 0, &server, strlen(server.sa_data) + sizeof(server.sa_family));

  close(sock);
  return EXIT_SUCCESS;
}
```
