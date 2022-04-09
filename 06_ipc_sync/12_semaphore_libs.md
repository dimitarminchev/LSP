## Библиотеки за работа със семафори

```c
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

int semget(key_t key, int nsems, int semflg);
int semctl(int semid, int semnum, int cmd, ...);
int semop(int semid, struct sembuf *sops, size_t nsops);
```

- **semget()** - връща System V идентификатор на семафорно множество, свързано с аргументa **key**.
- **semctl()** с **cmd = SETVAL** - Задава стойността на **semval** да стане **arg.val** за **semnum**-тия семафор в множеството.
- **semctl()** с **cmd = IPC_RMID** - премахва семафора.
- **semop()** - изпълнява операции на избрани семафори от множеството, обозначени с **semid**.