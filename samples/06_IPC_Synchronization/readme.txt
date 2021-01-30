1. Общи данни за съобщенията
msgtypes.c
---
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

2. Сървър за съобщения
msgsrv.c
---
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msgtypes.h"
int main()
{
	struct msg_1_t message1;
	struct msg_2_t message2;
	char * response = "Ok!";
	int msgid = msgget(KEY, 0777 | IPC_CREAT);
	msgrcv(msgid, &message1, sizeof(struct msg_1_t), 1, 0);
	printf("Client (pid = %i) send: %s\n", message1.snd_pid, message1.body);
	message2.mtype = 2;
	message2.snd_pid = getpid();
	message2.rcv_pid = message1.snd_pid;
	strcpy(message2.body, response);
	msgsnd(msgid, &message2, sizeof(struct msg_2_t), 0);
	msgrcv(msgid, &message1, sizeof(struct msg_1_t), 1, 0);
	msgctl(msgid, IPC_RMID, 0);
	return 0; // EXIT_SUCCESS
}

3. Клиент за съобщения
msgcli.c
---
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msgtypes.h"
int main()
{
	struct msg_1_t message1;
	struct msg_2_t message2;
	char buf[MAXLEN];
	
	int msgid = msgget(KEY, 0666);
	if(msgid == -1)
	{
	   printf("Server is not running!\n");
       return -1; // EXIT_FAILURE  
	}
	
	int i = 0;
	while((i < (MAXLEN - 1)) &&
	      (message1.body[i++] = getchar() != '\n'));
		  
	message1.body[i] = '\0';
    message1.mtype = 1;
    message1.snd_pid = getpid();	
	msgsnd(msgid, &message1, sizeof(struct msg_1_t), 0);
	msgrcv(msgid, &message2, sizeof(struct msg_2_t), 2, 0);
	printf("Server (pid = %i) responded: %s\n", message2.snd_pid, message2.body);
	message1.mtype = 1;
	msgsnd(msgid, &message1, sizeof(struct msg_1_t), 0);
	
	return 0; // EXIT_SUCCESS
}

4. Общи данни за споделена памет 
shmemtypes.h
---
#ifndef SHMEM_TYPES
#define SHMEM_TYPES
#define FTOK_FILE "./shmemserv"
#define MAXLEN 512
#define FREE 1
#define BUSY 0
#define SERVER 1
#define CLIENT 0
struct memory_block
{
   int server_lock;
   int client_lock;
   int turn;
   int readlast;
   char string[MAXLEN];
};
#endif


5. Сървър за споделена памет
shmemserv.c
---
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shmemtypes.h"
int main(int argc, char * argv[])
{
key_t key;
int shmid;
struct memory_block * mblock;
key = ftok(FTOK_FILE, 1);
if (key == -1)
{
printf("Failed to generate unique key. Server compiler with a wrong name?\n");
return EXIT_FAILURE;
}
shmid = shmget(key, sizeof(struct memory_block), 0666 | IPC_CREAT);
mblock = (struct memory_block *) shmat(shmid, 0, 0);
mblock->turn = CLIENT;
mblock->server_lock = FREE;
mblock->client_lock = FREE;
mblock->readlast = SERVER;
strcpy(mblock->string, "Hello!");
while (strcmp("q\n", mblock->string) != 0)
{
mblock->server_lock = BUSY;
mblock->turn = CLIENT;
while ((mblock->client_lock == BUSY) && (mblock->turn == CLIENT));
if (mblock->readlast == CLIENT)
{
mblock->readlast = SERVER;
printf("String sent by the client is: %s", mblock->string);
if (strcmp("q\n", mblock->string) != 0)
strcpy(mblock->string, "Ok!");
mblock->server_lock = FREE;
}
}
printf("Server got q and exits\n");
shmdt((void *) mblock);
shmctl(shmid, IPC_RMID, 0);
return EXIT_SUCCESS;
}

