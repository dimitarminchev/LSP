## Създаване на обектните файлове

За създаване на обектните файлове (директория libexample) използвайте следната команда:

```
gcc –c src/main.c -o bin/main.o
```

За създаване на обектните файлове предназначени за статична библиотека, използвайте:

```
gcc –c src/addlib/add.c -o bin/static/add.o
gcc –c src/addlib/answer.c -o bin/static/answer.o
```

За създаване на обектните файлове предназначени за споделена библиотека, използвайте:

```
gcc -c -fPIC src/addlib/add.c    -o bin/shared/add.o
gcc -c -fPIC src/addlib/answer.c -o bin/shared/answer.o
```
