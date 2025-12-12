## Most Important Signals

| signal                   | information                                                                                                                                                                                        | result                   |
|--------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|--------------------------|
| SIGHUP (1)               | The process's controlling terminal is closed (most often the user has logged out).                                                                                                                 | Terminate                |
| SIGINT (2)               | The user uses the interrupt combination Ctrl-C.                                                                                                                                                    | Terminate                |
| SIGABRT (6)              | The abort() function sends this signal to the process that invokes it. The process then terminates and a core file is generated.                                                                   | Terminate with core dump |
| SIGKILL (9)              | This signal is sent by the kill() system call, it exists to provide a safe way to unconditionally kill a process.                                                                                  | Terminate                |
| SIGSEGV (11)             | This signal, whose name derives from segmentation violation, is sent to a process when it attempts invalid memory access.                                                                          | Terminate with core dump |
| SIGTERM (15)             | This signal is sent only via kill() and allows the user to gracefully terminate a process (default action).                                                                                        | Terminate                |
| SIGCHLD (17)             | When a process terminates or stops, the kernel sends this signal to the parent. The handler for this signal typically calls wait() to determine the child process identifier (pid) and exit code. | Ignored                  |
| SIGCONT (18)             | The kernel sends this signal to a process when the process resumes after stopping (from SIGSTOP).                                                                                                  | Ignored                  |
| SIGSTOP (19)             | This signal is sent only via kill(), it unconditionally stops a process and cannot be caught or ignored.                                                                                           | Stop                     |
| SIGTSTP (20)             | The kernel sends this signal to all processes in the foreground group when the user uses the Ctrl-Z combination.                                                                                   | Stop                     |
| SIGIO (29)               | This signal is sent when an asynchronous I/O event is generated.                                                                                                                                   | Terminate                |
| SIGUSR1(10), SIGUSR2(12) | These signals are available for user-defined purposes; the kernel never uses them. Processes can use SIGUSR1 and SIGUSR2.                                                                          | Terminate                |

### Signals in Linux
Execute following terminal command to view signal list:
```
kill -l
``` 
Result:
```
 1) SIGHUP       2) SIGINT       3) SIGQUIT      4) SIGILL       5) SIGTRAP
 6) SIGABRT      7) SIGBUS       8) SIGFPE       9) SIGKILL     10) SIGUSR1
11) SIGSEGV     12) SIGUSR2     13) SIGPIPE     14) SIGALRM     15) SIGTERM
16) SIGSTKFLT   17) SIGCHLD     18) SIGCONT     19) SIGSTOP     20) SIGTSTP
21) SIGTTIN     22) SIGTTOU     23) SIGURG      24) SIGXCPU     25) SIGXFSZ
26) SIGVTALRM   27) SIGPROF     28) SIGWINCH    29) SIGIO       30) SIGPWR
31) SIGSYS      34) SIGRTMIN    35) SIGRTMIN+1  36) SIGRTMIN+2  37) SIGRTMIN+3
38) SIGRTMIN+4  39) SIGRTMIN+5  40) SIGRTMIN+6  41) SIGRTMIN+7  42) SIGRTMIN+8
43) SIGRTMIN+9  44) SIGRTMIN+10 45) SIGRTMIN+11 46) SIGRTMIN+12 47) SIGRTMIN+13
48) SIGRTMIN+14 49) SIGRTMIN+15 50) SIGRTMAX-14 51) SIGRTMAX-13 52) SIGRTMAX-12
53) SIGRTMAX-11 54) SIGRTMAX-10 55) SIGRTMAX-9  56) SIGRTMAX-8  57) SIGRTMAX-7
58) SIGRTMAX-6  59) SIGRTMAX-5  60) SIGRTMAX-4  61) SIGRTMAX-3  62) SIGRTMAX-2
63) SIGRTMAX-1  64) SIGRTMAX
```
https://dsa.cs.tsinghua.edu.cn/oj/static/unix_signal.html

Execute following terminal command to view signal(7) manual:
```
man 7 signal
```
https://man7.org/linux/man-pages/man7/signal.7.html

