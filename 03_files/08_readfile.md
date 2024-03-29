## Четене и отпечатване на файл

Инициализирайте променливите.
Отворете файла **readfile.c**, при проблем отпечатайте грешка.
Докато четенето от файла връща дължина различна от 0.
Ако дължината е -1 и грешката е **EINTR**, опитайте да прочетете отново.
Ако дължината е -1 и грешката <> **EINTR**, изведете грешка и преустановете.
В противен случай отпечатайте буфера.
Затворете файла, отпечатайте грешка при проблем.

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
