## Daemon skeleton

Steps typically required to daemonize a process:

1. Fork the parent process (`fork`) and let the parent exit; the child continues to run in the background.
2. Create a new session and become session leader (`setsid`). The calling process becomes the leader of a new session and process group and is disassociated from the controlling terminal (CTTY).
3. Catch and handle (or ignore) signals as needed.
4. Fork again (`fork`) and let the parent exit to ensure the daemon cannot reacquire a controlling terminal (only session leaders can acquire a controlling TTY).
5. Change the working directory (`chdir`) to a safe location (commonly `/`).
6. Set an appropriate file mode creation mask (`umask`).
7. Close all open file descriptors inherited from the parent (`close`).

### daemonize.c
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
    /* or another appropriate directory */
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

### Sources
1. [How to Create a Daemon in C?](https://nullraum.net/how-to-create-a-daemon-in-c/)
2. [Basic skeleton of a linux daemon written in C](https://github.com/pasce/daemon-skeleton-linux-c)
