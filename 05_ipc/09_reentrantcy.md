## Reentrancy

Когато ядрото изпрати сигнал, процесът обикновенно изпълнява някакъв код. Това може да се случи в средата на важна за него операция, която ако бъде прекъсната, ще постави процеса в несъгласувано състояние. Например структурата данни с която процесът работи е само наполовина актуализирана или изчислението е изпълнено само частично. Процесът дори може да обработва друг сигнал. 

Обработчика на сигнал (**signal handler**) не знае точно кой код се изпълнява от процеса в момента на поява на сигналът, това може да се случи по всяко време. Поради тази причина е много важно всеки обработчик на сигнал (**signal handler**), който напишете, да бъде много внимателен относно действията, които извършва и данните с които работи.

Обработчиците на сигнали (**signals handlers**), трябва да се погрижат да не правят предположения за това, какво прави процесът, когато бъде прекъснат. По-специално, те трябва да са предпазливи при модифициране на глобални и споделени данни. Като цяло, добра практика е обработчика на сигнал никога да не работи с глобални данни.

Какво ще кажете за системните извиквания или другите библиотечни функции? Какво ще стане, ако процесът е по средата на писане във файл или разпределяне на памет, и обработващ сигнал пише в същия файл или извика **malloc()**? Какво ще стане, ако при поява на сигнал, процесът е по средата на извикване на функция, която използва статичен буфер, например като **strsignal()**?

Поради всички изброени причини е много важно всеки обработчик на сигнал (**signal handler**) от процеса да е **reentrant** функция.

**reentrant** е функция която е безопасно да се извиква от самата нея (или едновременно от друга нишка в същия процес). За да се квалифицира като **reentrant**, функцията не трябва да манипулира статични данни, трябва да манипулира само данни, предоставени от стека, или данни, предоставени й от извикващия функцията, и не трябва да изпълнява функция която не е **reentrant**.

### Стандартните C функции, безопасни за употреба са:
> accept, access, aio_error, aio_return, aio_suspend, alarm, bind, cfgetispeed, cfgetospeed, cfsetispeed, cfsetospeed, chdir, chmod, chown, clock_gettime, close, connect, creat, dup, dup2, execle, execve, _Exit & _exit, fchmod, fchown, fcntl, fdatasync, fork, fpathconf, fstat, fsync, ftruncate, getegid, geteuid, getgid, getgroups, getpeername, getpgrp, getpid, getppid, getsockname, getsockopt, getuid, kill, link, listen, lseek, lstat, mkdir, mkfifo, open, pathconf, pause, pipe, poll,posix_trace_event, pselect, raise, read, readlink, recv, recvfrom, recvmsg, rename, rmdir, select, sem_post, send, sendmsg,sendto, setgid, setpgid, setsid, setsockopt, setuid, shutdown, sigaction, sigaddset, sigdelset, sigemptyset, sigfillset,sigismember, signal, sigpause, sigpending, sigprocmask, sigqueue, sigset, sigsuspend, sleep, socket, socketpair, stat, symlink, sysconf, tcdrain, tcflow, tcflush, tcgetattr, tcgetpgrp, tcsendbreak, tcsetattr, tcsetpgrp, time, timer_getoverrun,timer_gettime, timer_settime, times, umask, uname, unlink, utime, wait, waitpid, write.
