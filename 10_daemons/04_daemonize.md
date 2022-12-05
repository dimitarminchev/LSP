## Демонизиране

- Разклоняване на процеса, изход от родителя и при грешка
- Отваряне на дневника на приложението
- Създаване на **lock file** и заключване, изход при грешка
- Записване идентификатора на процеса **pid** във файла **lock file**
- Поемане на водеща роля в нова сесия, изход при грешка
- Промяна на директорията на процеса на '/'
- Затваряне на всички възможни файлови дескриптори, с изключение на **lock file**
- Отваряне на стандартните потоци (0 - 2), пренасочване към '/dev/null' и успешен изход 

### chat-daemon.c (BecomeDaemonProcess)

```c
int BecomeDaemonProcess(void)
{
  ...
  switch(iCurrentPID = fork())
  {
    case 0: break; // The child continues execution
	case -1: // Error forking ...
	default: exit(0);
  }
  ...
  openlog(cApplicationName, LOG_NOWAIT, LOG_LOCAL0);
  
  if((gLockFileDesc = creat)cLockFilePath, 0644) < 0)
  // Error creating the lock file ...
  
  if((LockResult = fcntl(gLockFileDesc, F_SETLK, &Lock)) < 0)
  // Error locking the lock file ...
  
  if(write(gLockFileDesc, cPIDString, strlen(cPIDString)) <= 0)
  // Error writing to lock file ...
  
  if(setsid() < 0) 
  // Error changing the session ID ...
  
  if(chdir("/") < 0)
  // Error changing the process folder ...
  
  long numFiles = sysconf(_SC_OPEN_MAX);
  for(i = numFiles-1; i >=0 ; --i) 
  {
    if(i != gLockFileDesc) close(i);
  }
  int stdioFD = open("/dev/null", O_RDWR);
  dup(stdioFD);
  dup(stdioFD);
  
  return EXIT_SUCCESS; // 0
}
```