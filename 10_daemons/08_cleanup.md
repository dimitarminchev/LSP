## Почистване

- If we have open lock file descriptor:
- Close the file descriptor
- Delete the lock file
- If we have open listening socket:
- Close the listening socket

### chat-daemon.c (Tidy Up)

```
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