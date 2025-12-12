## Thread Cancellation Example

- Create a thread
- Try to cancel it
- Wait for it to finish

```c
pthread_create(&thread, NULL, thread_func, NULL);
pthread_cancel(thread);
pthread_join(thread, NULL);
```

- Mark the thread as non-cancellable
  - ... while it works
  - ... and until we allow cancellation
  - ... and reach a cancellation point

```c
pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
...
pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
pthread_testcancel();
```

- Make the thread cancellable at any time
- But for now mark it in a non-cancellable state
  - ... while it works
  - ... and until we allow cancellation
- The thread is cancelled automatically, no need to reach a cancellation point

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

Compiling the program with explicit instruction to the compiler to support threads:
```
gcc threads-cancel.c -o threads-cancel -lpthread
```
