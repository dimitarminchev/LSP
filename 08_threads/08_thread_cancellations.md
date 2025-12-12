## Thread Cancellation Functions

```c
int pthread_cancel(pthread_t thread);
```
sends a cancellation request to the thread **thread**.  

```c
int pthread_setcancelstate(int state, int *oldstate);
```
sets the cancellation state of the thread via **state** to **PTHREAD_CANCEL_ENABLE** or **PTHREAD_CANCEL_DISABLE**

```c
int pthread_setcanceltype(int type, int *oldtype);
```
sets the cancellation type of the thread via **type** to **PTHREAD_CANCEL_DEFERRED** or **PTHREAD_CANCEL_ASYNCHRONOUS**