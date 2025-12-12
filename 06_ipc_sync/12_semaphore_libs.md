## Libraries for Working with Semaphores

```c
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

int semget(key_t key, int nsems, int semflg);
int semctl(int semid, int semnum, int cmd, ...);
int semop(int semid, struct sembuf *sops, size_t nsops);
```

- **semget()** - returns the System V semaphore set identifier associated with the **key** argument.
- **semctl()** with **cmd = SETVAL** - Sets the value of **semval** to become **arg.val** for the **semnum**-th semaphore in the set.
- **semctl()** with **cmd = IPC_RMID** - removes the semaphore.
- **semop()** - performs operations on selected semaphores from the set designated by **semid**.