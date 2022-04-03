## Функции за прекратяване на нишки

```c
int pthread_cancel(pthread_t thread);
```
изпраща заявка за прекратяване на нишка **thread**.  

```c
int pthread_setcancelstate(int state, int *oldstate);
```
задава състояние за прекратяване на нишката посредством **state** на **PTHREAD_CANCEL_ENABLE** или **PTHREAD_CANCEL_DISABLE**

```c
int pthread_setcanceltype(int type, int *oldtype);
```
задава тип за прекратяване на нишката посредством **type** на **PTHREAD_CANCEL_DEFERRED** или **PTHREAD_CANCEL_ASYNCHRONOUS**