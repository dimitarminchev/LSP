## Семафорен сървър

- Задайте 2 семафора - първият показва, че сървърът трябва да чете, вторият за клиента
- Създайте **semaphore-server**, изход при грешка
- Разпределете и прикрепете споделената памет и напишете "Hello!"
- Освободете семафора на клиента
- Докато текущото съобщение не е "q":
- Поискайте сървърния семафорен ресурс
- Ако текущото съобщение не е "q", напишете "Ok!" в паметта и освободете клиента.
- Извадете и премахнете споделената памет и семафорите

### semaphore-server.c
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
  key_t key;
  int shmid;
  int pid, semid;
  struct sembuf buf[2];
  struct memory_block * mblock;
  key = ftok(FTOK_FILE, 1); 
  if (key == -1)
  {
     printf("Failed to generate unique key. Server compiler with a wrong name?\n");
     return EXIT_FAILURE;
  }
  semid = semget(key, 3, 0666|IPC_CREAT);
  buf[0].sem_num = 0;
  buf[0].sem_flg = SEM_UNDO;
  buf[1].sem_num = 1;
  buf[1].sem_flg = SEM_UNDO;
  semctl(semid, 0, SETVAL, 0);  
  shmid = shmget(key, sizeof(struct memory_block), 0666 | IPC_CREAT); 
  mblock = (struct memory_block *) shmat(shmid, 0, 0); 
  strcpy(mblock->string, "Hello!");
  buf[0].sem_op = -1;
  buf[1].sem_op = 1;
  semop(semid, (struct sembuf*) &buf[1], 1);
  while (strcmp("q\n", mblock->string) != 0)
  {
     semop(semid, (struct sembuf*) &buf, 1);
     printf("String sent by the client is: %s", mblock->string);
     if (strcmp("q\n", mblock->string) != 0)
     strcpy(mblock->string, "Ok!");
     buf[0].sem_op = -1;
     buf[1].sem_op = 1;
     semop(semid, (struct sembuf*) &buf[1], 1);
  }
  printf("Server got q and exits\n");
  shmdt((void *) mblock);  
  shmctl(shmid, IPC_RMID, 0); 
  semctl(semid, 2, IPC_RMID);
  return EXIT_SUCCESS;
} 
```