## Най-важните сигнали

| сигнал                   | информация                                                                                                                                                                                            | резултат                 |
|--------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|--------------------------|
| SIGHUP (1)               | Контролният терминал на процеса е затворен (най-често потребителят е излязъл).                                                                                                                        | Terminate                |
| SIGINT (2)               | Потребителят използва комбинация за прекъсване Ctrl-C.                                                                                                                                                | Terminate                |
| SIGABRT (6)              | Функцията abort() изпраща този сигнал до процеса, който го предизвиква. След това процесът се прекратява и се генерира основен файл.                                                                  | Terminate with core dump |
| SIGKILL (9)              | Този сигнал се изпраща от системното повикване kill(), той съществува, за да осигури сигурен начин за безусловно убиване на процес.                                                                   | Terminate                |
| SIGSEGV (11)             | Този сигнал, чието име произтича от нарушаване на сегментирането, се изпраща в процес, когато се опитва невалиден достъп до паметта.                                                                  | Terminate with core dump |
| SIGTERM (15)             | Този сигнал се изпраща само чрез kill() и позволява на потребителя грациозно да прекрати процес (действие по подразбиране).                                                                           | Terminate                |
| SIGCHLD (17)             | Когато процес завърши или спре, ядрото изпраща този сигнал към родителя. Обработващият този сигнал обикновено извиква wait(), за да определи идентификатора на дъщерния процес (pid) и кода за изход. | Ignored                  |
| SIGCONT (18)             | Ядрото изпраща този сигнал на процес, когато процесът се възобновява след спиране (от SIGSTOP).                                                                                                       | Ignored                  |
| SIGSTOP (19)             | Този сигнал се изпраща само чрез kill(), той безусловно спира процес и не може да бъде уловена или пренебрегната.                                                                                     | Stop                     |
| SIGTSTP (20)             | Ядрото изпраща този сигнал до всички процеси от групата на преден план, когато потребителят използва комбинация Ctrl-Z.                                                                               | Stop                     |
| SIGIO (29)               | Този сигнал се изпраща, когато се генерира асинхронно входно-изходно събитие.                                                                                                                         | Terminate                |
| SIGUSR1(10), SIGUSR2(12) | Тези сигнали са налице за цели определени от потребителя; ядрото никога не ги използва. Процесите могат да използват SIGUSR1 и SIGUSR2.                                                               | Terminate                |

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

