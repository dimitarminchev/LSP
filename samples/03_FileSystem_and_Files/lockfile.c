#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, char * argv[])
{
   // var
   char str[64];
   memset(str, 32, 64);
   struct flock fi;
   sprintf(str, "Stored by process %i", getpid());

   // open file
   int fd = open("testlocks.txt", O_RDWR|O_CREAT);
   fi.l_type = F_WRLCK;
   fi.l_whence = SEEK_SET;
   fi.l_start = 0;
   fi.l_len = 64;
   int off = 0;

   // lock 64 ahead
   while (fcntl(fd, F_SETLK, &fi) == -1)
   {
      fcntl(fd, F_GETLK, &fi);
      printf("bytes %i - %i blocked by process %i\n", off, off+64, fi.l_pid);
      off += 64;
      fi.l_start = off;
   }
   lseek(fd, off, SEEK_SET);

   // write
   write(fd, str, strlen(str));
   getchar();
   fi.l_type = F_UNLCK;

   if (fcntl(fd, F_SETLK, &fi) == -1) 
   {
      printf("Error while blocking!\n");
   }

   // close file
   close(fd);
}
