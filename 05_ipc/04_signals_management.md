## Signal Management

| method        | description                                                                                |
|---------------|--------------------------------------------------------------------------------------------|
| sigemptyset() | initializes an empty signal set with all signals excluded from the set.                    |
| sigfillset()  | initializes a full signal set including all signals.                                       |
| sigaddset()   | adds a signal to a set.                                                                    |
| sigdelset()   | removes a signal from a set.                                                               |
| sigprocmask() | retrieves and/or changes the signal mask of the calling thread.                            |
| sigaction()   | changes the action of a signal.                                                            |
| sigwait()     | waits for a signal.                                                                        |
| strsignal()   | returns a string describing the signal.                                                    |

```c
#include <signal.h>

int sigemptyset (sigget_t *set);
int sigaddset (sigset_t *set, int signo);
int sigprocmask (int how, cont sigset_t *set, sigset_t *oldset);

int sigaction (int signo, const struct sigaction *act, struct sigaction *oldact);

struct sigaction {
  void (*sa_handler)(int);
  void (*sa_sigaction)(int, siginfo_t *, void *);
  sigset_t sa_mark;
  int sa_flags;
  void (*sa_restorer)(void);
};
```

**sigemptyset()** initializes the signal set specified by set by marking it empty (all signals are excluded from the set).

**sigaddset()** adds a signal to the signal set specified by set, while **sigdelset()** removes the signal from the signal set specified by set. Both return 0 on success, or -1 on error, in which case the error is set to error code **EINVAL**, which means the signal is an invalid signal identifier.

The behavior of **sigprocmask()** depends on the value of one of the following:

| Field       | Description                                                      |
|-------------|------------------------------------------------------------------|
| SIG_SETMASK | Sets the signal mask of the calling process.                     |
| SIG_BLOCK   | Signals are added to the signal mask of the calling process.     |
| SIG_UNBLOCK | Signals are removed from the signal mask of the calling process. |

The **sigaction** structure:

| Field        | Description                                                                                                                    |
|--------------|--------------------------------------------------------------------------------------------------------------------------------|
| SA_HANDLER   | Address of the handler SIG_IGN or SIG_DFL                                                                                      |
| SA_MASK      | Signals to block                                                                                                               |
| SA_FLAGS     | Additional flags, such as SA_RESETHAND                                                                                         |
| SA_RESETHAND | Allows "one-shot" mode. The behavior of the given signal returns to default after the signal handler returns.                 |

Calling **sigaction()** changes the behavior of the signal identified by **signo**, which can be any value except those associated with **SIGKILL** and **SIGSTOP**. If **act** is not NULL, the system call changes the current signal behavior as specified in **act**. If **oldact** is not NULL, the system call saves the previous behavior of the given signal (or the current one if **act** is NULL).
