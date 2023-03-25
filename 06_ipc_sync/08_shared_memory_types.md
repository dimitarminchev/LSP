## Определяне на общи данни

Определете идентификационен номер на опашката **FTOK_FILE**. Дефинирайте структурата на споделената памет **memory_block**:
- **server_lock** е 1, когато сървърът използва паметта
- **client_lock** е 1, когато клиентът използва паметта
- **turn** е 0, когато чакате клиентско съобщение
- **turn** е 1, когато чакате съобщение от сървъра
- **readlast** е 0, когато клиентът получи последно съобщение
- **readlast** е 1, когато сървър получи последно съобщение
- **string**  държи текущото съобщение

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
