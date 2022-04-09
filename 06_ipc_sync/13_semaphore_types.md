## Определяне на общи данни

Определяме заключващ файл **semaphore-server**. 
Дефинираме структурата за споделената памет **memory_block**. 
Променливата **string** съдържа текущото съобщение.

### semaphore-types.h
```c
#ifndef SHMEM_TYPES
#define SHMEM_TYPES

#define FTOK_FILE "./semaphore-server"

#define MAXLEN 512

struct memory_block
{
   char string[MAXLEN];
};

#endif
```
