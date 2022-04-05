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
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
int main (int argc, char * argv[])
{
   int pipedes[2];
   pipe(pipedes);
   pid_t pid = fork();
   if ( pid > 0 )
   {
      char *str = "String passed via pipe\n";
      close(pipedes[0]);
      write(pipedes[1], (void *) str, strlen(str) + 1);
      close(pipedes[1]);
   } 
   else
   {
      char buf[1024];
      int len;
      close(pipedes[1]);
      while ((len = read(pipedes[0], buf, 1024)) != 0) write(2, buf, len);
      close(pipedes[0]);
   }
   return 0;
}
```