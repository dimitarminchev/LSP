## Заключване на файлове

Използвайте методът **fcntl()**, който осигурява указател към структурата **flock**. Това извикване манипулира файловия дескриптор **fd**, в зависимост от командата **cmd**:

- За да заключите блок на файл, използвайте **F_SETLK**.
- Ако блокът вече е заключен, използвайте **F_GETLK**, за да получите информация за процеса на заключване.
- За да отключите блок на файл, използвайте **F_SETLK**, но задайте **flock.l_type = F_UNLCK**.

```c
#include<stdio.h>
FILE *fopen(const char *pathname, const char *mode);
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
int fseek(FILE *stream, long offset, int whence);
int fclose(FILE * stream);
```

Структурата flock
```c
struct flock {
   ...
   short l_type;   // F_RDLCK, F_WRLCK, F_UNLCK
   short l_whence; // SEEK_SET, SEEK_CUR, SEEK_END
   
   off_t l_start;  // Starting offset for lock
   off_t l_len;    // Number of bytes to lock
   
   pid_t l_pid;    // PID of process blocking our lock
   ...
}
```
