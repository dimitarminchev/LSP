## Показване на информация за сигналите

- Дефинирайте функцията за обработка на сигнали **SIGTERM**
- Иницирайте сигнално множество, като само **SIGTERM** е изключен
- Задайте обработчик на събития за **SIGTERM**
- Отпечатайте идентификатора на процеса (**pid**)
- Изчакайте и изведете подходящи съобщения за входящите сигнали
- Ако възникне грешка преустановете програмата

### signal-info.c
```c
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<unistd.h>

void signal_handler(int sig)
{
  printf("Signal %i: %s\n", sig, strsignal(sig));
  exit(EXIT_SUCCESS); // 0
}

int main(int argc, char* argv[])
{
  int sig;
  struct sigaction sa;
  sigset_t sset;
  sigfillset(&sset);
  sigdelset(&sset, SIGTERM);
  sigprocmask(SIG_SETMASK, &sset, 0);
  sa.sa_handler = signal_handler;
  sigaction(SIGTERM, &sa, 0);

  printf("My pid is %i\n", getpid());

  while(!sigwait(&sset, &sig))
  {
    printf("Signal %i: %s\n", sig, strsignal(sig));
  }

  return EXIT_FAILURE;
}
```
