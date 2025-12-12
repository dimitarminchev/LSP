## Methods for Working with Processes

The table below shows C methods used in process programming in a Linux operating system:

| Command                                                   | Information                                                    |
| --------------------------------------------------------- | -------------------------------------------------------------- |
| getpid()                                                  | returns the **pid** identifier of the calling process.         |
| getppid()                                                 | returns the **pid** identifier of the parent process.          |
| execl(), execlp(), execle(), execv(), execvp(), execvpe() | execute a command.                                             |
| fork()                                                    | creates a child process.                                       |
| exit()                                                    | causes normal process termination.                             |
| wait(), waitpid(), waitid()                               | waits for the process to change status.                        |
