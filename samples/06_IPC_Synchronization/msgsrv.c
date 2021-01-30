#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msgtypes.h"
int main()
{
	// Messages
	struct msg_1_t message1;
	struct msg_2_t message2;
	char * response = "Ok!";

	// Receive Message Identificator
	int msgid = msgget(KEY, 0777 | IPC_CREAT);

        // Receive Message 1
	msgrcv(msgid, &message1, sizeof(struct msg_1_t), 1, 0);
	printf("Client (pid = %i) send: %s\n", message1.snd_pid, message1.body);

        // Prepare to send Message 2
	message2.mtype = 2;
	message2.snd_pid = getpid();
	message2.rcv_pid = message1.snd_pid;
	strcpy(message2.body, response);

	// Send Message 2
	msgsnd(msgid, &message2, sizeof(struct msg_2_t), 0);

        // Receive Message 1
	msgrcv(msgid, &message1, sizeof(struct msg_1_t), 1, 0);

	// Remove Message Queue
	msgctl(msgid, IPC_RMID, 0);

	return 0; // EXIT_SUCCESS
}
