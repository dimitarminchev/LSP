## Starting a Child Process

```c
#include<sys/types.h>
#include<unistd.h>
pid_t fork(void);
pid_t getpid(void);
pid_t getppid(void);
```

- A successful call to **fork()** creates a new process, identical in almost all aspects to the calling process.
- The parent process receives the identifier (**pid**) of the child process, and the child process receives zero.
- On error and the child process is not created, **fork()** returns -1 and the error (**errno**) can be:

| Error  | Description                                                                               |
| ------ | ----------------------------------------------------------------------------------------- |
| EAGAIN | The kernel failed to allocate certain resources, such as a new process identifier (pid). |
| ENOMEM | There is insufficient kernel memory to execute the request.                               |

Program fragment for starting a child process:

### fork.c
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
int main(int argc, char * argv[])
{
   pid_t pid = fork();
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
```

More information:
[Linux Programming](https://www.slideshare.net/EmertxeSlides/linux-programming-36666547)
