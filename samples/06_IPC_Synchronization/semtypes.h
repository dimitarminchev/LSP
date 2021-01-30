#ifndef SHMEM_TYPES
#define SHMEM_TYPES
#define FTOK_FILE "./semserv"
#define MAXLEN 512
struct memory_block
{
  char string[MAXLEN];
};
#endif
