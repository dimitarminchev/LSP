## Signal Handling

- Define the signal handler function for **SIGTERM**
- Initialize a signal with only **SIGHUP** included and block signal handling
- Set an event handler for **SIGTERM**
- Print the process identifier (**pid**)
- Enter an infinite loop

### signal-handler.c
```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal Handler
void signal_handler(int i)
{
   printf ("Terminating\n");
   exit(EXIT_SUCCESS); // 1
}

// Main Program
int main(int argc, char ** argv)
{
   // Signal Structure Initialization
   struct sigaction sa;
   sigset_t newset;
   sigemptyset(&newset);
   sa.sa_flags = 0;
   sa.sa_handler = signal_handler;
   sigaction(SIGINT, &sa, NULL); // Ctrl+C

   // Print
   printf("My pid is %i\n", getpid());
   printf("Waiting...\n");

   // Forever
   while(1) sleep(1);

   return EXIT_FAILURE; // -1
}
```