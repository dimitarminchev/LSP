## Игра на зомбита

Дефинирайте обработчик на сигнал за прекратяване на изпълнението.
Инициализирайте променливи за използване на обработчик на сигнал.
Задайте действие при **SIGCHLD**, изход при грешка.
Направете 10 пъти следното: създайте дъщерен процес и запазете неговия идентификатор (**pid**).
Родителският процес отпечатва идентификатора на дъщерният процес.
Дъщерният процес отпечатва съобщение и излиза.

### zombie-test.c
```c
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
static void sigchld_hdl (int sig)
{
    while (waitpid(-1, NULL, WNOHANG) > 0) {}
}
int main (int argc, char *argv[])
{
    struct sigaction act;
    memset (&act, 0, sizeof(act));
    act.sa_handler = sigchld_hdl;
    if (sigaction(SIGCHLD, &act, 0)) {
        perror ("sigaction");
        return 1;
    }
    for (int i = 0; i < 10; i++) {
        int pid = fork();
        if (pid == 0) {
                printf("I will leave no zombie\n");
                exit(0);
        } else printf("Created a process with the PID %i\n", pid);
    }
    while (1) sleep(1);
    return 0;
}
```
