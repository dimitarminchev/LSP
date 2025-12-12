## Waiting for Signals

```c
#include<signal.h>
int sigwait(const sifset_t *set, int *sig);
```

The **sigwait()** function suspends execution of the calling thread, waiting for one of the signals to become pending.
The function accepts the signal (removes it from the pending signal list) and returns the signal number in **sig**.
On success, **sigwait()** returns 0, on error it returns a positive number, the error number.

### Signal Wait Example

Define the signal handler function for **SIGTERM**.
Initialize a signal with only **SIGHUP** included and block signal handling.
Set an event handler for **SIGTERM**.
Print the process identifier (**pid**).
Wait for an incoming **SIGHUP** signal and output an appropriate message.
If an error occurs, terminate the program.

### signal-wait.c
```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Main program
int main(int argc, char ** argv)
{
   // Signal Structure Initialization
   int sig;
   struct sigaction sa;
   sigset_t newset;
   sigemptyset(&newset);
   sigaddset(&newset, SIGINT); // Ctr + C
   sigprocmask(SIG_BLOCK, &newset, 0);
   sigaction(SIGTERM, &sa, 0);

   // Print
   printf("My pid is %i\n", getpid());
   printf("Waiting...\n");

   // Forever
   while(!sigwait(&newset, &sig))
   {
     printf("SIGINT recieved\n");
     return EXIT_SUCCESS; // 0
   }

   return EXIT_FAILURE; // -1
}
```