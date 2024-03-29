## Стартиране на дъщерен процес

```c
#include<sys/types.h>
#include<unistd.h>
pid_t fork(void);
pid_t getpid(void);
pid_t getppid(void);
```

- Успешно извикване на **fork()** създава нов процес, идентичен почти във всички аспекти с извикващия го процес.
- Родителският процес получава идентификатора (**pid**) на дъщерния процес, а дъщерния процес получава нула.
- При грешка и дъщерния процес не е създаден, **fork()** връща -1 и грешката (**errno**) може да бъде:

| Грешка | Пояснение                                                                                         |
| ------ | ------------------------------------------------------------------------------------------------- |
| EAGAIN | Ядрото не успя да разпредели определени ресурси, като например нов идентификатор (pid) на процес. |
| ENOMEM | Няма достатъчно памет на ядрото за изпълнение на заявката.                                        |

Програмен фрагмен за стартиране на дъщерен процес:

### fork.c
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
int main(int argc, char * argv[])
{
   pid_t pid = fork();
   if(pid == -1)
   {
      printf("Error forking a process!\n");
      return EXIT_FAILURE; // -1
   }
   else if(pid == 0)
   {
      printf("Child process!\n");
   }
   else
   {
      printf("Parent process!\n");
   }
   return EXIT_SUCCESS; // 0
}
```

Повече информация:
[Linux Programming](https://www.slideshare.net/EmertxeSlides/linux-programming-36666547)
