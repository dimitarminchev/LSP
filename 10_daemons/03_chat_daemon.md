## Чат демон

- Check the arguments, exit on error
- Daemonize the program, exit on error
- Prepare the listening socket
- Do until **graceful exit** is signalled 
- Accept and process a new connection
- Reset the **graceful exit** and **HUp** flags
- Clean up the resources and exit

### chat-daemon.c (main)

```
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