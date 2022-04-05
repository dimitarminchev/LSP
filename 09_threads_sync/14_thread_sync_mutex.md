## Пример за синхронизиране посредством използване на мютекс 

- Дефинираме променливи **mutex** и **balance**
- Дефинираме на функция за нишки, където заключваме mutex
- Добавяме сумата от депозита (_Променлива: deposit_) към баланса (_Променлива: balance_)
- Отпечатваме на баланса и отключваме на мютекса
- Създаваме на първа нишка с депозит от 200, извеждаме съобщение при неуспех
- Създаваме на втора нишка с депозит от 200, извеждаме съобщение при неуспех
- Изчакваме двете нишки да приключта своята работа

### thread-sync-mutex.c
```c
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

// Global Mutex
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

// Global Variable Balance
int balance = 1000;

// Thread Handler Function to Deposit Money into the Ballance
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

// Main Functoin
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

Компилиране на програмата с изрична инструкция към компилатора да поддръжка нишки:
```
gcc thread-sync-mutex.c -o thread-sync-mutex -lpthread
```