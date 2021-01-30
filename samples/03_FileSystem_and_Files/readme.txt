1. Отваряне и затваряне на файл
openclose.c
---
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char * argv[])
{
   int fd;
   fd = open("/proc/self/environ", O_RDONLY);
   if (fd == -1) 
   {
      printf("ERROR opening 'environ'!\n");
   } 
   else 
   {
      printf("File Descriptor of 'environ' = %d\n", fd);
   }
   // write/read commands to be added here
   if (close (fd) == -1)
   {
      printf("ERROR closing the file!\n");
   }
   return 0;
}

2. Четене и отпечатване на файл
readfile.c
---
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#define BUF_SIZE 1000000
int main(int argc, char *argv[])
{
   int fd = open("./readfile.c", O_RDONLY);
   if (fd == -1)
   {
      printf("ERROR opening the file!\n");
      return -1;
   }
   ssize_t len;
   char buf[BUF_SIZE];
   while ((len = read(fd, buf, BUF_SIZE - 1)) != 0)
   {
      if (len == -1)
      {
         if (errno == EINTR) continue;
         printf("ERROR reading the file!\n");
         break;
      }
      printf("%s", buf);
   }
   if (close(fd) == -1)
   {
      printf("ERROR closing the file!\n");
      return -2;
   }
   return 0;
}

3. Запис на изречения във файл
writefile.c
---
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <string.h>
#define BUF_SIZE 1000000
long getMicrotime(){
   struct timeval currentTime;
   gettimeofday(&currentTime, NULL);
   return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}
int getSentence(char *buf) {
   sprintf(buf, "%ld> This is a new sentence.\n", getMicrotime());
   return strlen(buf);
}
int main(int argc, char *argv[])
{
   int fd;
   fd = open("./sentences.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
   if (fd == -1)
   {
      printf("ERROR opening the file!\n");
      return -1;
   }
   char buf[BUF_SIZE];
   for (int i=0; i < 100; i++)
   {
      int text_len = getSentence(buf);
      ssize_t nr = write(fd, buf, text_len);
      if (nr == -1)
      {
         printf("ERROR writing to the file!\n");
         break;
      }
   }
   if (close(fd) == -1)
   {
      printf("ERROR closing the file!\n");
      return -2;
   }
   printf("SUCCESS!\n");
   return 0;
}

4. Направете файл с дупка
makesparse.c
---
#include <stdio.h>
#include <string.h>
#define BIG_SIZE 0x1000000 // 16777216 bytes = 16 MB
int main(int argc, char * argv[])
{
   FILE * f;
   f = fopen(argv[1], "w");
   if (f == NULL)
   {
      printf("ERROR creating file: %s", argv[1]);
      return 1;
   }
   fwrite(argv[1], 1, strlen(argv[1]), f);
   fseek(f, BIG_SIZE, SEEK_CUR);
   fwrite(argv[1], 1, strlen(argv[1]), f);
   fclose(f);
}

5. Заключване на файлове
lockfile.c
---
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, char * argv[])
{
   char str[64];
   memset(str, 32, 64);
   struct flock fi;
   sprintf(str, "Stored by process %i", getpid());
   int fd = open("testlocks.txt", O_RDWR|O_CREAT);
   fi.l_type = F_WRLCK;
   fi.l_whence = SEEK_SET;
   fi.l_start = 0;
   fi.l_len = 64;
   int off = 0;
   while (fcntl(fd, F_SETLK, &fi) == -1)
   {
      fcntl(fd, F_GETLK, &fi);
      printf("bytes %i - %i blocked by process %i\n", off, off+64, fi.l_pid);
      off += 64;
      fi.l_start = off;
   }
   lseek(fd, off, SEEK_SET);
   write(fd, str, strlen(str));
   getchar();
   fi.l_type = F_UNLCK;
   if (fcntl(fd, F_SETLK, &fi) == -1) printf("ERROR while blocking!\n");
   close(fd);
}
