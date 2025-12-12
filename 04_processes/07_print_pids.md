## Print Process IDs

- Initialize the functions and variables.
- Create a child process and save its identifier (**pid**).
- If the value of **pid** is positive, then the parent process is running. Print the identifier of the parent process and **ppid**.
- If the value of **pid** is zero, then the child process is running. Print the identifier of the child process and **ppid**.
- If the value of **pid** is -1, then an error has occurred. Output an appropriate message and exit.

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
