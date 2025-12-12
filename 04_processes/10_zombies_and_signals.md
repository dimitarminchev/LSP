## Zombies and Simple Signal Handling

When a child process dies before the parent process, the kernel places it in a special state called zombie (**zombie**). The process in this state waits for the parent process to query its status, and only then does the child process cease to exist as a zombie. If the parent process never queries the child process's status, then the zombie becomes a ghost (**ghost**), which is very bad practice. If the parent process terminates before its child processes, then their parent becomes the init process. The init process, in turn, periodically waits for all its child processes, thus ensuring that none of them remain zombies.

Waiting for a process:
```c
#include<sys/wait.h>
pid_t waitpid(pid_t pid, int *wstatus, int options);
```

Signal handling:
```c
#include<signal.h>
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
struct sigaction {
  void (*sa_handler)(int);
  void (*sa_sigaction)(int, siginfo_t *, void *);
  sigset_t sa_mask;
  int sa_flags;
  void (*sa_restorer)(void);
};
```

But what happens if the parent process dies before the child process, or if it dies before it has a chance to wait for its zombies? Every time a process terminates, the Linux kernel reviews the list of child processes and reparents them to the init process (process identifier pid = 1). This ensures that no process will be left without a parent. The init process, in turn, periodically waits for all its child processes, thus ensuring that none of them remain zombies for too long. Although this is still considered good practice, this safeguard means that short-lived processes should not worry excessively about waiting for all their children.