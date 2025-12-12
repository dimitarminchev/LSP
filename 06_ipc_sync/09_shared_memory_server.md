## Memory Server

Create **./shared-memory-server**, exit on error. 
Allocate shared memory. 
Configure the client's memory and write the message **"Hello!"** to it. 
While the current message is not "q". 
Lock the memory for the server, set the client's turn. 
Wait if the client is using the memory. 
If the client has processed the last message - indicate that the server has processed the current message, print the message from the client and return **"Ok!"** remove the server lock. 
Remove the shared memory.

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
