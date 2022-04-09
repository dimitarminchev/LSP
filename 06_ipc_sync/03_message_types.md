## Определяне на общи данни

- Определете **KEY** за уникалният идентификационен номер на опашката.
- Определете **MAXLEN** за максимална дължина на съобщението.
- Определете **msg_1_t** за клиентското съобщение.
- Определете **msg_1_2** за отговора от страна на сървъра.

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
