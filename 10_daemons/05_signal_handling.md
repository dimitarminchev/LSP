## Обработка на сигнали

- Дефиниране на обработчици на сигнали **handler**
- На **SIGUSR1** = задайте флага **graceful**
- На **SIGHUP** = задайте флагове **graceful** и **HUp**
- На **SIGTERM** = процес на почистване и изход
- Блокиране на флагове **SIGUSR2**, **SIGALRM** ...  (общо 7)
- Задаване манипулатора за **SIGUSR1**, **SIGHUP**, **SIGTERM** и други фатални сигнали (общо 16)

### chat-daemon.c (ConfigureSignalHandlers)

```c
void Handler(int Signal) {
  switch(Signal) 
  {
    case SIGUSR1: gGracefulShutdown = 1; break;
	case SIGHUP: gGracefulShutdown = gCaughtHupSignal = 1; break;
	case SIGTERM: TidyUp(); exit(EXIT_SUCCESS); 
	...
	default: ...
	  TidyUp(); exit(0);
  }
  ...
}
int ConfigureSignalHandlers(void)
{
  int i, j, k;
  int BlockSignals[] = {SIGUSR2, SIGALRM, SIGPIPE, ... };
  int HandleSignals[] = {SIGUSR1, SIGHUP, SIGTERM, ... };
  sigemptyset(&SigMask);
  for(i = 0; i < 7; i++)
  {
    sigaddset(&SigMask, *(BlockSignals + i));
  }  
  ...
  for(i = 0; i < 16; i++)
  {
    sigaction(*(HandleSignals + i), &SignalAction, NULL);
  }
  return EXIT_SUCCESS; // 0
}
```