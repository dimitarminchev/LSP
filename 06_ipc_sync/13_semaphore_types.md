## Определяне на общи данни

Определяме заключващ файл **semaphore-server**. 
Дефинираме структурата за споделената памет **memory_block**. 
Променливата **string** съдържа текущото съобщение.

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
