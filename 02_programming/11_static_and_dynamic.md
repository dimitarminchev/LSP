## Static and Dynamic Library

Combine the files of the objects into a single static library/archive using the command:

```
ar rcs bin/static/libadd.a bin/static/add.o bin/static/answer.o
```

Link the static main.o with the library using the command:

```
gcc bin/main.o -Lbin/static –ladd -o bin/statically-linked
```

For a shared library in GCC ending with .so instead of .a, use the command:

```
gcc -shared bin/shared/add.o bin/shared/answer.o -o bin/shared/libadd.so
```

Connect dynamically to the shared library using the command:

```
gcc bin/main.o -Lbin/shared -ladd -o bin/use-shared-library
```

Move the shared library to the default location:

```
sudo mv bin/shared/libadd.so /usr/lib
sudo chmod u=rwx,go=rx  /usr/lib/libadd.so
```

Use the shared library through **LD_LIBRARY_PATH**:

```
LD_LIBRARY_PATH=$(pwd)/bin/shared bin/use-shared-library
```
