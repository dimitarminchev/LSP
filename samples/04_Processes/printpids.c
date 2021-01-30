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
   // clonning
   pid_t pid = fork();

   // error check
   if(pid == -1)
   {
      printf("ERROR!\n");
      return EXIT_FAILURE; // -1
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
   return EXIT_SUCCESS; // 0
}
