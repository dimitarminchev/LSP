## Thread Library

The **pthreads** library defines a set of C programming language types, functions and constants, 
which support applications with requirements for multiple flows of control, called threads, within a single process. 

There are about 100 thread procedures, all with the prefix **pthread_** and they can be categorized into four groups:

| Group                   | Description                                                           |
| ----------------------- | --------------------------------------------------------------------- |
| **Thread management**   | Thread management, creating and joining threads                       |
| **Mutexes**             | Mutexes                                                               |
| **Condition variables** | Condition variables                                                   |
| **Synchronization**     | Synchronization between threads using read/write locking             |

_Note: In this topic we will focus only on "Thread management"._