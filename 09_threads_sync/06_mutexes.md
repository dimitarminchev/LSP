## Mutexes

**Mutexes** are used to prevent data inconsistencies that can occur when multiple threads operate on the same memory region at the same time, or to prevent **race conditions** when the order of memory operations matters.

A **race condition** often occurs when two or more threads perform operations on the same memory area, and the result depends on the order in which those operations are executed.

Mutexes are used to serialize access to shared resources such as memory. Whenever a global resource is accessed by more than one thread, the resource should have a mutex associated with it.
