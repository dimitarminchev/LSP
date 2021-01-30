#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char * argv[])
{
   // arguments check
   if(argc != 2)
   {
      printf("Syntax: openclose [filename]\n");
      return -1;
   }

   // file descriptor
   int fd = open(argv[1], O_RDONLY);
   // int fd = open("/proc/self/environ", O_RDONLY);

   // error
   if (fd == -1)
   {
      printf("Error opening the file!\n");
   }
   else
   {
      printf("File Descriptor = %d\n", fd);
   }

   // write/read commands to be added here
   if (close(fd) == -1)
   {
      printf("Error closing the file!\n");
   }

   return 0;
}
