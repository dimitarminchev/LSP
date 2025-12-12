## Reentrancy

When the kernel sends a signal, the process is usually executing some code. This can happen in the middle of an important operation that, if interrupted, will place the process in an inconsistent state. For example, the data structure the process is working with is only half updated or the computation is only partially complete. The process may even be handling another signal.

The signal handler (**signal handler**) does not know exactly what code is being executed by the process at the moment the signal appears, this can happen at any time. For this reason, it is very important that every signal handler (**signal handler**) you write is very careful about the actions it performs and the data it works with.

Signal handlers (**signals handlers**) must take care not to make assumptions about what the process is doing when it is interrupted. In particular, they must be cautious when modifying global and shared data. In general, good practice is for the signal handler to never work with global data.

What about system calls or other library functions? What will happen if the process is in the middle of writing to a file or allocating memory, and a signal handler writes to the same file or calls **malloc()**? What will happen if, when a signal appears, the process is in the middle of calling a function that uses a static buffer, such as **strsignal()**?

For all these reasons, it is very important that every signal handler (**signal handler**) in the process is a **reentrant** function.

**reentrant** is a function that is safe to call from itself (or simultaneously from another thread in the same process). To qualify as **reentrant**, the function must not manipulate static data, must only manipulate data provided by the stack or data provided to it by the calling function, and must not execute a function that is not **reentrant**.

### Standard C functions that are safe to use:
> accept, access, aio_error, aio_return, aio_suspend, alarm, bind, cfgetispeed, cfgetospeed, cfsetispeed, cfsetospeed, chdir, chmod, chown, clock_gettime, close, connect, creat, dup, dup2, execle, execve, _Exit & _exit, fchmod, fchown, fcntl, fdatasync, fork, fpathconf, fstat, fsync, ftruncate, getegid, geteuid, getgid, getgroups, getpeername, getpgrp, getpid, getppid, getsockname, getsockopt, getuid, kill, link, listen, lseek, lstat, mkdir, mkfifo, open, pathconf, pause, pipe, poll,posix_trace_event, pselect, raise, read, readlink, recv, recvfrom, recvmsg, rename, rmdir, select, sem_post, send, sendmsg,sendto, setgid, setpgid, setsid, setsockopt, setuid, shutdown, sigaction, sigaddset, sigdelset, sigemptyset, sigfillset,sigismember, signal, sigpause, sigpending, sigprocmask, sigqueue, sigset, sigsuspend, sleep, socket, socketpair, stat, symlink, sysconf, tcdrain, tcflow, tcflush, tcgetattr, tcgetpgrp, tcsendbreak, tcsetattr, tcsetpgrp, time, timer_getoverrun,timer_gettime, timer_settime, times, umask, uname, unlink, utime, wait, waitpid, write.
