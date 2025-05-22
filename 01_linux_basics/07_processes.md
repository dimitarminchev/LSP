## Processes in Linux

The main task of operating systems is to execute computer programs. When each program is started, one or more **processes** are created, which effectively represent program code in execution. But in addition to static code, they also consist of data, resources, state, and a virtualized computer. 

In Linux, each process is represented by a unique identifier called **pid**. When there are no active processes, the operating system idlely runs a special **idle process** (Term in English: Idle Process), which has the unique identifier **pid = 0**. 

Processes can create other processes, with the original process referred to as the **parent** and the newly created one called the **child**. In this way, hierarchical groups of processes are created, which can communicate and share resources with each other.

Every process is owned by a user and a group registered in the operating system. In most cases, it is the user who launched the application and the corresponding group to which they belong.
