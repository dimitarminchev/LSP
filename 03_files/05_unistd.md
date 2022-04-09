## Библиотека за работа с файлове

Библиотеката **unistd.h** съдържа методи за работа с файлове:
```c
#include<unistd.h>
int open(const char *name, int flags);
int open(const char* name, int flags, mode_t mode);
int close();
```

Параметъра флаг (**flag**) е бит маска определяща следното:

| флаг         |  Информация                                                  |
| ----------- | ------------------------------------------------------------ |
| O_APPEND    | Файлът ще бъде отворен в режим на добавяне.                  |
| O_ASYNC     | SIGIO се генерира, когато може да се чете или да се записва. |
| O_CREAT     | Ако файлът не съществува го създава.                         |
| O_DIRECT    | Отваря файла за директен вход/изход.                         |
| O_DIRECTORY | Ако името не е директория, то дава грешка                    |
| O_EXCL      | Ако O_CREAT и файлът съществува, то дава грешка.             |
| O_LARGEFILE | Отваря файл по-голям от 2 ГБ                                 |
| O_NOCTTY    | Този флаг не се използва                                     |
| O_NOFOLLOW  | Ако name е символна връзка, то дава грешка                   |
| O_NONBLOCK  | Ако е възможно, отваря файла в неблокиращ режим.             |
| O_SYNC      | Файлът ще бъде отворен за синхронен Вход/Изход               |
| O_TRUNC     | Ако файлът съществува, той се съкращава до нулева дължина    |

В случай че е зададен флаг **O_CREAT**, то режима на работа е бит маска, както следва:

|         |         |         |         |
| ------- | ------- | ------- | ------- |
| S_IRWXU | S_IXUSR | S_IWGRP | S_IROTH |
| S_IRUSR | S_IRWXG | S_IXGRP | S_IWOTH |
| S_IWUSR | S_IRGRP | S_IRWXO | S_IXOTH |