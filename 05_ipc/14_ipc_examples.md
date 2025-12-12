## Inter-Process Communication Exercise
Practice the materials from this topic by implementing the projects presented below.

### Reverse Encryptor Decryptor

Let's define "Reverse Encryption" (**RE**) as a technique for protecting text messages in which the text of the messages is reversed before they are sent further. Write a program **reverse-encryptor-decryptor.c** that has two processes communicating via an anonymous pipe (**anonymous pipe**). 

The following rules must be valid for both processes:
- **Parent process** must read text from the keyboard, then apply the RE technique and send the encoded message to the **Child process**.
- **Child process** must wait for incoming messages, print the encoded messages to the screen, then decode them and store them in the file **reverse-encryptor-decryptor.log**.

### Encrypted Chat

Write a pair of programs for server (**encrypted-chat-server.c**) and client (**encrypted-chat-client.c**). The server should mimic the behavior of the **Parent process** from the previous task, and the client should mimic the **Child process** respectively. The programs should use a named pipe (**named pipe**) as a communication method.
