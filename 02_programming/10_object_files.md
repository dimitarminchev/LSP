## Object Files

To create the object files (directory libexample) use the following command:

```
gcc -c src/main.c -o bin/main.o
```

To create the object files intended for a static library, use:

```
gcc -c src/addlib/add.c -o bin/static/add.o
gcc -c src/addlib/answer.c -o bin/static/answer.o
```

To create the object files intended for a shared library, use:

```
gcc -c -fPIC src/addlib/add.c    -o bin/shared/add.o
gcc -c -fPIC src/addlib/answer.c -o bin/shared/answer.o
```
