## Semaphore Server

- Set up 2 semaphores - the first indicates that the server should read, the second for the client
- Create **semaphore-server**, exit on error
- Allocate and attach the shared memory and write "Hello!"
- Release the client's semaphore
- While the current message is not "q":
- Request the server semaphore resource
- If the current message is not "q", write "Ok!" to memory and release the client.
- Detach and remove the shared memory and semaphores

### semaphore-server.c
```c
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"semaphore-types.h"

int main(int argc, char ** argv)
{
  key_t key = ftok(FTOK_FILE, 1);
  if (key == -1)
  {
     printf("Error ftok.\n");
     return EXIT_FAILURE;
  }

  int shmid = shmget(key, sizeof(struct memory_block), 0666 | IPC_CREAT);
  if(shmid == -1)
  {
    printf("Error shmget.\n");
    return EXIT_FAILURE;
  }

  int semid = semget(key, 3, 0666|IPC_CREAT);
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
  semctl(semid, 0, SETVAL, 0);

  struct memory_block * mb;
  mb = (struct memory_block *) shmat(shmid, 0, 0);
  strcpy(mb->string, "Hello!");
  buf[0].sem_op = -1;
  buf[1].sem_op = 1;
  semop(semid, (struct sembuf*) &buf[1], 1);

  while (strcmp("q\n", mb->string) != 0)
  {
     semop(semid, (struct sembuf*) &buf, 1);
     printf("Client: %s\n", mb->string);
     if (strcmp("q\n", mb->string) != 0)
     strcpy(mb->string, "Ok!");
     buf[0].sem_op = -1;
     buf[1].sem_op = 1;
     semop(semid, (struct sembuf*) &buf[1], 1);
  }

  printf("Server exit.\n");
  shmdt((void *) mb);
  shmctl(shmid, IPC_RMID, 0);
  semctl(semid, 2, IPC_RMID);
  return EXIT_SUCCESS;
}
```
