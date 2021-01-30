#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
// Signal Child Handler
static void handler(int sig)
{
   while (waitpid(-1, NULL, WNOHANG) > 0) {}
}
// Main Program
int main(int argc, char *argv[])
{
   // Attach Signal Handler
   struct sigaction act;
   memset (&act, 0, sizeof(act));
   act.sa_handler = handler;

   // Error check
   if (sigaction(SIGCHLD, &act, 0)) 
   {
      perror("sigaction");
      return -1; // EXIT_FAILURE
   }

   // 10 times
   for (int i = 0; i < 10; i++)
   {
      // clonning
      int pid = fork();
      if (pid == 0)
      {
         // child
         printf("I will leave no zombie\n");
         exit(0);
      }
      else
      {
         // parent
         printf("Created a process with the PID %i\n", pid);
      }
   }

   // forever
   while (1) sleep(1);

   return 0; // EXIT_SUCCESS
}
