## Записване на изречения във файл

- Инициализирайте функциите и променливите.
- Създайте дъщерен процес и запазете неговия идентификатор (**pid**).
- Ако стойността на **pid** е положителна, то работи родителски процес. Отпечатайте идентификатора на родителският процес и **ppid**.
- Ако стойността на **pid** е нула, то работи дъщерен процес. Отпечатайте идентификатора на дъщерния процес и **ppid**.
- Ако стойността на **pid** е -1, то е възникнала грешка. Изведете подходящо съобщение и излезте.

### print-pids.c
```c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
void printPIDs(char* name) 
{
   printf ("-----The %s process:\n", name);
   printf ("My pid=%d\n", getpid());
   printf ("Parent's pid=%d\n", getppid());
   printf ("------------------------\n");
}
int main(int argc, char* argv[])
{
   pid_t pid = fork();
   if(pid == -1)
   {
      printf("ERROR!\n");
      return EXIT_FAILURE;
   }
   else if(pid > 0)
   {
      printPIDs("PARENT");
   }
   else if (!pid) // pid==0
   {
      printPIDs("CHILD");
      exit(0);
   }
   return EXIT_SUCCESS;
}
```
