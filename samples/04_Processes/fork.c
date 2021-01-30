#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
int main(int argc, char * argv[])
{
   // cloning
   pid_t pid = fork();

   // error
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
