## Creating Threads

Initially your **main()** program consists of a single, default thread. 
All other threads must be explicitly created by the programmer. 
pthread_create creates a new thread and makes it executable. 
This routine can be called any number of times from anywhere within your code.

**pthread_create** arguments:

- **thread**: a unique identifier for the new thread, returned by the subroutine.
- **attr**: an attribute object that may be used to set thread attributes. You can specify a thread attributes object, or NULL for the default values.
- **start_routine**: the routine that the thread will execute once it is created.
- **arg**: a single argument that may be passed to start_routine. It must be passed by reference as a pointer cast of type void. NULL may be used if no argument is to be passed.