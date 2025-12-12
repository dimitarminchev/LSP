## Signals

Signals are a mechanism for unidirectional asynchronous notifications. A signal can be sent from the kernel to a process, from a process to another process, or from a process to itself. Signals typically alert a process to some event, such as a segmentation fault or a user pressing the **Ctrl-C** key combination.

The Linux kernel implements around 30 signals (the exact number depends on the architecture).

Each signal is represented by a numeric constant and a text name. For example, **SIGHUP**, used to signal that a terminal hangup has occurred, has a value of 1 on the i386 architecture.

With the exception of **SIGKILL** (which always terminates the process) and **SIGSTOP** (which always stops the process), processes can control what happens when they receive a signal.

They can accept the default action, which can be terminating the process, terminating the process and dumping core, stopping the process, or nothing depending on the signal. Alternatively, processes can explicitly choose to ignore or handle signals. Ignored signals are silent.

Handled signals cause execution of a user signal handler function. The program jumps to this function as soon as the signal is received and (when the signal handler returns), program control resumes at the previously interrupted instruction.
