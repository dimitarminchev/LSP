## Показване на изходния код на файла

- Инициализирайте променливите
- Изпълнете **nano show-source.c**
- Ако изпълнението не е успешно, изведете съобщение и излезте

### show-source.c
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char * argv[])
{
   int ret = execl("/bin/nano", "nano", "show-source.c", NULL);
   if (ret == -1)
   {
     printf("Error running nano!\n");
     return EXIT_FAILURE; // -1
   }
   return EXIT_SUCCESS; // 0
}
```