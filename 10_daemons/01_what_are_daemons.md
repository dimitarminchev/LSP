## What are daemons?

A **daemon** is a process that runs in the background and is not attached to a controlling terminal.

Typically, daemons are started at system boot, run as `root` or another dedicated user (for example `apache` or `postfix`), and perform system-level tasks. Traditionally many daemon program names end with the letter `d` (for example `crond` and `sshd`), but this is a convention rather than a requirement.

Daemons commonly have two requirements:
- they should run as a child of `init` (or the system's init replacement),
- they must not be attached to a terminal.
