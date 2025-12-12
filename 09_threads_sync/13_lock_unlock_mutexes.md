## Locking and unlocking mutexes

```c
#include <pthread.h>
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```

- `pthread_mutex_lock()` is used by a thread to acquire the lock on the specified mutex variable. If the mutex is already locked by another thread, this call will block the caller until the mutex becomes available.

- `pthread_mutex_trylock()` attempts to lock the mutex but, if the mutex is already locked, returns immediately with an error code indicating the resource is busy. This can be useful to avoid deadlock situations.

- `pthread_mutex_unlock()` releases the mutex when called by the owning thread. This call must be made after the thread finishes using the protected data so other threads can acquire the mutex.
