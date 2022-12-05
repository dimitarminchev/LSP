## Обработка на конекции

- Дефиниране на обработчик при заявка за връзка:
  - Прочаване на текстов ред от свързаният сокет
  - Ако няма грешка, запис на реда обратно в сокета
  - Връщане на резултата от четене/запис
- Докато приемането на връзки е наред:
  - Приемане на нова връзка, при **EINTR** повторен опит, при друга грешка изход от цикъла
  - Обработка на приетата връзка
  - Затваряне на сокета

### chat-daemon.c (Handle and Accept Connections)

```c
int HandleConnection(const int slave)
{
  ...
  int retval = ReadLine(slave, readbuf, buflen, &bytesRead);
  if(retval == 0)
  {
    WriteToSocket(slave, readbuf, bytesRead);
  }
  return retval;
}
int AcceptConnections(const int master)
{
  inr proceed = 1, slave, retval = 0;
  struct sockaddr_in client;
  socklen_t clilen;
  while((proceed == 1) && (gGracefullShutdown == 0))
  {
    clilen = sizeof(client);
	slave = accept(master, (struct sockaddr *)&client, &clilen);
	if(slave < 0)
	{
	  if(errno == EINTR) continue;
	  proceed = 0;
	  retval = -1;
	}
	else
	{
	  retval = HandleConnection(slave);
	  if(retval) proceed = 0;
	}
	close(slave);
  }
  return retval;
}
```