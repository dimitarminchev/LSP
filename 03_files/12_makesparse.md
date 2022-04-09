## Направете файл с дупка

- Инициализирайте променливите
- Създайте файл, като използвате за името му първият аргумент, предаден на програмата
- Ако не се отвори, изведете грешка и излезте
- Запишете името на файла във файла
- Прескочете 16777216 байта напред във файла
- Запишете отново името на файла във файла
- Затворете файла

### makesparse.c
```c
#include <stdio.h>
#include <string.h>

#define BIG_SIZE 0x1000000

int main(int argc, char * argv[])
{
  FILE * f;
  f = fopen(argv[1], "w");
  if (f == NULL) 
  {
     printf("ERROR creating file: %s", argv[1]);
     return 1;
  }
  fwrite(argv[1], 1, strlen(argv[1]), f);
  fseek(f, BIG_SIZE, SEEK_CUR);
  fwrite(argv[1], 1, strlen(argv[1]), f);
  fclose(f);
}
```