## Socket Pair

```c
#include<sys/types.h>
#include<sys/socket.h>
int socketpair(int domain, int type, int protocol, int sv[2]);
```
The **socketpair()** call creates a pair of connected sockets in the specified domain, of the specified type, and using the optionally specified protocol.

The file descriptors used in referencing the new sockets are returned in **sv[0]** and **sv[1]** respectively. 

On success, the method returns 0, on error -1, and error information is found in **errno**.