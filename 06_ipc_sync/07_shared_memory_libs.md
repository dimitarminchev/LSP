## Libraries for Working with Shared Memory

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

- **ftok()** = converts a pathname and a project identifier to a System V IPC key.
- **shmget()** = allocates a System V shared memory segment.
- **shmat()** = attaches the System V shared memory segment identified by **shmid** to the address space of the calling process.
- **shmdt()** = detaches the shared memory segment located at the address specified by **shmaddr** from the address space of the calling process.
- **shmctl()** with cmd = IPC_RMID - marks the segment to be destroyed.