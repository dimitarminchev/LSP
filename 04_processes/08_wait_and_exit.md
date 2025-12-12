## Waiting for and Terminating a Child Process

```c
#include<stdlib.h>
void exit(int status);
```

- Calling **exit()** performs some basic shutdown steps and then instructs the kernel to terminate the process.
- The status parameter (**status**) is used to indicate the exit status of the process.
- When a process finishes, the kernel sends a **SIGCHLD** signal to the parent.

```c
pid_t pid = fork();
if (pid > 0) {
   printPIDs("PARENT");
   wait(&child_status);
}
else if (!pid) {
   printPIDs("CHILD");
   exit(0);
} 
else if (pid == -1) {
   printf("ERROR");
   return EXIT_FAILURE;
}
```

Before terminating the process, the C library performs the following steps:
- Calls all functions registered with **atexit()** or **on_exit()**, in reverse order
of their registration.
- Flushes all standard open input-output streams.
- Removes all temporary files created with the **tmpfile()** function.

These steps complete all the work that the process must do in user space, so **exit()** calls the system call **_exit()** to allow the kernel to handle the rest of the termination process:

```c
#include <unistd.h>
void _exit (int status);
```

The process can be terminated if a signal is sent whose default action is to terminate the process. Such signals are **SIGTERM** and **SIGKILL**.

When a process finishes, the kernel sends a **SIGCHLD** signal to the parent process. By default, this signal is ignored and the parent takes no action. Processes can choose to handle this signal through the **signal()** or **sigaction()** system calls.

```c
#include<sys/types.h>
#include<sys/wait.h>
pid_t wait(int status);
int WIFEXITED(status);
int WIFSIGNALED(status);
int WIFSTOPPED(status);
int WIFCONTINUED(status);
int WEXITSTATUS(status);
int WTERMSIG(status);
int WSTOPSIG(status);
int WCOREDUMP(status);
```

- **wait()** returns the value of the identifier (**pid**) of a child process or -1 on error.
- If no child process has terminated, the call blocks until a child process finishes.
- **WIFEXITED** returns true if the process terminated normally.
- On normal termination, **WEXITSTATUS** provides the eight bits that are passed to **_exit**.
- WIFSIGNALED returns true if a signal caused the process termination.
- In case of termination by signal, **WTERMSIG** returns the number of that signal.
- In case of termination by signal, **WCOREDUMP** returns true if the process dumped core in response to receiving the signal.
- **WIFSTOPPED** and **WIFCONTINUED** return true if the process was stopped or continued.
- If **WIFSTOPPED** is true, **WSTOPSIG** provides the number of the signal that stopped the process.

When an error occurs, there are two possible values:

| Error  | Information                                             |
| ------ | ------------------------------------------------------- |
| ECHILD | The calling process has no child processes.             |
| EINTR  | The call terminated early due to a received signal.     |
