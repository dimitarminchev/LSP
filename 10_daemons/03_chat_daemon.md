## Чат демон

- Проверка на аргументите, изход при грешка
- Демонизиране на програмата, изход при грешка
- Подготвяне на сокета за слушане
- Изпълнение, докато не бъде получен сигнал **graceful exit**
- Приемане и обработка на нова връзка
- Нулиране на флаговете **graceful exit** и **HUp**
- Почистване на ресурсите и изход

### chat-daemon.c (main)

```c
int main(int argc, char *argv[])
{
  int result;
  pit_t daemonPID;
  
  if(argc > 1) {
  // Process the arguments ...
  
  if((result = BecomeDaemonProcess()) < 0) {
  // Daemonize Error ...
  
  if((result = ConfigureSignalHandlers()) < 0) {
  // Signal Handlers Error ...
  
  if((result = BindPassiveSocket(gListenPort, &gMasterSocket)) < 0) {
  // Socket Binding Error ...
  
  // Do Work ...
  do
  {
    if(AcceptConnections(gMasterSocket) < 0) {
	// Connection Accept Error ...
	
	if((gGracefulShutdown == 1) && (gCaughtHupSignal == 0)) break;
	gGracefulShutdown = gCaughtHupSignal = 0;
	
  } while(1);
  
  // Clenup & Exit ...
  TidyUp();
  
  return EXIT_SUCCESS; // 0
}
```