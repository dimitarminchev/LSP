## Библиотеки за работа със споделена памет

```c
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>

key_t ftok(const char *pathname, int proj_id);
int shmget(key_t key, size_t size, int shmflg);
void *shmat(int shmid, const void *shaddr, int shmflg);
int shmdt(const void *shmaddr);
int shmctl(int shmid, int cmd, struct shmid_ds *buf);
```

- **ftok()** = преобразува име на път и идентификатор на проект към ключ на System V IPC.
- **shmget()** = разпределя сегмент на System V споделена памет .
- **shmat()** = придава сегмента на System V споделена памет, идентифициран от **shmid*, в адресното пространство на извикващия процес.
- **shmdt()** = отделя сегмента на споделената памет, разположен на адреса, определен от **shmaddr** от адресното пространство на извикващия процес.
- **shmctl()** с cmd = IPC_RMID - маркира сегмента, който ще бъде унищожен.