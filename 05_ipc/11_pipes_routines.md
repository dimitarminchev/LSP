## Working with Pipes

```c
#include <unistd.h>
int pipe(int pipefd[2]);
```

**pipe()** - creates an anonymous pipe.  
- The **pipefd** array is used to return two file descriptors pointing to the ends of the pipe.
- **pipefd[0]** refers to the read end of the pipe
- **pipefd[1]** refers to the write end of the pipe.

```c
#include <sys/types.h>
#include <sys/stat.h>
int mkfifo(const char *pathname, mode_t mode);
```

**mkfifo**() - creates a named pipe (**FIFO**).
- **mode** specifies the permissions for the **FIFO** structure. It is modified by the **umask** method in the usual way: the permissions of the created file are (**mode & ~umask**).
