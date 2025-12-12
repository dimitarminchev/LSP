## Deadlock

**Deadlock** occurs when a mutex is not released (unlocked) and remains held, preventing progress.

This leads to the program stalling for an indefinite time. Deadlocks can be caused by poorly written application logic or incorrect use of joins.

Be careful when acquiring two or more mutexes in the same section of code. If the first `pthread_mutex_lock` succeeds but the second `pthread_mutex_lock` is blocked because another thread holds that mutex, the first mutex may end up preventing other threads from accessing data — including the thread that holds the second mutex.

Threads may wait indefinitely for a resource to be released, leading to a dead end. It is best to detect failures, release resources, and retry or abort before retrying.
