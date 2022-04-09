## Отваряне и затваряне на файл
- Инициализирайте променливите
- Отворете файла само за четене и получете файлов дескриптор
- Ако файловият дескриптор е -1, отпечатайте съобщение за грешка
- В противен случай, отпечатайте стойността на файловия дескриптор
- Затворете файла
- Ако затварянето е неуспешно, изведете съобщение за грешка

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