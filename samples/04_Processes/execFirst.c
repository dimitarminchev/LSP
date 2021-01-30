#include<stdio.h>
#include<unistd.h>
int main(int argc, char * argv[])
{
   printf("Executе program: %s\n", argv[0]);
   printf("Process Identification Number (pid): %i\n", getpid());
   printf("Parent pid = %i\n", getppid());
   return 0;
}
