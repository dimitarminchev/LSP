## Създаване на статична и динамична библиотеки

Комбинирайте файловете на обектите в една статична библиотека / архив, посредством командата:

```
ar rcs bin/static/libadd.a bin/static/add.o bin/static/answer.o
```

Свържете статично main.o с библиотеката, посредством командата:

```
gcc bin/main.o -Lbin/static –ladd -o bin/statically-linked
```

За споделена библиотека на GCC завършваща с .so вместо с .a, използвайте командата:

```
gcc -shared bin/shared/add.o bin/shared/answer.o -o bin/shared/libadd.so
```

Свържете се динамично със споделената билиотека, посредством командата:

```
gcc bin/main.o -Lbin/shared -ladd -o bin/use-shared-library
```

Преместете споделената библиотека в местоположението по-подразбиране:

```
sudo mv bin/shared/libadd.so /usr/lib
sudo chmod u=rwx,go=rx  /usr/lib/libadd.so
```

Използвайте споделената библиотека посредтсвом **LD_LIBRARY_PATH**:

```
LD_LIBRARY_PATH=$(pwd)/bin/shared bin/use-shared-library
```
