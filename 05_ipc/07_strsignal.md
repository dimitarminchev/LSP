## Examining Signals

```c
#include<string.h>
#include<signal.h>
char *strsignal(int sig);
extern const char * const sys_siglist[];
int sigfillset(sigset_t *set);
int sigdelset(sigset_t *set, int signum);
```

Calling **strsignal()** returns a pointer to a description of the signal given by **signo**.

**sys_siglist** is an array of strings containing the names of the signals supported by the system, indexed by signal number. 