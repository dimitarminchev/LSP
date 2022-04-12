## Обработка на сигнали

- Define signals **handler**:
- On **SIGUSR1** = set the **graceful** flag
- On **SIGHUP** = set **graceful** and **HUp** flags
- On **SIGTERM** = cleanup and exit process
- Block **SIGUSR2**, **SIGALRM** ... flags (total 7)
- Set the handler for **SIGUSR1**, **SIGHUP**, **SIGTERM** and other fatal signals (total 16)


### chat-daemon.c (ConfigureSignalHandlers)

```
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