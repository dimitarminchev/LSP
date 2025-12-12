## Memory Client

Create **./shared-memory-server**, exit on error. 
Allocate the shared memory. 
While the current message is not "q". 
Lock the memory for the client, set the server's turn. 
Wait if the server is using the memory. 
If the server has processed the last message - indicate that the client has processed the current message, print the message from the server, read a line from the keyboard and remove the client lock. 
Remove the shared memory.

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
