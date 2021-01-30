#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

// Signal Handler
void signal_handler(int sig) 
{
   printf("Signal %i - %s\n", sig, sys_siglist[sig]);
   exit(EXIT_SUCCESS); // 1
}

// Main Program
int main(int argc, char ** argv) 
{
   // Signal Structure Initialization
   int sig;
   struct sigaction sa;
   sigset_t sset;
   sigfillset(&sset);
   sigdelset(&sset, SIGTERM);
   sigprocmask(SIG_SETMASK, &sset, 0);
   sa.sa_handler = signal_handler;
   sigaction(SIGTERM, &sa, 0);

   // Print
   printf("My pid is %i\n", getpid());
   printf("Waiting...\n");

   // Forever
   while(!sigwait(&sset, &sig)) 
   {
      printf("Signal %i - %s\n", sig, sys_siglist[sig]);
      printf("%s\n", strsignal(sig));
   }

   return EXIT_FAILURE; // -1
}
