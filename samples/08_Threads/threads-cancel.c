#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

// Global variable
int i;

// Thread function
void * thread_func(void * arg)
{
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
  for(i=0; i<4; i++)
  {
     sleep(1);
     printf("I am running verry important process %i ...\n", i+1);
  }
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  pthread_testcancel();
  printf("YOU WILL NOT STOP ME!!!\n");
}

// Main function
int main(int argc, char * argv[])
{
  pthread_t thread;

  // Thread create
  pthread_create(&thread, NULL, thread_func, NULL);

  // бичим айляк 1 секунда
  while(i < 1) sleep(1);

  // Thread cancel
  pthread_cancel(thread);
  printf("Requsted to cancel the thread!\n");

  // Thread Join
  pthread_join(thread, NULL);
  printf("The thread is stopped!\n");


  return EXIT_SUCCESS; // 0
}
