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
