## Почистване

- Ако има отворен дескриптор на заключващ файл:
  - Затваряне на файловия дескриптор
  - Изтриване на файла за заключване
- Ако има отворен сокет за слушане:
  - Затворете сокета за слушане

### chat-daemon.c (Tidy Up)

```c
int gLockFileDesk = -1;
int gMasterSocket = -1;
const char *cost gLockFilePath = "/var/run/chat-daemon.pid"

void TidyUp(void)
{
  if(gLockFileDesk != -1)
  {
    close(gLockFileDesk);
	unlink(gLockFilePath);
	gLockFileDesk = -1;
  }
  if(gMasterSocket != -1)
  {
    close(gMasterSocket);
	gMasterSocket = -1;
  }
}
```