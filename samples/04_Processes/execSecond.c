#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char * argv[])
{
   char *args[] = {"./execFirst",NULL};
   execvp(args[0], args);
   return 0;
}
