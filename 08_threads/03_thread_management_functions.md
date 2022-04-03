## Функции за управление на нишки

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
```
стартира нова нишка в извикващия процес

```c
int pthread_join(pthread_t thread, void **retval);
```
изчаква приключване на определена нишка

```c
void pthread_exit(void *retval);
```
прекратява извикващата нишка и връща стойност чрез retval, която (ако нишката може да се присъедини) е достъпна за друга нишка в същия процес, който извиква **pthread_join**(3).
