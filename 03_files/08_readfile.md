## Reading and Printing a File

Initialize the variables.
Open the file **readfile.c**, print an error if there's a problem.
While reading from the file returns a length different from 0.
If the length is -1 and the error is **EINTR**, try to read again.
If the length is -1 and the error is not **EINTR**, output an error and stop.
Otherwise, print the buffer.
Close the file, print an error if there's a problem.

### readfile.c
```c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#define BUF_SIZE 1000000
int main(int argc, char *argv[])
{
    int fd = open("./readfile.c", O_RDONLY);
    if (fd == -1)
    {
        printf("ERROR opening the file!\n");
        return -1;
    }
    ssize_t len;
    char buf[BUF_SIZE];
    while ((len = read(fd, buf, BUF_SIZE - 1)) != 0)
    {
        if (len == -1)
        {
            if (errno == EINTR) continue;
            printf("ERROR reading the file!\n");
            break;
        }
        printf("%s", buf);
    }
    if (close(fd) == -1)
    {
        printf("ERROR closing the file!\n");
        return -2;
    }
    return 0;
}
```
