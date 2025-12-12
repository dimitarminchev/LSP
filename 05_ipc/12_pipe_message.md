## Using Anonymous Pipes

- Open a pipe (**pipe**) and save the input/output file descriptors (**I/O FD**)
- Create a child process (**fork**) 
- Parent process: close the input file descriptor (**input/read**)
  - Write a message to the output file descriptor (**output/write**) 
  - Close the output file descriptor (**output/write**)
- Child process: close the output file descriptor (**output/write**)
  - Read a message from the input file descriptor (**input/read**)
  - Print the received message
  - Close the input file descriptor (**input/read**)

### pipe-pass-message.c
```c
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char ** argv)
{
   int pipefd[2];
   int pd = pipe(pipefd);
   if(pd == -1)
   {
     printf("Error pipe!\n");
     return EXIT_FAILURE;
   }

   int pid = fork();
   if(pid == -1)
   {
     printf("Error fork!\n");
     return EXIT_FAILURE;
   }

   if(pid > 0)
   {
     char* str = "Hello World!";
     printf("Parent pid %i\nSend: %s\n", getpid(), str);
     close(pipefd[0]);
     write(pipefd[1], (void*)str, strlen(str)+1);
     close(pipefd[1]);
   }
   else
   {
     printf("Child pid %i\nReceive: ", getpid());
     char buf[1024];
     int len;
     close(pipefd[1]);
     while((len = read(pipefd[0], buf, 1024)) != 0)
     {
        printf("%s", buf);
     }
     close(pipefd[0]);
     printf("\n");
   }

   return EXIT_SUCCESS;
}

```
