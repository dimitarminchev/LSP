## Writing Sentences to a File

Create an empty file **sentences.txt**, in case of failure print an error and exit.
Do the following 100 times: call **getSentence()** to get new text in the buffer and its length, write the buffer to the file and record the number of bytes.
If the number of written bytes is -1, print an error and exit.
Close the file, output an error in case of failure.

### writefile.c
```c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <string.h>
#define BUF_SIZE 1000000
long getMicrotime(){
        struct timeval currentTime;
        gettimeofday(&currentTime, NULL);
        return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}
int getSentence(char *buf) {
    sprintf(buf, "%ld> This is a new sentence.\n", getMicrotime());
    return strlen(buf);
}
int main(int argc, char *argv[])
{
    int fd;
    fd = open("./sentences.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        printf("ERROR opening the file!\n");
        return -1;
    }
    char buf[BUF_SIZE];
    for (int i=0; i < 100; i++)
    {
        int text_len = getSentence(buf);
        ssize_t nr = write(fd, buf, text_len);
        if (nr == -1)
        {
            printf("ERROR writing to the file!\n");
            break;
        }
    }
    if (close(fd) == -1)
    {
        printf("ERROR closing the file!\n");
        return -2;
    }
    printf("SUCCESS!\n");
    return 0;
}
```