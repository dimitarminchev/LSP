## Working with Files in C

Before a file can be read or written, it must be opened. The kernel maintains a list of open files called the file table. This table is indexed by non-negative integers known as file descriptors (often abbreviated as fds). Each entry in the list contains information about an open file, including a pointer to an in-memory copy of the file's backing inode and associated metadata, such as file position and access modes. Both user space and kernel space use file descriptors as unique "cookies" during operation. Opening a file returns a file descriptor, and subsequent operations (read, write, etc.) accept the file descriptor as a primary argument.

Basic methods for working with files are presented in the table below:

| Method   | Description                                                 |
| -------- | ----------------------------------------------------------- |
| fopen()  | Opens a file and returns a file descriptor                  |
| fread()  | Reads data from a file                                      |
| fwrite() | Writes data to a file                                       |
| fflush() | Flushes the stream                                          |
| close()  | Closes the file descriptor                                  |
| fseek()  | Sets the file descriptor position to a given value          |
| fcntl()  | Manipulates the file descriptor (e.g., for locking)         |
| errno    | Number of the last error                                    |
