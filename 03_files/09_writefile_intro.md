## Четене и писане на файл

```c
#include<unistd.h>
ssize_t write(int fd, const coid *buf, size_t count);
```

Библиотеката **unistd.h** съдържа методи за работа с файлове:
- Записва **count** на брой байтове, започващи от **buf** до текущата позиция във файла, посочен от файловия дескриптор **fd**.
- При успех се връща броят на записани байтове и се актуализира текущата позиция във файла.
- При грешка в резултат се връща -1, а информацията се записва във **errno**.

### Note:

> When a call to write( ) returns, the kernel has copied the data from the supplied buffer into a kernel buffer, but there is no guarantee that the data has been written out to its intended destination. Indeed, write calls return much too fast for that to be the case. The disparity in performance between processors and hard disks would make such behavior painfully obvious. 
>
> Instead, when a user-space application issues a write( ) system call, the Linux kernel performs a few checks, and then simply copies the data into a buffer. Later, in the background, the kernel gathers up all of the "dirty" buffers, sorts them optimally, and writes them out to disk (a process known as writeback). This allows write calls to occur lightning fast, returning almost immediately. It also allows the kernel to defer writes to more idle periods, and batch many writes together.
>
> The delayed writes do not change POSIX semantics. For example, if a read is issued for a piece of just-written data that lives in a buffer and is not yet on disk, the request will be satisfied from the buffer, and not cause a read from the "stale" data on disk. This behavior actually improves performance, as the read is satisfied from an in-memory cache without having to go to disk. The read and write requests interleave as intended, and the results are as expected—that is, if the system does not crash before the data makes it to disk! Even though an application may believe that a write has occurred successfully, in this event, the data will never make it to disk. 
