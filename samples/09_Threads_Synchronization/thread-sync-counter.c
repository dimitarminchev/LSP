#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

// Gobal Variables
#define NUM_LOOPS 7000000
long long SUM = 0;

// Global Mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Thread Handler Function for Counting Numbers
void * counting(void *arg)
{
  int offset = *(int *)arg;
  for(int i = 0; i < NUM_LOOPS; i++)
  {
    // Critical Section
    pthread_mutex_lock(&mutex);
    SUM += offset;
    pthread_mutex_unlock(&mutex);
    // End of Critical Section
  }
  pthread_exit(NULL);
}

// Main Function
int main(int argc, char *argv[])
{
  // Create Threads
  pthread_t thread1, thread2;
  int result, plusone = 1, minusone = -1;

  result = pthread_create( &thread1, NULL, counting, &plusone);
  if(result == -1)
  {
    printf("Error creating thread one.\n");
    return EXIT_FAILURE; // -1
  }
  result = pthread_create( &thread2, NULL, counting, &minusone);
  if(result == -1)
  {
    printf("Error creating thread two.\n");
    return EXIT_FAILURE; // -1
  }

  // Execute Treads
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  printf("Total Sum = %lld\n", SUM);
  pthread_mutex_destroy(&mutex);

  return EXIT_SUCCESS; // 0
}
