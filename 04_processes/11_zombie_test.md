## Zombie Game

Define a signal handler for terminating execution.
Initialize variables for using the signal handler.
Set action for **SIGCHLD**, exit on error.
Do the following 10 times: create a child process and save its identifier (**pid**).
The parent process prints the identifier of the child process.
The child process prints a message and exits.

### zombie-test.c
```c
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
static void sigchld_hdl (int sig)
{
    while (waitpid(-1, NULL, WNOHANG) > 0) {}
}
int main (int argc, char *argv[])
{
    struct sigaction act;
    memset (&act, 0, sizeof(act));
    act.sa_handler = sigchld_hdl;
    if (sigaction(SIGCHLD, &act, 0)) {
        perror ("sigaction");
        return 1;
    }
    for (int i = 0; i < 10; i++) {
        int pid = fork();
        if (pid == 0) {
                printf("I will leave no zombie\n");
                exit(0);
        } else printf("Created a process with the PID %i\n", pid);
    }
    while (1) sleep(1);
    return 0;
}
```
