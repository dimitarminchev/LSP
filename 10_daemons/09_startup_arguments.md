## Аргументи за стартиране

- Ако са подадени аргументи, то първият трябва да бъде команда '**stop**' или '**restart**'
- Отваряне на **lock file**, изход при грешка
- Прочитане и конвертирайте на **pid** от файла **lock file**
- Ако командата е **stop**, изпращане на **SIGUSR1** към процеса **pid** и успешен изход
- Ако командата е '**restart**', изпращане на **SIGHUP** към процеса **pid** и успешен изход
- Ако командата не е правилна, отпечатване на правилната употреба и изход с грешка

### chat-daemon.c (main arguments)

```c
int main(int argc, char *argv[])
{
  ...
  if(argc > 1) 
  {
	int fd = fd = open(gLockFilePath, O_RDNONLY);
	if(fd < 0)
	{
	  printf("Error opening lock file!\n");
	  return EXIT_FAILURE; // -1
	}
	
	char pid_buf[16];
	int len = read(fd, pid_buf, 16);
	pid_buf[len] = 0;
	pid_t pid = atoi(pid_buf);
	
	if(!strcmp(argv[1], "stop"))
	{
	  kill(pid, SIGUSR1);
	  exit(EXIT_SUCCESS);
	}
	if(!strcmp(argv[1], "restart"))
	{
	  kill(pid, SIGHUP);
	  exit(EXIT_SUCCESS);
	}
	printf("Usage: %s [stop|restart]\n", argv[0]);
	exit(EXIT_FAILURE);
  }
  ...
}
```