## Създаване и унищожаване на мютекси

```c
#include<pthread.h>
void pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
void pthread_mutex_destroy(pthread_mutex_t *mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
```

Променливите за мютекси трябва да бъдат декларирани с тип **pthread_mutex_t** и трябва да бъдат инициализирани, 
преди да могат да бъдат използвани. Съществуват два начина за инициализиране на променлива от тип мютекс:
- Статично, когато се декларират. 
- Динамично, посредством **pthread_mutex_init()**. Този метод позволява задаването на атрибути за мютекс обекта.
