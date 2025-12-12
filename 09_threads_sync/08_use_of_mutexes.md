## Typical use of mutexes

A typical sequence when using a mutex is:

- Create and initialize a mutex variable
- Multiple threads attempt to lock the mutex
- Only one succeeds and that thread owns the mutex
- The owning thread performs some set of actions
- The owner unlocks the mutex
- Another thread acquires the mutex and the process repeats
- Finally the mutex is destroyed

When multiple threads race for a mutex, the losing threads block on the call, but it is possible to use a `trylock()` variant where losing threads are not blocked.

When protecting shared data, every thread that needs to access the data must use the mutex. For example, if four threads update the same data but only one uses a mutex, the data can still become corrupted.
