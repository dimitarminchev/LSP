## Defining Common Data

Define the queue identification number **FTOK_FILE**. Define the shared memory structure **memory_block**:
- **server_lock** is 1 when the server is using the memory
- **client_lock** is 1 when the client is using the memory
- **turn** is 0 when waiting for a client message
- **turn** is 1 when waiting for a message from the server
- **read_last** is 0 when the client received the last message
- **read_last** is 1 when the server received the last message
- **string** holds the current message

### shared-memory-types.h
```c
#ifndef SHMEM_TYPES
#define SHMEM_TYPES

#define FTOK_FILE "./shared-memory-server"

#define MAX_LEN 512
#define FREE 1
#define BUSY 0
#define SERVER 1
#define CLIENT 0

struct memory_block
{
  int server_lock;
  int client_lock;
  int turn;
  int read_last;
  char string[MAX_LEN];
};

#endif
```
