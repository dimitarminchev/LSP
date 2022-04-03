## Пример за прекратяване на нишки

- Създаваме нишка
- Опитваме да я прекратим
- Изчакваме я да приключи

```c
pthread_create(&thread, NULL, thread_func, NULL);
pthread_cancel(thread);
pthread_join(thread, NULL);
```

- Маркираме нишката като неотменима
- ... докато работи
- ... и докато не разрешим прекратяване
- ... и достигнем точка за прекратяване

```c
pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
...
pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
pthread_testcancel();
```

- Правим нишката отменима по всяко време
- Но засега я маркираме в неотменяемо състояние
- ... докато работи
- ... и докато не разрешим прекратяване
- Нишката се прекратяване автоматично, няма нужда да достигаме до точка за прекратяване

```c
pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
...
pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
```

### threads-cancel.c
```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
int i;
void * thread_func(void * arg)
{
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
  for(i=0; i<4; i++)
  {
     sleep(1);
     printf("I am running verry important process %i ...\n", i+1);
  }
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  pthread_testcancel();
  printf("YOU WILL NOT STOP ME!!!\n");
}
int main(int argc, char * argv[])
{
  pthread_t thread;
  pthread_create(&thread, NULL, thread_func, NULL);
  while(i < 1) sleep(1);
  pthread_cancel(thread);
  printf("Requsted to cancel the thread!\n");
  pthread_join(thread, NULL);
  printf("The thread is stopped!\n");
  return EXIT_SUCCESS; // 0
}
```

Компилиране на програмата с изрична инструкция към компилатора да поддръжка нишки:
```
gcc threads-cancel.c -o threads-cancel -lpthread
```
