## Слушане на сокет

- Инициализиране на конфигурацията на сокета за семейството на **INET**, предоставения порт и всички интерфейси
- Създаване на сокета, изход при грешка
- Настройване на сокета за повторно използване на адреса
- Свързване на сокета, изход при грешка
- Слушане на сокета, изход при грешка
- Изход с успех

### chat-daemon.c (BindPassiveSocket)

```c
int BindPassiveSocket(const int portNum, int *consr boundSocket)
{
  struct coskaddr_in sin;
  memset(&sin.sin_zero, 0, 8);
  sin.sin_port = htons(portNum);
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  
  int newsock = socket(PF_INET, SOCK_STREAM, 0)
  if(newsock < 0)
  {
    printf("Error creating socket!\n");
	return EXIT_FAILURE; // -1
  }  
  
  int optval = 1;
  size_t optlen = sizeof(int);
  setsockopt(newsock, SOL_SOCKET, SO_REUSEADDR, &optval, optlen);
  
  if(bind(newsock, (struct sockaddr*)&sin, sizeof(struct sockaddr_in)) < 0)
  {
    printf("Error binding socket!\n");
	return EXIT_FAILURE; // -1
  }  
  
  if(listen(newsock, SOMAXCONN) < 0)
  {
    printf("Error listening on socket!\n");
	return EXIT_FAILURE; // -1
  }
  *boundSocket = newsock;
  
  return EXIT_SUCCESS; // 0
}
```