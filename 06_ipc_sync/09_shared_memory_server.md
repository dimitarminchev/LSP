## Сървър за памет

Създайте **./shared-memory-server**, излезте при грешка. 
Разпределете споделена памет. 
Конфигурирайте паметта на клиента и запишете съобщение **"Hello!"** в него. 
Докато текущото съобщение не е "q". 
Заключете паметта за сървъра, задайте ред на клиента. 
Изчакайте, ако клиентът използва паметта. 
Ако клиентът е обработил последното съобщение - посочете, че сървърът е обработил текущото съобщение, отпечатайте съобщението от клиента и върнете **"Ok!"** премахнете заключването на сървъра. 
Премахнете споделената памет.

### shared-memory-server.c
```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include "shared-memory-types.h"

int main(int argc, char ** argv)
{
  key_t key = ftok(FTOK_FILE, 1);
  if(key == -1)
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

  struct memory_block * mblock;
  mblock = (struct memory_block *) shmat(shmid, 0, 0);
  mblock->turn = CLIENT;
  mblock->server_lock = FREE;
  mblock->client_lock = FREE;
  mblock->read_last = SERVER;
  strcpy(mblock->string, "Hello");

  while(strcmp("q\n", mblock->string) != 0)
  {
    mblock->server_lock = BUSY;
    mblock->turn = CLIENT;
    while((mblock->client_lock == BUSY) &&
          (mblock->turn == CLIENT))
    if(mblock->read_last == CLIENT)
    {
      mblock->read_last = SERVER;
      printf("Sended: %s\n", mblock->string);
      if(strcmp("q\n", mblock->string) != 0)
       strcpy(mblock->string, "OK");
      mblock->server_lock = FREE;
    }
  }

  printf("Server exit.\n");
  shmdt((void*)mblock);
  shmctl(shmid, IPC_RMID, 0);
  return EXIT_SUCCESS;
}
```
