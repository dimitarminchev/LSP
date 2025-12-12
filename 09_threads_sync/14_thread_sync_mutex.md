## Example: synchronization using a mutex

- Define the `mutex` and `balance` variables
- Define the thread function that locks the mutex
- Add the deposit amount (`deposit`) to the balance (`balance`)
- Print the balance and unlock the mutex
- Create the first thread with a deposit of 200 and report an error on failure
- Create the second thread with a deposit of 200 and report an error on failure
- Wait for both threads to finish

### thread-sync-mutex.c
```c
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

// Global Mutex
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

// Global Variable Balance
int balance = 1000;

// Thread Handler Function to Deposit Money into the Balance
void *deposit(void *arg)
{
  // Critical Section
  pthread_mutex_lock(&mutex1);

  int deposit_amount = *(int *)arg;
  balance += deposit_amount;
  printf("Balance: $%i\n", balance);

  pthread_mutex_unlock(&mutex1);
  // End of Critical Section
}

// Main Function
int main(int argc, char *argv[])
{
  int result;
  pthread_t thread1, thread2;
  int deposit_amount = 200;

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

  return EXIT_SUCCESS; // 0
}
```

Compile the program and link with pthreads:

```
gcc thread-sync-mutex.c -o thread-sync-mutex -lpthread
```
