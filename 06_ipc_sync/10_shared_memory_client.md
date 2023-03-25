## Клиент за памет

Създайте **./shared-memory-server**, излезте при грешка. 
Разпределете споделената памет. 
Докато текущото съобщение не е "q". 
Заключете паметта за клиента, задавайте ред на сървъра. 
Изчакайте, ако сървърът използва паметта. 
Ако сървърът е обработил последното съобщение - посочете, че клиентът е обработил текущото съобщение, отпечатайте съобщението от сървъра, прочетете ред от клавиатурата и премахнете заключването на клиента. 
Премахнете споделената памет.

### shared-memory-client.c
```c
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
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

  int shmid = shmget(key, sizeof(struct memory_block), 0666);
  if(shmid == -1)
  {
    printf("Error shmget.\n");
    return EXIT_FAILURE;
  }

  struct memory_block * mb;
  mb = (struct memory_block *) shmat(shmid, 0, 0);

  while(strcmp("q\n", mb->string) != 0)
  {
    int i = 0;
    mb->client_lock = BUSY;
    mb->turn = SERVER;
    while((mb->server_lock == BUSY) &&
          (mb->turn == SERVER))
    if(mb->read_last == SERVER)
    {
      mb->read_last = CLIENT;
      printf("Received: %s\n", mb->string);
      while( (i < (MAX_LEN - 1)) &&
             ((mb->string[i++] = getchar()) != '\n') )
      mb->string[i] = '\0';
      mb->client_lock = FREE;
    }
  }

  printf("Client exit.\n");
  shmdt((void*)mb);
  return EXIT_SUCCESS;
}
```
