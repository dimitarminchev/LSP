#ifndef SHMEM_TYPES
#define SHMEM_TYPES
#define FTOK_FILE "./shmemserv"
#define MAXLEN 512
#define FREE 1
#define BUSY 0
#define SERVER 1
#define CLIENT 0
struct memory_block
{
   int server_lock;
   int client_lock;
   int turn;
   int readlast;
   char string[MAXLEN];
};
#endif
