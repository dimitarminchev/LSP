## Разглеждане на сигнали

```c
#include<string.h>
#include<signal.h>
char *strsignal(int sig);
extern const char * const sys_siglist[];
int sigfillset(sigset_t *set);
int sigdelset(sigset_t *set, int signum);
```

Извикване на **strsignal()** връща указател към описание на сигнала, даден от **signo**.

**sys_siglist** е масив от низове, съдържащи имената на сигналите, поддържани от системата, индексирани с номер на сигнала. 