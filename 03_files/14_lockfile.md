## Lock and Write There

Open for writing or create **./testlocks.txt**. 
While locking 64 bytes from **offset** is unsuccessful: get and print information about the locking process and move **offset** by another 64 bytes. 
Move **offset** bytes from the beginning of the file and write information about the current process. 
Wait for the **Enter** key to be pressed. 
Unlock the 64 locked bytes, output an error on failure. 
Close the file. 

### lockfile.c
```c
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
```
