#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <syslog.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

// Global Variables
volatile sig_atomic_t gGracefulShutdown = 0;
int gMasterSocket = -1;
int gCaughtHupSignal = 0;
int gListenPort = 10000;
int gLockFileDesk = -1;
const char *const gLockFilePath = "chat-daemon.pid";

// Daemonize
int BecomeDaemonProcess(char *cApplicationName)
{
  // pid
  int pid = fork();
  switch(pid)
  {
    case -1: // error
    {
      printf("Error fork the process.\n");
      exit(EXIT_FAILURE);
    }
    case  0: // child process
      break;
    default: // parent process
      exit(EXIT_SUCCESS);
  }
  char pidString[10];
  sprintf(pidString,"%d",(int)getpid());

  // Log
  openlog(cApplicationName, LOG_NOWAIT, LOG_LOCAL0);

  if((gLockFileDesk = creat(gLockFilePath, 0644) < 0))
  {
    printf("Error creating the lock file.\n");
    exit(EXIT_FAILURE);
  }

  int LockResult;
  struct flock Lock;
  Lock.l_type = F_WRLCK;
  Lock.l_whence = SEEK_SET;
  Lock.l_len = Lock.l_start = 0;
  Lock.l_pid = 0;

  if((LockResult = fcntl(gLockFileDesk, F_SETLK, &Lock)) < 0)
  {
    printf("Error locking the lock file.\n");
    exit(EXIT_FAILURE);
  }

  if(write(gLockFileDesk, pidString, strlen(pidString)) <= 0)
  {
    printf("Error writing to lock file.\n");
    exit(EXIT_FAILURE);
  }

  if(setsid() < 0)
  {
    printf("Error changing the session ID.\n");
    exit(EXIT_FAILURE);
  }

  if(chdir("/") < 0)
  {
    printf("Error changing the process folder.\n");
    exit(EXIT_FAILURE);
  }

  long numFiles = sysconf(_SC_OPEN_MAX);
  for(int i = numFiles-1; i >=0 ; --i)
  {
    if(i != gLockFileDesk) close(i);
  }
  int stdioFD = open("/dev/null", O_RDWR);
  dup(stdioFD); // stdout
  dup(stdioFD); // stferr

  return EXIT_SUCCESS; // 0
}

// Cleanup
void TidyUp(void)
{
  if(gLockFileDesk != -1)
  {
    close(gLockFileDesk);
    unlink(gLockFilePath);
    gLockFileDesk = -1;
  }
  if(gMasterSocket != -1)
  {
    close(gMasterSocket);
    gMasterSocket = -1;
  }
}

// Singlas handling
void Handler(int Signal)
{
  switch(Signal)
  {
    case SIGUSR1: gGracefulShutdown = 1; break;
    case SIGHUP: gGracefulShutdown = gCaughtHupSignal = 1; break;
    case SIGTERM:
    {
       TidyUp();
       exit(EXIT_SUCCESS);
       break;
    }
    // (total 16)
    default:
      // ?
      TidyUp();
      exit(EXIT_SUCCESS);
  }
  // ?
}
int ConfigureSignalHandlers(void)
{
  int BlockSignals[] = {SIGUSR2, SIGALRM, SIGPIPE }; // 7
  int HandleSignals[] = {SIGUSR1, SIGHUP, SIGTERM }; // 16

  // Signal Mask
  sigset_t signalMask;
  sigemptyset(&signalMask);
  for(int i = 0; i < 7; i++)
  {
    sigaddset(&signalMask, *(BlockSignals + i));
  }

  // Signal Action
  struct sigaction signalAction;
  sigemptyset(&signalAction.sa_mask);
  signalAction.sa_flags = 0;
  signalAction.sa_handler = Handler;
  for(int i = 0; i < 16; i++)
  {
    sigaction(*(HandleSignals + i), &signalAction, NULL);
  }

  return EXIT_SUCCESS; // 0
}

// Set listening Socket
int BindPassiveSocket(const int portNum, int *const boundSocket)
{
  struct sockaddr_in sin;
  memset(&sin.sin_zero, 0, 8);
  sin.sin_port = htons(portNum);
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = htonl(INADDR_ANY);

  int newsock = socket(PF_INET, SOCK_STREAM, 0);
  if(newsock < 0)
  {
    printf("Error creating socket!\n");
    return EXIT_FAILURE; // -1
  }

  int optval = 1;
  size_t optlen = sizeof(int);
  setsockopt(newsock, SOL_SOCKET, SO_REUSEADDR, &optval, optlen);

  if(bind(newsock, (struct sockaddr*)&sin, sizeof(struct sockaddr_in)) < 0)
  {
    printf("Error binding socket!\n");
    return EXIT_FAILURE; // -1
  }

  if(listen(newsock, SOMAXCONN) < 0)
  {
    printf("Error listening on socket!\n");
    return EXIT_FAILURE; // -1
  }
  *boundSocket = newsock;

  return EXIT_SUCCESS; // 0
}

