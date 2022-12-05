
## Скелет на демон
Необходими стъпки за демонизиране на процес:

1. Разклонете родителския процес (_Използваме: ` fork `_) и го оставете да се прекрати, ако разклоняването е успешно и тъй като родителският процес е прекратен, дъщерният процес сега работи във фонов режим.
2. Създайте нова сесия и получете идентификатор (_Използваме: ` setsid `_) Извикващият процес става лидер на новата сесия и лидер на групата процеси на новата група процеси. Процесът вече е отделен от управляващия го терминал (CTTY).
3. Уловетеве сигналите, като ги игнорирате и/или обработвате.
4. Разклонете отново (_Използваме: ` fork `_) и оставете родителския процес да се терминира, за да сте сигурни, че сте се отървали от водещия процес на сесията. (Само водещите сесии могат да получат отново TTY.)
5. Променете работната директория на демона (_Използваме: ` chdir `_).
6. Променете маската на файловия режим в съответствие с нуждите на демона (_Използваме: ` umask `_).
7. Затвoрете всички отворени файлови дескриптори, които могат да бъдат наследени от родителския процес (_Използваме: ` close `_).

### daemonaze.c
```c
/*
 * daemonize.c
 * This example daemonizes a process, writes a few log messages,
 * sleeps 20 seconds and terminates afterwards.
 * This is an answer to the stackoverflow question:
 * https://stackoverflow.com/questions/17954432/creating-a-daemon-in-linux/17955149#17955149
 * Fork this code: https://github.com/pasce/daemon-skeleton-linux-c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

static void skeleton_daemon()
{
    pid_t pid;

    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    /* Catch, ignore and handle signals */
    //TODO: Implement a working signal handler */
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    /* Fork off for the second time*/
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* Set new file permissions */
    umask(0);

    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/");

    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
    {
        close (x);
    }

    /* Open the log file */
    openlog ("firstdaemon", LOG_PID, LOG_DAEMON);
}

int main()
{
    skeleton_daemon();

    while (1)
    {
        //TODO: Insert daemon code here.
        syslog (LOG_NOTICE, "First daemon started.");
        sleep (20);
        break;
    }

    syslog (LOG_NOTICE, "First daemon terminated.");
    closelog();

    return EXIT_SUCCESS;
}
```

### Източници
1. [How to Create a Daemon in C?](https://nullraum.net/how-to-create-a-daemon-in-c/)
2. [Basic skeleton of a linux daemon written in C](https://github.com/pasce/daemon-skeleton-linux-c)