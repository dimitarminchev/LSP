## Example: synchronization using a semaphore

- Declare a semaphore (`sem`)
- Declare the balance variable and initialize it to 1000
- Define the thread function that handles the argument and releases the semaphore
- Initialize the semaphore with value zero (meaning: busy)
- Start the first thread, passing the deposit amount (`deposit_amount`)
- Start the second thread, passing the deposit amount (`deposit_amount`)
- Wait for both threads to finish and destroy the semaphore

### thread-sync-semaphore.c
```c
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

// Global Semaphore
sem_t sem;

// Global Variable Balance
int balance = 1000;

// Thread Handler Function to Deposit Money into the Balance
void *deposit(void *arg)
{
  // Critical Section
  sem_post(&sem);

  int deposit_amount = *(int *)arg;
  balance += deposit_amount;
  printf("Balance: $%i\n", balance);

  sem_wait(&sem);
  // End of Critical Section
}

// Main Function
int main(int argc, char *argv[])
{
  int result;
  pthread_t thread1, thread2;
  int deposit_amount = 200;

  // Semaphore Initialization
  sem_init(&sem, 0, 0);

  // Create Thread
  result = pthread_create(&thread1, NULL, &deposit, &deposit_amount);
  if(result == -1)
  {
    printf("Error creating thread one.\n");
    return EXIT_FAILURE; // -1
  }
  result = pthread_create(&thread2, NULL, &deposit, &deposit_amount);
  if(result == -1)
  {
    printf("Error creating thread two.\n");
    return EXIT_FAILURE; // -1
  }

  // Execute and join the results
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  // Semaphore Destroy
  sem_destroy(&sem);

  return EXIT_SUCCESS; // 0
}
```

Compile the program and link with pthreads:

```
gcc thread-sync-semaphore.c -o thread-sync-semaphore -lpthread
```