// ReadLine Helper Function
int ReadLine(const int sock,char *const buffer,const size_t buflen, size_t *const bytesRead)
{
 int done=0,retval=0;
 char c,lastC=0;
 size_t bytesSoFar=0;
 ssize_t readResult;

 do
 {
  readResult = recv(sock,&c,1,0);
  switch(readResult)
  {
   case -1:
     if(errno!=EINTR)
     {
      retval=-1;
      done=1;
     }
     break;

   case 0:
     retval=0;
     done=1;
     break;

   case 1:
     buffer[bytesSoFar]=c;
     bytesSoFar+=readResult;
     if(bytesSoFar>=buflen)
     {
       done=1;
       retval=-1;
       if((c=='\n')&&(lastC=='\r')) done=1;
       lastC=c;
       // break;
     }
     break;
   }
  }
  while(!done);
  buffer[bytesSoFar] = 0;
  *bytesRead = bytesSoFar;
  return retval;
}

// Write to Socket Helper Function
int WriteToSocket(const int sock,const char *const buffer, const size_t buflen)
{
  size_t bytesWritten=0;
  ssize_t writeResult;
  int retval=0,done=0;
  do
  {
    writeResult = send(sock,buffer+bytesWritten,buflen-bytesWritten,0);
    if(writeResult==-1)
    {
      if(errno==EINTR) writeResult=0;
      else
      {
	retval=1;
	done=1;
      }
    }
    else
    {
	bytesWritten+=writeResult;
	if(writeResult==0) done=1;
    }
   }
   while(done==0);
   return retval;
}

// Connection Handling
int HandleConnection(const int slave)
{
  char *buffer;
  size_t len;
  size_t bytes;

  int retval = ReadLine(slave, buffer, len, &bytes);
  if(retval == 0)
  {
    WriteToSocket(slave, buffer, bytes);
  }
  return retval;
}
int AcceptConnections(const int master)
{
  int proceed = 1, slave, retval = 0;
  struct sockaddr_in client;
  socklen_t clilen;
  while((proceed == 1) && (gGracefulShutdown == 0))
  {
    clilen = sizeof(client);
    slave = accept(master, (struct sockaddr *)&client, &clilen);
    if(slave < 0)
    {
      if(errno == EINTR) continue;
      proceed = 0;
      retval = -1;
    }
    else
    {
      retval = HandleConnection(slave);
      if(retval) proceed = 0;
    }
    close(slave);
  }
  return retval;
}

// Main Program
int main(int argc, char *argv[])
{
  int result;
  pid_t daemonPID;

  if(argc > 1)
  {
    int fd = open(gLockFilePath, O_RDONLY);
    if(fd < 0)
    {
      printf("Error opening lock file!\n");
      exit(EXIT_FAILURE);
    }

    char pid_buf[16];
    int len = read(fd, pid_buf, 16);
    pid_buf[len] = 0;
    pid_t pid = atoi(pid_buf);

    if(!strcmp(argv[1], "stop"))
    {
      kill(pid, SIGUSR1);
      exit(EXIT_SUCCESS);
    }
    if(!strcmp(argv[1], "restart"))
    {
      kill(pid, SIGHUP);
      exit(EXIT_SUCCESS);
    }
    printf("Usage: %s [stop|restart]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if((result = BecomeDaemonProcess(argv[0])) < 0)
  {
    printf("Daemonize Error.\n");
    exit(EXIT_FAILURE);
  }

  if((result = ConfigureSignalHandlers()) < 0) 
  {
    printf("Signal Handlers Error.\n");
    exit(EXIT_FAILURE);
  }

  if((result = BindPassiveSocket(gListenPort, &gMasterSocket)) < 0) 
  {
    printf("Socket Binding Error.\n");
    exit(EXIT_FAILURE);
  }

  // Do Work ...
  do
  {
    if(AcceptConnections(gMasterSocket) < 0) 
    {
      printf("Connection Accept Error.\n");
      exit(EXIT_FAILURE);
    }

    if((gGracefulShutdown == 1) && (gCaughtHupSignal == 0)) break;
    gGracefulShutdown = gCaughtHupSignal = 0;

  } while(1);

  // Clenup & Exit ...
  TidyUp();

  return EXIT_SUCCESS; // 0
}
