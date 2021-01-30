#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shmemtypes.h"
int main(int argc, char * argv[])
{
  struct memory_block * mblock;

  // Shared Memory Key
  key_t key = ftok(FTOK_FILE, 1);
  if (key == -1)
  {
    printf("Failed to generate unique key. Server compiler with a wrong name?\n");
    return EXIT_FAILURE; // 01
  }

  // Shared Memory Identificator
  int shmid = shmget(key, sizeof(struct memory_block), 0666 | IPC_CREAT);


  // Memory Block
  mblock = (struct memory_block *) shmat(shmid, 0, 0);
  mblock->turn = CLIENT;
  mblock->server_lock = FREE;
  mblock->client_lock = FREE;
  mblock->readlast = SERVER;

  // Preapre and Send
  strcpy(mblock->string, "Hello!");
  while (strcmp("q\n", mblock->string) != 0)
  {
    int i = 0;
    mblock->server_lock = BUSY;
    mblock->turn = CLIENT;
    while ((mblock->client_lock == BUSY) && (mblock->turn == CLIENT));
    if (mblock->readlast == CLIENT)
    {
      mblock->readlast = SERVER;
      printf("Client > %s", mblock->string);
      printf("Write message and press [Enter] to send ...\n");
      while ((i < (MAXLEN - 1)) && ((mblock->string[i++] = getchar()) != '\n') );
      // if (strcmp("q\n", mblock->string) != 0)
      mblock->string[i] = 0;
      mblock->server_lock = FREE;
    }
  }

  // Quit and free shared memory resourse
  printf("Server quit!\n");
  shmdt((void *) mblock);
  shmctl(shmid, IPC_RMID, 0);

  return EXIT_SUCCESS; // 1
}
