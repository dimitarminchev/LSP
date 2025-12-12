## Defining Common Data

- Define **KEY** for the unique identification number of the queue.
- Define **MAXLEN** for the maximum message length.
- Define **msg_1_t** for the client message.
- Define **msg_2_t** for the response from the server.

### message-types.h
```c
#ifndef MSG_TYPES
#define MSG_TYPES

#define KEY 1274
#define MAXLEN 512

struct msg_1_t
{
   long mtype;
   int snd_pid;
   char body[MAXLEN];
};

struct msg_2_t
{
   long mtype;
   int snd_pid;
   int rcv_pid;
   char body[MAXLEN];
};

#endif
```
