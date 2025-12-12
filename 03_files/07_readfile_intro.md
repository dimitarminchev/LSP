## Reading File Contents

The **unistd.h** library contains methods for working with files:

```c
#include<unistd.h>
ssize_t read(int fd, void *buf, size_t len);
```

- Each call reads **len** number of bytes into **buf** from the current position of the file specified in the file descriptor **fd**.
- On success, it returns the number of bytes written to **buf**.
- On error, it returns -1, and error information is written to **errno**.

Actually, the read method can lead to many possibilities:
- Returns a value equal to **len** and all read bytes are stored in **buf**. The results are as expected.
- Returns a value less than len but greater than zero. The read bytes are stored in **buf**. This can happen because a signal interrupted the read in the middle, an error occurred in the middle of reading, more than zero but less than the value of len bytes are available, or EOF is reached before len bytes are read. Reissuing the read (with correspondingly updated **buf** and **len** values) will read the remaining bytes into the rest of the buffer or indicate the cause of the problem.
- Returns a value of 0. This indicates **EOF**. There is nothing to read.
- The method call blocks because no data is available. This will not happen in non-blocking mode.
- Returns a value of -1 and the error is set to **EINTR**. This indicates that a signal was received before any bytes were read.
- Returns a value of -1 and the error is set to **EAGAIN**. This indicates that the read would block because no data is currently available. This only happens in non-blocking mode.
- Returns a value of -1 and the error is set to a value other than **EINTR** or **EAGAIN**. This indicates a more serious error.
