## Thread exit

A thread can arrange for functions to be called when the thread exits. These functions are known as **thread cleanup handlers**. More than one cleanup handler can be registered for each thread. Handlers are pushed onto a **stack**, which means they are executed in the reverse order from which they were added.

When a thread is canceled or terminates by calling `pthread_exit()`, all registered cleanup handlers are popped and executed in the reverse order in which they were pushed onto the stack.
