## Сървър за съобщения

- Създайте опашка за съобщения с даден ключ **KEY**. 
- Изчакайте съобщение от тип **msg_1_t** от опашката. 
- Отпечатайте данните за получените съобщения. 
- Подгответе и изпратете отговор от тип **msg_2_t**. 
- Изчакайте потвърждение **msg_1_t**. 
- Премахнете опашката за съобщения.

### message-server.c
```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include "message-types.h"

int main(int argc, char ** argv)
{
   int msgid = msgget(KEY, 0777 | IPC_CREAT);
   if(msgid == -1)
   {
     printf("Error msgget.\n");
     return EXIT_FAILURE;
   }

   struct msg_1_t message1;
   msgrcv(msgid, &message1, sizeof(struct msg_1_t), 1, 0);
   printf("Client [pid = %i] send: %s\n", message1.snd_pid, message1.body);

   struct msg_2_t message2;
   message2.mtype = 2;
   message2.snd_pid = getpid();
   message2.rcv_pid = message1.snd_pid;
   strcpy(message2.body, "OK\n");
   msgsnd(msgid, &message2, sizeof(struct msg_2_t), 0);

   msgrcv(msgid, &message1, sizeof(struct msg_1_t), 1, 0);
   printf("Client [pid = %i] send: %s\n", message1.snd_pid, message1.body);

   msgctl(msgid, IPC_RMID, 0);
   return EXIT_SUCCESS;
}
```
