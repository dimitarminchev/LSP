## Клиент за съобщения

- Отварете опашка за съобщения с даден ключ **KEY**. 
- Изведете съобщение и излезте от програмата, в случай на неуспех. 
- Прочетете тялото на съобщението от клавиатурата и задайте другите параметри на **msg_1_t**. 
- Изпратете съобщение **msg_1_t** в опашката. 
- Изчакайте **msg_2_t** и го отпечатайте. 
- Изпратете потвърждение **msg_1_t**.

### message-client.c
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "message-types.h"

int main(int argc, char ** argv)
{
  int msgid = msgget(KEY, 0666);
  if(msgid == -1)
  {
    printf("Error msgget.\n");
    return EXIT_FAILURE;
  }

  int i = 0;
  struct msg_1_t message1;
  while( (i < (MAXLEN - 1)) &&
         ((message1.body[i++] = getchar()) != '\n') );
  message1.body[i] = '\0';
  message1.mtype = 1;
  message1.snd_pid = getpid();
  msgsnd(msgid, &message1, sizeof(struct msg_1_t), 0);
  printf("Sended: %s\n", message1.body);

  struct msg_2_t message2;
  msgrcv(msgid, &message2, sizeof(struct msg_2_t), 2, 0);
  printf("Server [pid = %i] responded: %s\n", message2.snd_pid, message2.body);

  message1.mtype = 1;
  msgsnd(msgid, &message1, sizeof(struct msg_1_t), 0);

  return EXIT_SUCCESS;
}
```
