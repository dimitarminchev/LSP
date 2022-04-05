## Показване на информация за сигналите

- Дефинирайте функцията за обработка на сигнали **SIGTERM**
- Иницирайте сигнално множество, като само **SIGTERM** е изключен
- Задайте обработчик на събития за **SIGTERM**
- Отпечатайте идентификатора на процеса (**pid**)
- Изчакайте и изведете подходящи съобщения за входящите сигнали
- Ако възникне грешка преустановете програмата

### signal-info.c
```c
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
```