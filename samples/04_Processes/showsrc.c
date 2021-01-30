#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char * argv[])
{
   // Ecxecute a program
   int ret = execl("/bin/nano", "nano", "showsrc.c", NULL);
   // Error check
   if (ret == -1)
   {
     printf("Error running nano!\n");
     return EXIT_FAILURE; // -1
   }
   return EXIT_SUCCESS; // 0
}
