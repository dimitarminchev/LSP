## Чат демон
Настоящата програма има за цел да демонстрира чат клиент-вървър приложение, което използва сокети и работи на фонов режим. 

### chat-daemon.c

```c
// Headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <syslog.h>
#include <signal.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Common Constants
#define MAX_CLIENTS 100
#define BUFFER_SZ 2048
#define NAME_LEN 32

// Common Variables
static int client_count = 0;
static int uid = 10;
int option = 1;
int listenfd = 0, connfd = 0;
struct sockaddr_in serv;
struct sockaddr_in client;
pthread_t tid;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

// Structure of Client
typedef struct {
  struct sockaddr_in address;
  int sockfd;
  int uid;
  char name[NAME_LEN];
}
Client_t;

// Array of Clients
Client_t * clients[MAX_CLIENTS];

// Add Client
void add_client(Client_t * cl) {
  pthread_mutex_lock( & clients_mutex);
  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (clients[i] == NULL) {
      clients[i] = cl;
      break;
    }
  }
  pthread_mutex_unlock( & clients_mutex);
}

// Remove Client
void remove_client(int uid) {
  pthread_mutex_lock( & clients_mutex);
  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (clients[i] != NULL && clients[i] -> uid == uid) {
      clients[i] = NULL;
      break;
    }
  }
  pthread_mutex_unlock( & clients_mutex);
}

// Send Message
void send_message(char * msg, int uid) {
  pthread_mutex_lock( & clients_mutex);
  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (clients[i] != NULL && clients[i] -> uid != uid) {
      int wrt_status = write(clients[i] -> sockfd, msg, strlen(msg));
      if (wrt_status < 0) break;
    }
  }
  pthread_mutex_unlock( & clients_mutex);
}

// Handle Client
void * handle_client(void * arg) {
  char buffer[BUFFER_SZ];
  char name[NAME_LEN];
  int leave_flag = 0;
  client_count++;

  Client_t * cli = (Client_t * ) arg;

  // Joined
  sprintf(name, "%s:%i", inet_ntoa(cli -> address.sin_addr), ntohs(cli -> address.sin_port));
  strcpy(cli -> name, name);
  sprintf(buffer, "%s joined!\n", cli -> name); // Write to buffer
  send_message(buffer, cli -> uid); // Print to all other clients
  bzero(buffer, BUFFER_SZ); // Clear buffer

  while (1) {
    if (leave_flag) break;

    int receive = recv(cli -> sockfd, buffer, BUFFER_SZ, 0);
    if (receive > 0) {
      // Message
      char buff[BUFFER_SZ];

      // Attempts to overcome limitations: https://developers.redhat.com/blog/2019/08/12/efficient-string-copying-and-concatenation-in-c#update_after_wg14_april_2019_meeting
      strncpy(buff, cli -> name, BUFFER_SZ - 1);
      buff[BUFFER_SZ - 1] = '\0';
      size_t n = strlen(buff);
      strncat(buff, "> ", BUFFER_SZ - n - 1);
      n = strlen(buff);
      strncat(buff, buffer, BUFFER_SZ - n - 1);

      // Print & Send
      send_message(buff, cli -> uid);
    } else if (receive == 0 || strcmp(buffer, "exit") == 0) {
      // Left
      sprintf(buffer, "%s left!\n", cli -> name);
      send_message(buffer, cli -> uid);
      leave_flag = 1;
    } else {
      leave_flag = 1;
    }
    bzero(buffer, BUFFER_SZ);
  }
  close(cli -> sockfd);
  remove_client(cli -> uid);
  free(cli);
  client_count--;
  pthread_detach(pthread_self());

  return NULL;
}

// Daemonize
static void daemonize() {
  // Fork off the parent process 
  pid_t pid = fork();

  // An error occurred 
  if (pid < 0) exit(EXIT_FAILURE);

  // Success: Let the parent terminate 
  if (pid > 0) exit(EXIT_SUCCESS);

  // On success: The child process becomes session leader 
  if (setsid() < 0) exit(EXIT_FAILURE);

  // Catch, ignore and handle signals 
  signal(SIGCHLD, SIG_IGN);
  signal(SIGHUP, SIG_IGN);

  // Fork off for the second time
  pid = fork();

  // An error occurred 
  if (pid < 0) exit(EXIT_FAILURE);

  // Success: Let the parent terminate 
  if (pid > 0) exit(EXIT_SUCCESS);

  // Set new file permissions 
  umask(0);
  int stdiofd = open("/dev/null", O_RDWR);
  dup(stdiofd);
  dup(stdiofd);

  // Open the log file 
  openlog("chat-daemon", LOG_PID, LOG_DAEMON);
}

// Main Method
int main(int argc, char * argv[]) {
  // Arguments check
  if (argc != 2) {
    printf("Syntax: ./chat-daemon [port]\n");
    return EXIT_FAILURE;
  }

  // Socket settings
  listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  serv.sin_family = AF_INET;
  serv.sin_addr.s_addr = INADDR_ANY;
  serv.sin_port = htons(atoi(argv[1]));

  // Bind
  if (bind(listenfd, (struct sockaddr * ) & serv, sizeof(serv)) < 0) {
    printf("ERROR: bind()");
    return EXIT_FAILURE;
  }

  // Listen
  if (listen(listenfd, 10) < 0) {
    printf("ERROR: listen()");
    return EXIT_FAILURE;
  }

  // Daemonize
  daemonize();

  // Working
  while (1) {
    socklen_t client_len = sizeof(client);
    connfd = accept(listenfd, (struct sockaddr * ) & client, & client_len);

    // Check for max clients
    if (client_count + 1 == MAX_CLIENTS) {
      syslog(LOG_NOTICE, "Max clients connected! Connection rejected!\n");
      close(connfd);
      continue;
    }

    // Client settings
    Client_t * cli = (Client_t * ) malloc(sizeof(Client_t));
    cli -> address = client;
    cli -> sockfd = connfd;
    cli -> uid = uid++;

    // Add client to queue
    add_client(cli);
    pthread_create( & tid, NULL, & handle_client, (void * ) cli);

    // Reduce CPU usage
    sleep(1);
  }

  closelog();
  return EXIT_SUCCESS;
}
```

### Стартиране на чат демона

Server:
```
gcc chat-daemon.c -o chat-daemon -lpthread
./chat-daemon 5005
```

Clients:
```
nc 46.10.253.12 5005
```