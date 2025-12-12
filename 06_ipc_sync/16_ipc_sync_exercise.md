## Inter-Process Communication Synchronization Exercise
Practice the materials from this topic by implementing the projects presented below.

### Double Shared Memory
Write a pair of server and client programs (**double-memory-server.c** and **double-memory-client.c**) that share memory blocks between them. The server should support up to 2 clients simultaneously, which should not conflict during operation. The server initializes the shared memory with greeting messages for its clients and waits for them to change with their messages. When the client writes a new message, the server responds with the same message but with the expression **Confirmed!** at the end.
 
The client is started with one argument: **client_number**, which identifies the client (1 or 2) to the server. The client should continuously print the message from the shared memory, read a line from the keyboard, and write it to the shared memory. The program should exit when the message "q" is entered.

### Double Dumper
Write a program **double-dumper.c** that shows the changes in the shared memory from the **Double Shared Memory** project in real time. You may need to modify the server or client programs to support this functionality.