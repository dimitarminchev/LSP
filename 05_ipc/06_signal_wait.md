## Изчакване на сигнали

```c
#include<signal.h>
int sigwait(const sifset_t *set, int *sig);
```

Функцията **sigwait()** спира изпълнението на извикващата нишка, изчаквайки един от сигналите да стане текущ.
Функцията приема сигнала (премахва го от чакащия списък със сигнали) и връща номера на сигнала в **sig**.
При успех **sigwait()** връща 0, при грешка връща положително число, номер на грешката.

### Пример за изчакване на сигнал

Дефинирайте функцията за обработка на сигнали **SIGTERM**.
Иницирайте сигнал, като само **SIGHUP** е включен и блокирайте обработката на сигнали.
Задайте обработчик на събития за **SIGTERM**.
Отпечатайте идентификатора на процеса (**pid**).
Изчакайте входящ сигнал **SIGHUP** и изведете подходящо съобщение.
Ако възникне грешка преустановете програмата.

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