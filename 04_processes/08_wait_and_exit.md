## Изчакване и прекратяване на дъщерен процес

```c
#include<stdlib.h>
void exit(int status);
```

- Извикване на **exit()** изпълнява някои основни стъпки за изключване и след това инструктира ядрото да прекрати процеса.
- Параметърът на състоянието (**status**) се използва за обозначаване на изходното състояние на процеса.
- Когато процес завърши, ядрото изпраща сигнал **SIGCHLD** към родителят.

```c
pid_t pid = fork();
if (pid > 0) {
   printPIDs("PARENT");
   wait(&child_status);
}
else if (!pid) {
   printPIDs("CHILD");
   exit(0);
} 
else if (pid == -1) {
   printf("ERROR");
   return EXIT_FAILURE;
}
```

Преди да прекрати процеса, библиотеката C изпълнява следните стъпки:
- Извиква всички функции, регистрирани с **atexit()** или **on_exit()**, в обратен ред
на тяхната регистрация.
- Изчиства всички стандартни отворени вхдни-изходни потоци.
- Премахва всички временни файлове, създадени с функцията **tmpfile()**.

Тези стъпки завършват цялата работа, която процесът трябва да направи в потребителското пространство, така че **exit()** извиква системното повикване **_exit()**, за да позволи на ядрото да се справи с останалата част от процеса на прекратяване:

```c
#include <unistd.h>
void _exit (int status);
```

Процесът може да бъде прекратен, ако се изпрати сигнал, чието действие по подразбиране е да прекрати процеса. Такива сигнали са **SIGTERM** и **SIGKILL**.

Когато процес завърши, ядрото изпраща сигнал **SIGCHLD** към родителският процес. По подразбиране този сигнал се игнорира и родителят не предприема никакви действия. Процесите могат да изберат да обработват този сигнал, чрез системните извиквания **signal()** или **sigaction()**.

```c
#include<sys/types.h>
#include<sys/wait.h>
pid_t wait(int status);
int WIFEXITED(status);
int WIFSIGNALED(status);
int WIFSTOPPED(status);
int WIFCONTINUED(status);
int WEXITSTATUS(status);
int WTERMSIG(status);
int WSTOPSIG(status);
int WCOREDUMP(status);
```

- **wait()** връща стойността на идентификатора (**pid**) на дъшерен процес или -1 при грешка.
- Ако никакъв дъщерен процес не е прекратен, извикването блокира, докато дъщерен процес приключи.
- **WIFEXITED** връща вярно (true), ако процесът завърши нормално.
- При нормално прекратяване **WEXITSTATUS** осигурява осем бита, които се предават на **_exit**.
- WIFSIGNALED връща вярно (true), ако сигнал е причинил прекратяването на процеса.
- В случай на прекратяване от сигнал **WTERMSIG** връща номера на този сигнал.
- В случай на прекратяване от сигнал, **WCOREDUMP** връща вярно (true), ако процесът натоварва ядро в отговор на получаването на сигнала.
- **WIFSTOPPED** и **WIFCONTINUED** връщат вярно (true), ако процесът е бил спрян или продължен.
- Ако **WIFSTOPPED** е вярно (true), **WSTOPSIG** предоставя номера на сигнала, който е спрял процеса.

При възникване на грешка има две възможни стойности:

| Грешка | Информация                                          |
| ------ | --------------------------------------------------- |
| ECHILD | Извикващият процес няма дъщерни процеси.            |
| EINTR  | Извикването проключи по-рано поради получен сигнал. |
