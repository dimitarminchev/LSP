## Process Management

The table below shows commands for managing processes in a Linux operating system:

| Command      | Information                                                    |
| ------------ | -------------------------------------------------------------- |
| ps           | snapshot of current processes.                                 |
| top          | displays Linux processes.                                      |
| kill         | sends a signal to a process.                                   |
| pgrep, pkill | search or signal processes based on name and other attributes. |
| killall      | kills processes by name.                                       |
| Ctrl-C       | kills the foreground process.                                  |
| Ctrl-Z       | suspends the foreground process.                               |
| jobs         | shows the status of jobs.                                      |
| fg           | brings the suspended process to the foreground.                |

More information: 
[https://www.tecmint.com/linux-process-management/](https://www.tecmint.com/linux-process-management/)

Example:
```
$ pgrep -u tecmint top
$ kill 2308
$ pgrep -u tecmint top
$ pgrep -u tecmint glances
$ pkill glances
$ pgrep -u tecmint glances
```