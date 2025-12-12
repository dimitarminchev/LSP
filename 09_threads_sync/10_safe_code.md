## Thread-safe code

`Thread-safe code` means that functions may be called by multiple threads safely.

This implies there are no static or global variables that other threads can corrupt or read concurrently. If static or global variables are used, either protect them with mutexes or rewrite the functions to avoid using shared state.

In C, local variables are allocated on the stack. Therefore any function that does not use static data or other shared resources is thread-safe.

Functions that are not thread-safe should only be used by one thread at a time in the program, and the program must ensure exclusive access.
