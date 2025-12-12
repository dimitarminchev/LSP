## Libraries for Working with Messages

```c
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg>

int msgget(key_t key, int msgflg);
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
```

The **msgget()** system call returns the System V message queue identifier associated with the value of the **key** argument.

The **msgsnd()** and **msgrcv()** system calls are used, respectively, to send and receive messages from a System V message queue. The calling process must have write permission on the message queue to send a message and read permission to receive a message.

**msgctl()** with **cmd** = **IPC_RMID** removes the message queue.