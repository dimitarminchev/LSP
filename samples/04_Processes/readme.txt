1. Изпълнение на команда и/или програма
execFirst.c
---
#include <stdio.h>
int main(int argc, char * argv[])
{
   printf("Executе program: %s\n", argv[0]);
   return 0;
}

execSecond.c
---
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char * argv[])
{
   char *args[] = {"./execFirst",NULL};
   execvp(args[0], args);
   return 0;
}

2. Показване на изходния код на файла
showsrc.c
---
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char * argv[])
{
   int ret = execl("/bin/nano", "nano", "showsrc.c", NULL);
   if (ret == -1)
   {
     printf("Error running nano!\n");
     return EXIT_FAILURE; // -1
   }
   return EXIT_SUCCESS; // 0
}

3. Стартиране на дъщерен процес
fork.c
---
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

4. Отпечатване на идентификаторите на процесите
printpids.c
---
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
void printPIDs(char* name) 
{
   printf ("-----The %s process:\n", name);
   printf ("My pid=%d\n", getpid());
   printf ("Parent's pid=%d\n", getppid());
   printf ("------------------------\n");
}
int main(int argc, char* argv[])
{
   pid_t pid = fork();
   if(pid == -1)
   {
      printf("ERROR!\n");
      return EXIT_FAILURE;
   }
   else if(pid > 0)
   {
      printPIDs("PARENT");
   }
   else if (!pid) // pid==0
   {
      printPIDs("CHILD");
      exit(0);
   }
   return EXIT_SUCCESS;
}

5. Отпечатване на състояние за изпълнението
execstat.c
---
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
int main(int argc, char * argv[])
{
   int pid, status;
   if (argc < 2) 
   {
      printf("Usage: %s command, [arg1 [arg2]...]\n", argv[0]);
      return EXIT_FAILURE;
   }
   printf("Starting %s...\n", argv[1]);
   pid = fork();
   if (pid == 0) 
   {
      execvp(argv[1], &argv[1]);
      perror("execvp");
      return EXIT_FAILURE; // Never get there normally
   }
   else 
   {
      if (wait(&status) == -1) 
	  {
         perror("wait");
         return EXIT_FAILURE;
      }
      if (WIFEXITED(status)) printf("Child terminated normally with exit code %i\n", WEXITSTATUS(status));
      if (WIFSIGNALED(status)) printf("Child was terminated by a signal #%i\n", WTERMSIG(status));
      if (WCOREDUMP(status)) printf("Child dumped core\n");
      if (WIFSTOPPED(status)) printf("Child was stopped by a signal #%i\n", WSTOPSIG(status));
   }
   return EXIT_SUCCESS;
}
---

6. Игра на зомбита
zombietest.c
---
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
static void sigchld_hdl(int sig)
{
   while (waitpid(-1, NULL, WNOHANG) > 0) {}
}
int main(int argc, char *argv[])
{
   struct sigaction act;
   memset (&act, 0, sizeof(act));
   act.sa_handler = sigchld_hdl;
   if (sigaction(SIGCHLD, &act, 0)) 
   {
      perror ("sigaction");
      return 1;
   }
   for (int i = 0; i < 10; i++) 
   {
      int pid = fork();
      if (pid == 0) 
	  {
         printf("I will leave no zombie\n");
         exit(0);
      } else printf("Created a process with the PID %i\n", pid);
   }
   while (1) sleep(1);
   return 0;
}