## Семафор клиент

- Задайте 2 семафора - първият показва, че сървърът трябва да чете, вторият за клиента
- Създайте **semaphore-server**, изход при грешка
- Прикачете споделената памет
- Докато текущото съобщение не е "q":
- Поискайте семафорен ресурс на клиента и отпечатайте следващото съобщение
- Прочетете нов ред от клавиатурата в споделената памет
- Освободете семафора на сървъра
- Отделете споделената памет

### semaphore-client.c
```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semaphore-types.h"

int main(int argc, char * argv[])
{
  key_t key = ftok(FTOK_FILE, 1);
  if (key == -1)
  {
     printf("Error ftok.\n");
     return EXIT_FAILURE;
  }

  int shmid = shmget(key, sizeof(struct memory_block), 0666);
  if (shmid == -1)
  {
     printf("Error shmget.\n");
     return EXIT_FAILURE;
  }

  int semid = semget(key, 2, 0666);
  if(semid == -1)
  {
    printf("Error semget.\n");
    return EXIT_FAILURE;
  }

  struct sembuf buf[2];
  buf[0].sem_num = 0;
  buf[0].sem_flg = SEM_UNDO;
  buf[1].sem_num = 1;
  buf[1].sem_flg = SEM_UNDO;
  buf[1].sem_op = -1;

  struct memory_block * mb;
  mb = (struct memory_block *) shmat(shmid, 0, 0);

  while (strcmp("q\n", mb->string) != 0)
  {
    semop(semid, (struct sembuf*) &buf[1], 1);
    printf("Server: %s\n", mb->string);
    int i = 0;
    while ((i < (MAX_LEN - 1)) && ((mb->string[i++] = getchar()) !=  '\n') );
    mb->string[i] = 0;
    buf[0].sem_op = 1;
    buf[1].sem_op = -1;
    semop(semid, (struct sembuf*) &buf, 1);
  }

  printf("Client exits\n");
  shmdt((void *) mb);
  return EXIT_SUCCESS;
}
```
