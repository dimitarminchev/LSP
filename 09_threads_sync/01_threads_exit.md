## Изход от нишка

Нишка може да организира кои функции да бъдат извиквани при изход от нишката. Тези функции са известни още като **манипулатори за почистване на нишки** (_Термин на Английски език: Thread Cleanup Handlers_). Повече от един манипулатор за почистване може да бъде установен за всяка нишка. Манипулаторите се записват в **стек**  (_Термин на Английски език: Stack_), което означава, че се изпълняват в обратен ред спрямо добавянето им.

Когато дадена нишка бъде анулирана или прекратена чрез извикване на **pthread_exit()**, всички подредени манипулатори за почистване се извеждат и изпълняват в обратен ред на реда, в който са били поставени в стека.