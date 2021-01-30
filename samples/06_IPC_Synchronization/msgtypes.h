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
