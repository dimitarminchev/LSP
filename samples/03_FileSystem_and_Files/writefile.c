#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <string.h>
#define BUF_SIZE 1000000
// Time
long getMicrotime(){
   struct timeval currentTime;
   gettimeofday(&currentTime, NULL);
   return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}
// Sentance
int getSentence(char *buf) {
   sprintf(buf, "%ld microseconds since 1 Jan 1970 0:00 GMT\n", getMicrotime());
   return strlen(buf);
}
// Main 
int main(int argc, char *argv[])
{
   // File Descriptor
   int fd = open("./sentences.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

   // Error in open
   if (fd == -1)
   {
      printf("Error opening the file!\n");
      return -1;
   }

   // Write in file
   char buf[BUF_SIZE];
   for (int i=0; i < 100; i++)
   {
      int buf_len = getSentence(buf);
      ssize_t nr = write(fd, buf, buf_len);
      // Error in write
      if (nr == -1)
      {
         printf("Error writing to the file!\n");
         return -2;
      }
   }

   // Error in close
   if (close(fd) == -1)
   {
      printf("Error closing the file!\n");
      return -3;
   }

   // OK
   printf("Success writing in file!\n");
   return 0;
}
