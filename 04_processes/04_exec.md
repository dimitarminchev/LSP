## Executing a Command

```c
#include<unistd.h>
int execl (const char *path, const char *arg, ...);
int execlp (const char *file, const char *arg, ...);
int execle (const char *path, const char *arg, ..., char *const envp[]);
int execv (const char *path, char *const argv[]);
int execvp (const char *file, char *const argv[]);
int execve (const char *filename, char * const argv[], char *const envp[]);
```

Useful notes:
- **l** and **v** indicate whether arguments are provided via a list or an array (vector).
- **p** means that the user's path is searched for the given file. Commands using the p variants can specify only a filename, as long as it is located in the user's path.
- **e** indicates that a new environment is also provided for the new process.

### Error Values
On success, the system calls do not return. 
On failure, the system calls return -1 and set the error to one of the following values:

| Стойност | Информация                                                                                                                                                                                                          |
|----------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| E2BIG    | Общият брой байтове в предоставения аргумент (arg) или средата (envp) е твърде голям.                                                                                                                               |
| EACCESS  | Процесът няма разрешение за търсене на компонент в пътя; пътя не е обикновен файл; целевият файл не е маркиран като изпълним; или файловата система, на която се намира пътя или файла не е монтиран като изпълним. |
| EFAULT   | Даденият указател не е валиден.                                                                                                                                                                                     |
| EIO      | Възникна грешка вход / изход на ниско ниво (това е лошо).                                                                                                                                                           |
| EISDIR   | Крайният компонент в пътя или интерпретаторът е директория.                                                                                                                                                         |
| ELOOP    | Системата е срещнала твърде много символични връзки в пътя.                                                                                                                                                         |
| EMFILE   | Процесът на извикване достигна своята граница за отворените файлове.                                                                                                                                                |
| ENFILE   | Беше достигнато ограничението за отворените файлове в цялата система.                                                                                                                                               |
| ENOENT   | Целта на пътя или файла не съществува или необходимата споделена библиотека не съществува.                                                                                                                          |
| ENOEXEC  | Целта на пътя или файла е невалидна програма или е предназначена за различна архитектура.                                                                                                                           |
| ENOMEM   | Няма достатъчно памет на ядрото за изпълнение на нова програма.                                                                                                                                                     |
| ENOTDIR  | Непълен компонент в пътя не е директория.                                                                                                                                                                           |
| EPERM    | Файловата система, на която се намира пътят или файла, е монтирана nosuid, потребителят не е root и пътя или файл има зададен suid или sgid бит.                                                                    |
| ETXTBSY  | Целта или файла е отворен за писане от друг процес.                                                                                                                                                                 |