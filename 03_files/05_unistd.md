## Library for Working with Files

The **unistd.h** library contains methods for working with files:
```c
#include<unistd.h>
int open(const char *name, int flags);
int open(const char* name, int flags, mode_t mode);
int close();
```

The flag parameter (**flag**) is a bitmask defining the following:

| flag        | Information                                                   |
| ----------- | ------------------------------------------------------------- |
| O_APPEND    | The file will be opened in append mode.                       |
| O_ASYNC     | SIGIO is generated when it can be read or written.            |
| O_CREAT     | If the file does not exist, it creates it.                    |
| O_DIRECT    | Opens the file for direct input/output.                       |
| O_DIRECTORY | If the name is not a directory, it gives an error             |
| O_EXCL      | If O_CREAT and the file exists, it gives an error.            |
| O_LARGEFILE | Opens a file larger than 2 GB                                 |
| O_NOCTTY    | This flag is not used                                         |
| O_NOFOLLOW  | If name is a symbolic link, it gives an error                 |
| O_NONBLOCK  | If possible, opens the file in non-blocking mode.             |
| O_SYNC      | The file will be opened for synchronous Input/Output          |
| O_TRUNC     | If the file exists, it is truncated to zero length            |

In case the **O_CREAT** flag is set, the mode is a bitmask as follows:

|         |         |         |         |
| ------- | ------- | ------- | ------- |
| S_IRWXU | S_IXUSR | S_IWGRP | S_IROTH |
| S_IRUSR | S_IRWXG | S_IXGRP | S_IWOTH |
| S_IWUSR | S_IRGRP | S_IRWXO | S_IXOTH |