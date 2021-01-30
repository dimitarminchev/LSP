1. Обработка на сигнал
signal-handler.c
---
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

2. Изчакване на сигнали
signal-wait.c
---
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

3. Показване на информация за сигналите
signal-info.c
---
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
void term_handler(int sig) 
{
   printf("Signal %i - %s\n", sig, sys_siglist[sig]);
   exit(EXIT_SUCCESS);
}
int main(int argc, char ** argv) 
{
   int sig;
   struct sigaction sa;
   sigset_t sset;
   sigfillset(&sset);
   sigdelset(&sset, SIGTERM);
   sigprocmask(SIG_SETMASK, &sset, 0);
   sa.sa_handler = term_handler;
   sigaction(SIGTERM, &sa, 0);
   printf("My pid is %i\n", getpid());
   printf("Waiting...\n");
   while(!sigwait(&sset, &sig)) 
   {
      printf("Signal %i - %s\n", sig, sys_siglist[sig]);
      printf("%s\n", strsignal(sig));
   }
   return EXIT_FAILURE;
}

4. Използване на анонимни тръби
pipe-pass-message.c
---
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
int main (int argc, char * argv[])
{
   int pipedes[2];
   pipe(pipedes);
   pid_t pid = fork();
   if ( pid > 0 )
   {
      char *str = "String passed via pipe\n";
      close(pipedes[0]);
      write(pipedes[1], (void *) str, strlen(str) + 1);
      close(pipedes[1]);
   } 
   else
   {
      char buf[1024];
      int len;
      close(pipedes[1]);
      while ((len = read(pipedes[0], buf, 1024)) != 0) write(2, buf, len);
      close(pipedes[0]);
   }
   return 0;
}

5. Чат Сървър
pipe-chat-server.c
---
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define FIFO_NAME "./pipe-chat-fifo"
int main(int argc, char * argv[]) 
{
   char ch;
   mkfifo(FIFO_NAME, 0600);
   FILE * f = fopen(FIFO_NAME, "w");
   if (f == NULL)
   {
      printf("Failed to open FIFO!\n");
      return -1;
   }
   do 
   {
      ch = getchar();
      fputc(ch, f);
      if (ch == 10) fflush(f);
   } 
   while (ch != 'q');
   fclose(f);
   unlink(FIFO_NAME);
   return 0;
}

6. Чат Клиент
pipe-chat-client.c
---
#include <stdio.h>
#include <unistd.h>
#define FIFO_NAME "./pipe-chat-fifo"
int main ()
{
   char ch;
   FILE * f = fopen(FIFO_NAME, "r");
   do
   {
      ch = fgetc(f);
      putchar(ch);
   } 
   while (ch != 'q');
   fclose(f);
   unlink(FIFO_NAME);
   return 0;
}