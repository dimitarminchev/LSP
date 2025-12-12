## Defining Common Data

Define the lock file **semaphore-server**. 
Define the structure for the shared memory **memory_block**. 
The variable **string** contains the current message.

### semaphore-types.h
```c
#ifndef SEM_TYPES
#define SEM_TYPES

#define FTOK_FILE "./semaphore-server"

#define MAX_LEN 512

struct memory_block
{
  char string[MAX_LEN];
};

#endif
```
