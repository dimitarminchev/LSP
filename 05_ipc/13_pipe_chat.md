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
