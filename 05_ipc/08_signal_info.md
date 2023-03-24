## Показване на информация за сигналите

- Дефинирайте функцията за обработка на сигнали **SIGTERM**
- Иницирайте сигнално множество, като само **SIGTERM** е изключен
- Задайте обработчик на събития за **SIGTERM**
- Отпечатайте идентификатора на процеса (**pid**)
- Изчакайте и изведете подходящи съобщения за входящите сигнали
- Ако възникне грешка преустановете програмата

### signal-info.c
```c
// Requred headers
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<unistd.h>

// Signal Handler
void signal_handler(int sig)
{
  printf("Signal %i: %s\n", sig, strsignal(sig));
  exit(EXIT_SUCCESS); // 0
}

// Main program method to start with
int main(int argc, char* argv[])
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

  // Waiting for signals
  while(!sigwait(&sset, &sig))
  {
    printf("Signal %i: %s\n", sig, strsignal(sig));
  }

  return EXIT_FAILURE;
}
```
