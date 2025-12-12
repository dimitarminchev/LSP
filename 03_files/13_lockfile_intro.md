## File Locking

Use the **fcntl()** method, which provides a pointer to the **flock** structure. This call manipulates the file descriptor **fd**, depending on the command **cmd**:

- To lock a block of a file, use **F_SETLK**.
- If the block is already locked, use **F_GETLK** to get information about the locking process.
- To unlock a block of a file, use **F_SETLK**, but set **flock.l_type = F_UNLCK**.

```c
#include<stdio.h>
FILE *fopen(const char *pathname, const char *mode);
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
int fseek(FILE *stream, long offset, int whence);
int fclose(FILE * stream);
```

The flock structure
```c
struct flock {
   ...
   short l_type;   // F_RDLCK, F_WRLCK, F_UNLCK
   short l_whence; // SEEK_SET, SEEK_CUR, SEEK_END
   
   off_t l_start;  // Starting offset for lock
   off_t l_len;    // Number of bytes to lock
   
   pid_t l_pid;    // PID of process blocking our lock
   ...
}
```
