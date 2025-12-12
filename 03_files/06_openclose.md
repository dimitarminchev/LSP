## Opening and Closing a File
- Initialize the variables
- Open the file for read-only and get a file descriptor
- If the file descriptor is -1, print an error message
- Otherwise, print the value of the file descriptor
- Close the file
- If closing fails, output an error message

### openclose.c
```c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char * argv[]) 
{
    int fd;
    fd = open ("/proc/self/environ", O_RDONLY);
    if (fd == -1) {
        printf("ERROR opening 'environ'!\n");
    } else {
        printf("File Descriptor of 'environ' = %d\n", fd);
    }

    // write/read commands to be added here
    if (close (fd) == -1)
        printf("ERROR closing the file!\n");
}
```