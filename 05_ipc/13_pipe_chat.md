## Using Named Pipes
The presented pair of programs implements a chat-based client/server application that demonstrates the use of named pipes.

### pipe-chat-server.c

Create a file named **./pipe-chat-fifo**. 
Open **./pipe-chat-fifo** for writing, exit in case of error. 
Start a loop that runs until we receive **"q"** from the keyboard. 
Read a character (**key**) and write it to the file. 
If **key** is Enter, use **flush**. 
Close and delete the file. 

```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

#define FIFO_FILE "./pipe-chat-fifo"

int main(int argc, char ** argv)
{
  mkfifo(FIFO_FILE, 0600);
  FILE* f = fopen(FIFO_FILE, "w");
  if(f == NULL)
  {
    printf("Error open file!\n");
    return EXIT_FAILURE;
  }

  char key;
  do
  {
    key = getchar();
    fputc(key, f);
    if(key == 10) fflush(f);
  }
  while(key != 'q');

  fclose(f);
  unlink(FIFO_FILE);
  return EXIT_SUCCESS;
}
```

### pipe-chat-client.c

Open a file named **./pipe-chat-fifo** for reading. 
Start a loop that runs until we receive **"q"** from the keyboard. 
Read a character (**key**). 
Output the received character to the console. 
Close and delete the file. 

```c
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#define FIFO_FILE "./pipe-chat-fifo"

int main(int argc, char ** argv)
{
  FILE* f = fopen(FIFO_FILE, "r");
  if(f == NULL)
  {
    printf("Error open file!\n");
    return EXIT_FAILURE;
  }

  char key;
  do
  {
    key = fgetc(f);
    putchar(key);
  }
  while(key != 'q');

  fclose(f);
  unlink(FIFO_FILE);
  return EXIT_SUCCESS;
}
```
