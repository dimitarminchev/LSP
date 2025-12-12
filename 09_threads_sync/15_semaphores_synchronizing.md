## Synchronizing with semaphores

```c
#include <semaphore.h>
int sem_init(sem_t *sem, int pshared, unsigned int value);
int sem_wait(sem_t *sem);
int sem_post(sem_t *sem);
int sem_destroy(sem_t *sem);
```

- `sem_init()` initializes an unnamed semaphore at the address given by `sem`. The `value` argument specifies the initial value of the semaphore.

- `sem_wait()` decrements (locks) the semaphore pointed to by `sem`. If the semaphore value is zero, the call blocks until the semaphore becomes positive.

- `sem_post()` increments (unlocks) the semaphore pointed to by `sem`.

- `sem_destroy()` destroys the unnamed semaphore at the address given by `sem`.
