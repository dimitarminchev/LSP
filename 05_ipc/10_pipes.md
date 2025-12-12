## Anonymous and Named Pipes

### Anonymous Pipes

An anonymous pipe (_English term: Anonymous pipe_) is a simple **FIFO** communication channel that can be used for unidirectional inter-process communication (IPC). Typically, the parent program opens anonymous pipes and creates a new process that inherits the other ends of the pipes. The anonymous pipe lasts only as long as the process lasts.

### Named Pipes

A named pipe (_English term: Named pipe_) is an extension of the concept of traditional anonymous pipes. A named pipe can be identified by name and shown as a file in the system. A named pipe can continue to exist as long as the computer system is on, not just during the lifetime of the process. A named pipe can be deleted if it is no longer being used.
