## Пример за изход от нишкa

- Дефинираме функция за изход, която освобождава заетата памет
- Дефинираме функция на нишката: Заключване на отмяната на нишката
- Заемаме 1K памет и извеждаме съобщение
- Добавяме манипулатор за почистване при изход от нишката, предаващ заетата памет като параметър
- Отключваме отмяната на нишката
- Отпечатваме 5 съобщения за 5 секунди
- Извикваме и изпълняваме, манипулатора за почистване при изход от нишката

### thread-clean-exit.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define MEM_SIZE 1024 // 1K
// Thread Cleanup Handler Function
void thread_cleanup_handler(void *arg)
{
  free(arg);
  printf("Freed %i bytes accolated memory.\n", MEM_SIZE);
}
// Thread Handler Function
void *thread_handler(void * arg)
{
  // Critical Section
  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

  void *mem = malloc(MEM_SIZE);
  printf("Allocated %i bytes memory.\n", MEM_SIZE);

  // Attach Thread Cleanup Hanler
  pthread_cleanup_push(thread_cleanup_handler, mem);

  // End of Critical Section
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

  for(int i=0; i<5; i++)
  {
    sleep(1); // sleep for 1 second
    printf("Important process %i is running...\n", i+1);
  }

  // Execute Thread Cleanup Handler
  pthread_cleanup_pop(1);
}
// Main Function
int main(int argc, char *argv[])
{
  pthread_t thread;
  int result = pthread_create(&thread, NULL, thread_handler, NULL);
  if(result == -1)
  {
    printf("Error creating thread!\n");
    return EXIT_FAILURE; // -1
  }
  pthread_join(thread, NULL);
  return EXIT_SUCCESS; // 0
}
```

Компилиране на програмата с изрична инструкция към компилатора да поддръжка нишки:
```
gcc thread-clean-exit.c -o thread-clean-exit -lpthread
```