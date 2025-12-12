## Managing thread exit

```c
#include <pthread.h>
void pthread_cleanup_push(void (*routine)(void *), void *arg);
void pthread_cleanup_pop(int execute);
```

- The function `pthread_cleanup_push()` pushes a cleanup handler onto the calling thread's stack of cleanup handlers. When the handler is later invoked, the `arg` value will be passed to it.

- The function `pthread_cleanup_pop()` pops the handler at the top of the cleanup stack and optionally executes it if the `execute` argument is nonzero.
