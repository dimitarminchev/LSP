## Creating and destroying mutexes

```c
#include <pthread.h>
void pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
void pthread_mutex_destroy(pthread_mutex_t *mutex);
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
```

Mutex variables must be declared with type `pthread_mutex_t` and initialized before they can be used. There are two ways to initialize a mutex variable:

- Statically, at declaration time using `PTHREAD_MUTEX_INITIALIZER`.
- Dynamically, using `pthread_mutex_init()`. This allows setting attributes for the mutex object.
