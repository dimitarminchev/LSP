## Съединяване на нишки

![Joining Threads](06_joining_threads.png) 

**pthread_join()** блокира извикващата нишка, докато нишката с идентификатор **threadid** приключи.

Програмистът може да получи състоянието на прекратяване на нишката, ако указано извикване на **pthread_exit()**.