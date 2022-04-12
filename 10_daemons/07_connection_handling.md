## Обработка на конекции

- Define connections handler:
- Read text line from the passed socket
- If no error - write the line back to socket
- Return the result of the read/write
- While connections accepting is ok:
- Accept new connection, on **EINTR** try again, on other error exit the loop
- Handle the accepted connection
- Close the accepted socket

### chat-daemon.c (Handle and Accept Connections)

```
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