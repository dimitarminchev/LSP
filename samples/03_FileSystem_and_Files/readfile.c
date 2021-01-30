#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#define BUF_SIZE 1000000
int main(int argc, char *argv[])
{
   // file descriptor
   int fd = open("./readfile.c", O_RDONLY);

   // error in open
   if (fd == -1)
   {
      printf("Error opening the file!\n");
      return -1;
   }

   // buffer
   ssize_t len;
   char buf[BUF_SIZE];
   while ((len = read(fd, buf, BUF_SIZE - 1)) != 0)
   {
      // error in read
      if (len == -1)
      {
         if (errno == EINTR) continue;
         printf("Error reading the file!\n");
         break;
      }
      // Print the first 1000000 chars
      printf("%s", buf);
   }

   // close
   if (close(fd) == -1)
   {
      printf("Error closing the file!\n");
      return -2;
   }
   return 0;
}
