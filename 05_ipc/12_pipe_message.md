## Използване на анонимни тръби

- Отворете тръба (**pipe**) и запазете входно/изходните файлови дескриптори (**I/O FD**)
- Създайте дъщерен процес (**fork**) 
- Родителски процес: затворете входният файлов дескриптор (**input/read**)
  - Запишете съобщение на изходният файлов дескриптор (**output/write**) 
  - Затворете изходният файлов дескриптор (**output/write**)
- Дъщерен процес: затворете изходният файлов дескриптор (**output/write**)
  - Прочетете съобщение от входният файлов дескриптор (**input/read**)
  - Отпечатайте полученото съобщение
  - Затворете входният файлов дескриптор (**input/read**)

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
