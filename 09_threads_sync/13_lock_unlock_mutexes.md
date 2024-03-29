## Заключване и отключване на мутекси

```c
#include<pthread.h>
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex)
int pthread_mutex_unlock(pthread_mutex_t *mutex)
```

- **pthread_mutex_lock()** се използва от дадена нишка, за да получи заключване на посочената мютекс променлива. Ако мутексът вече е заключен от друга нишка, това извикване ще блокира извикващата нишка, докато мутексът не бъде отключен.

- **pthread_mutex_trylock()** ще се опита да заключи мутекс. Ако обаче мютексът вече е заключен, процедурата ще се върне незабавно с код за грешка заето (_Термин на Английски език: bussy_). Тази процедура може да бъде полезна за предотвратяване на условия за възникване на мъртва хваатка.

- **pthread_mutex_unlock()** ще отключи мутекс, ако бъде извикана от притежаващата го нишка. Извикването на тази процедура е необходимо, след като дадена нишка е приключила използването на защитени данни, ако други нишки трябва да получат мутекса за работата си със защитените данни. 