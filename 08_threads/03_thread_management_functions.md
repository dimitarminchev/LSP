## Thread Management Functions

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
```
starts a new thread in the calling process

```c
int pthread_join(pthread_t thread, void **retval);
```
waits for the specified thread to terminate

```c
void pthread_exit(void *retval);
```
terminates the calling thread and returns a value via retval, which (if the thread is joinable) is available to another thread in the same process that calls **pthread_join**.
