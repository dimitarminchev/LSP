## Използване на именовани тръби
Представената двойка програми реализира чат базирано клиент/сървър приложение, което демонстрира използването на именовани тръби.

### pipe-chat-server.c

Създайте файл на име **./pipe-chat-fifo**. 
Отворете за писане **./pipe-chat-fifo** в случай на грешка излезте. 
Стартирайте цикъл, който работи докато получим **"q"** от клавиатурата. 
Прочетете символ (**key**) и го запишете във файла. 
Ако **key** е Enter използвайте **flush**. 
Затворете и изтрийте файла. 

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

Отворете за четене файл на име **./pipe-chat-fifo**. 
Стартирайте цикъл, който работи докато получим **"q"** от клавиатурата. 
Прочетете символ (**key**). 
Изведете получения символ в конзолата. 
Затворете и изтрийте файла. 

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

### pipe-echo-chat.c
Представената програма реализира чат базирано приложение което връща ехо и демонстрира използването на именовани тръби.

- Създайте файл на име **pipe-echo-chat-fifo-file**. 
- Създайте дъщерен процес (**fork**) в случай на грешка излезте от програмата.

- Родителски процес: 
  - Отворете за писане **pipe-echo-chat-fifo-file** в случай на грешка излезте. 
  - Четете от клавиатурата и пращайте полученото във файлa
  - Затворете файлов дескриптор 

- Дъщерен процес: 
  - Отворете за четене **pipe-echo-chat-fifo-file** в случай на грешка излезте. 
  - Прочетете съобщение от входният файлов дескриптор 
  - Отпечатайте полученото съобщение
  - Затворете файловия дескриптор 

```c
#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#define FIFO_FILE "pipe-echo-chat-fifo-file"

int main(int argc, char ** argv)
{
   mkfifo(FIFO_FILE, 0644);

   int pid = fork();
   if(pid == -1)
   {
      printf("Error fork!\n");
      return EXIT_FAILURE;
   }

   if(pid > 0)
   {
      int fd = open(FIFO_FILE, O_WRONLY);
      if(fd == -1)
      {
         printf("Error open file for writing!\n");
         return EXIT_FAILURE;
      }

      char writeBuffer[80];
      while (1)
      {
             fgets(writeBuffer, 80, stdin);
             write(fd, writeBuffer, strlen(writeBuffer) + 1);
      }
      close(fd);
   }
   else
   {
      int fd = open(FIFO_FILE, O_RDONLY);
      if(fd == -1)
      {
         printf("Error open file for reading!\n");
         return EXIT_FAILURE;
      }

      char readBuffer[80];
      while (1)
      {
         read(fd, readBuffer, sizeof(readBuffer));
         printf("%s\n", readBuffer);

      }
      close(fd);
   }

   unlink(FIFO_FILE);

   return EXIT_SUCCESS;
}
```
