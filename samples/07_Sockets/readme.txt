1. Файл сокет сървър
file-socket-server.c
--
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#define SOCK_NAME "socket.soc"
#define BUF_SIZE 256
int main(int argc, char ** argv)
{
  struct sockaddr srvr_name, rcvr_name;
  char buf[BUF_SIZE];
  int sock = socket(AF_UNIX, SOCK_DGRAM, 0);
  if (sock < 0)
  {
    perror("socket failed");
    return EXIT_FAILURE;
  }
  srvr_name.sa_family = AF_UNIX;
  strcpy(srvr_name.sa_data, SOCK_NAME);
  if (bind(sock, &srvr_name, strlen(srvr_name.sa_data) + sizeof(srvr_name.sa_family)) < 0)
  {
    perror("bind failed");
    return EXIT_FAILURE;
  }
  socklen_t namelen = sizeof(srvr_name);
  int bytes = recvfrom(sock, buf, sizeof(buf), 0, &rcvr_name, &namelen);
  if (bytes < 0)
  {
    perror("recvfrom failed");
    return EXIT_FAILURE;
  }
  buf[bytes] = 0;
  rcvr_name.sa_data[namelen] = 0;
  printf("Client sent: %s\n", buf);
  close(sock);
  unlink(SOCK_NAME);
}

2. Файл сокет клиент
file-socket-client.c
---
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#define SOCK_NAME "socket.soc"
#define BUF_SIZE 256
int main(int argc, char ** argv)
{
  char buf[BUF_SIZE];
  struct sockaddr srvr_name;
  int sock = socket(AF_UNIX, SOCK_DGRAM, 0);
  if (sock < 0)
  {
    perror("socket failed");
    return EXIT_FAILURE;
  }
  srvr_name.sa_family = AF_UNIX;
  strcpy(srvr_name.sa_data, SOCK_NAME);
  strcpy(buf, "Hello, Unix sockets!");
  sendto(sock, buf, strlen(buf), 0, &srvr_name,
  strlen(srvr_name.sa_data) + sizeof(srvr_name.sa_family));
  close(sock);
}

3. Двойка сокети
socket-pair.c
---
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#define STR1 "How are you?"
#define STR2 "I'm ok, thank you."
#define BUF_SIZE 1024
int main(int argc, char ** argv)
{
  int sockets[2];
  char buf[BUF_SIZE];

  if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) < 0)
  {
    perror("socketpair() failed");
    return EXIT_FAILURE;
  }
  int pid = fork();
  if (pid != 0)
  {
    close(sockets[1]);
    write(sockets[0], STR1, sizeof(STR1));
    read(sockets[0], buf, sizeof(buf));
    printf("%s\n", buf);
    close(sockets[0]);
  }
  else
  {
    close(sockets[0]);
    read(sockets[1], buf, sizeof(buf));
    printf("%s\n", buf);
    write(sockets[1], STR2, sizeof(STR2));
    close(sockets[1]);
  }
}

4. Мрежов сокет сървър
network-socket-server.c
---
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
  char buf[BUF_SIZE];
  struct sockaddr_in serv_addr, cli_addr;
  if (argc < 2)
  {
    fprintf(stderr,"usage: %s <port_number>\n", argv[0]);
    return EXIT_FAILURE;
  }
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (socket < 0)
  {
    printf("socket() failed: %d\n", errno);
    return EXIT_FAILURE;
  }
  memset((char *) &serv_addr, 0, sizeof(serv_addr));
  int port = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port);
  if (bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("bind() failed: %d\n", errno);
    return EXIT_FAILURE;
  }
  listen(sock, 1);
  int clen = sizeof(cli_addr);
  int newsock = accept(sock, (struct sockaddr *) &cli_addr, &clen);
  if (newsock < 0)
  {
    printf("accept() failed: %d\n", errno);
    return EXIT_FAILURE;
  }
  memset(buf, 0, BUF_SIZE);
  read(newsock, buf, BUF_SIZE-1);
  buf[BUF_SIZE] = 0;
  printf("MSG: %s\n", buf);
  write(newsock, "OK", 2);
  close(newsock);
  close(sock);
}

5. Мрежов сокет клиент
network-socket-cient.c
---
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
#define BUF_SIZE 256
int main(int argc, char ** argv)
{
  struct sockaddr_in serv_addr;
  struct hostent *server;
  char buf[BUF_SIZE];
  if (argc < 3)
  {
    fprintf(stderr,"usage: %s <hostname> <port_number>\n", argv[0]);
    return EXIT_FAILURE;
  }
  int port = atoi(argv[2]);
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
  {
    printf("socket() failed: %d", errno);
    return EXIT_FAILURE;
  }
  server = gethostbyname(argv[1]);
  if (server == NULL)
  {
    printf("Host not found\n");
    return EXIT_FAILURE;
  }
  memset((char *) &serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  strncpy((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
  serv_addr.sin_port = htons(port);
  if (connect(sock_client, (const struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("connect() failed: %d", errno);
    return EXIT_FAILURE;
  }
  printf(">");
  memset(buf, 0, BUF_SIZE);
  fgets(buf, BUF_SIZE-1, stdin);
  write(sock, buf, strlen(buf));
  memset(buf, 0, BUF_SIZE);
  read(sock, buf, BUF_SIZE-1);
  printf("%s\n",buf);
  close(sock);
  return 0;
}
