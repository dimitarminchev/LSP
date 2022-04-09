## Библиотеки за работа със съобщения

```c
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg>

int msgget(key_t key, int msgflg);
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
```

Системното извикване **msgget()** връща System V идентификатор на опашката за съобщения свързана със стойността на аргумента **key**.

Системните извиквания **msgsnd()** и **msgrcv()** се използват, съответно, за изпращане и получаване на съобщения от System V опашка за съобщения. Извикващият процес трябва да има разрешение за запис в опашката на съобщенията, за да изпрати съобщение и да има разрешение за четене, за да получи съобщение.

**msgctl()** и **cmd** = **IPC_RMID** премахва опашка на съобщенията.