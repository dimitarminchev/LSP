#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msgtypes.h"
int main()
{
	// Messages
	struct msg_1_t message1;
	struct msg_2_t message2;
	char buf[MAXLEN];

	// Message Identificator
	int msgid = msgget(KEY, 0666);
	if(msgid == -1)
	{
	   printf("Server is not running!\n");
       	   return -1; // EXIT_FAILURE
	}

        // Read for standart input the message1.body
        printf("Please write the message and press [Enter] to send:\n");
	int i = 0;
	while((i < (MAXLEN - 1)) &&
	      (message1.body[i++] = getchar() != '\n'));

	// Prepare Message 1
	// message1.body[i] = '\0';
        message1.mtype = 1;
        message1.snd_pid = getpid();

	// Send Message 1
	msgsnd(msgid, &message1, sizeof(struct msg_1_t), 0);

        // Receive Message 2
	msgrcv(msgid, &message2, sizeof(struct msg_2_t), 2, 0);
	printf("Server (pid = %i) responded: %s\n", message2.snd_pid, message2.body);

        // Prepare and Send Message 1
	message1.mtype = 1;
	msgsnd(msgid, &message1, sizeof(struct msg_1_t), 0);

	return 0; // EXIT_SUCCESS
}
