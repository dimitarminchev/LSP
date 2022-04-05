## Пример за синхронизиране посредством използване на семафор 

- Декларираме семафор (_Променлива: sem_)
- Декларираме баланс (_Променлива: balance_) и го инициираме с 1000
- Дефинираме процедура при работа на нишката, която oбработва аргумента и освобождава семафора
- Инициираме семафора със стойност нула (_Означава: Зает_)
- Стартираме първата нишка и предаваме параметър за сума на депозита (_Променлива: deposit_amount_)
- Стартираме втората нишка и предаваме параметър за сума на депозита (_Променлива: deposit_amount_)
- Изчакваме двете нишки да приключат своята работа и унищожаваме семафора

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

// Thread Handler Function to Deposit Money into the Ballance
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

// Main Functoin
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

Компилиране на програмата с изрична инструкция към компилатора да поддръжка нишки:
```
gcc thread-sync-semaphore.c -o thread-sync-semaphore -lpthread
```