6. Клиент за споделена памет
shmemcli.c
---
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shmemtypes.h"
int main(int argc, char * argv[])
{
key_t key;
int shmid;
struct memory_block * mblock;
key = ftok(FTOK_FILE, 1);
if (key == -1)
{
printf("Failed to generate unique key. Server compiler with a wrong name?\n");
return EXIT_FAILURE;
}
shmid = shmget(key, sizeof(struct memory_block), 0666);
if (shmid == -1)
{
printf("Server is not running!\n");
return EXIT_FAILURE;
}
mblock = (struct memory_block *) shmat(shmid, 0, 0);
while (strcmp("q\n", mblock->string) != 0)
{
int i = 0;
mblock->client_lock = BUSY;
mblock->turn = SERVER;
while ((mblock->server_lock == BUSY) && (mblock->turn == SERVER));
if (mblock->readlast == SERVER)
{
mblock->readlast = CLIENT;
printf("Server sends %s\n", mblock->string);
while ((i < (MAXLEN - 1)) && ((mblock->string[i++] = getchar()) != '\n') );
mblock->string[i] = 0;
mblock->client_lock = FREE;
}
}
printf("Client exits\n");
shmdt((void *) mblock);
return EXIT_SUCCESS;
}

7. Общи данни за семафорна комуникация
semtypes.h
---
#ifndef SHMEM_TYPES
#define SHMEM_TYPES
#define FTOK_FILE "./semserv"
#define MAXLEN 512
struct memory_block
{
char string[MAXLEN];
};
#endif

8. Семафорен сървър
semserv.c
---
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semtypes.h"
int main(int argc, char * argv[])
{
key_t key;
int shmid;
int pid, semid;
struct sembuf buf[2];
struct memory_block * mblock;
key = ftok(FTOK_FILE, 1);
if (key == -1)
{
printf("Failed to generate unique key. Server compiler with a wrong name?\n");
return EXIT_FAILURE;
}
semid = semget(key, 3, 0666|IPC_CREAT);
buf[0].sem_num = 0;
buf[0].sem_flg = SEM_UNDO;
buf[1].sem_num = 1;
buf[1].sem_flg = SEM_UNDO;
semctl(semid, 0, SETVAL, 0);
shmid = shmget(key, sizeof(struct memory_block), 0666 | IPC_CREAT);
mblock = (struct memory_block *) shmat(shmid, 0, 0);
strcpy(mblock->string, "Hello!");
buf[0].sem_op = -1;
buf[1].sem_op = 1;
semop(semid, (struct sembuf*) &buf[1], 1);
while (strcmp("q\n", mblock->string) != 0)
{
semop(semid, (struct sembuf*) &buf, 1);
printf("String sent by the client is: %s", mblock->string);
if (strcmp("q\n", mblock->string) != 0)
strcpy(mblock->string, "Ok!");
buf[0].sem_op = -1;
buf[1].sem_op = 1;
semop(semid, (struct sembuf*) &buf[1], 1);
}
printf("Server got q and exits\n");
shmdt((void *) mblock);
shmctl(shmid, IPC_RMID, 0);
semctl(semid, 2, IPC_RMID);
return EXIT_SUCCESS;
}

9. Семафорен клиент
semcli.c
---
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semtypes.h"
int main(int argc, char * argv[])
{
key_t key;
int shmid;
struct memory_block * mblock;
int semid;
struct sembuf buf[2];
key = ftok(FTOK_FILE, 1);
if (key == -1)
{
printf("Failed to generate unique key. Server compiler with a wrong name?\n");
return EXIT_FAILURE;
}
shmid = shmget(key, sizeof(struct memory_block), 0666);
if (shmid == -1)
{
printf("Server is not running!\n");
return EXIT_FAILURE;
}
semid = semget(key, 2, 0666);
buf[0].sem_num = 0;
buf[0].sem_flg = SEM_UNDO;
buf[1].sem_num = 1;
buf[1].sem_flg = SEM_UNDO;
mblock = (struct memory_block *) shmat(shmid, 0, 0);
buf[1].sem_op = -1;
while (strcmp("q\n", mblock->string) != 0)
{
int i = 0;
semop(semid, (struct sembuf*) &buf[1], 1);
printf("Server sends %s\n", mblock->string);
while ((i < (MAXLEN - 1)) && ((mblock->string[i++] = getchar()) != '\n') );
mblock->string[i] = 0;
buf[0].sem_op = 1;
buf[1].sem_op = -1;
semop(semid, (struct sembuf*) &buf, 1);
}
printf("Client exits\n");
shmdt((void *) mblock);
return EXIT_SUCCESS;
}