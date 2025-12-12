## Create a File with a Hole

- Initialize the variables
- Create a file using the first argument passed to the program as its name
- If it doesn't open, output an error and exit
- Write the file name to the file
- Skip 16777216 bytes forward in the file
- Write the file name to the file again
- Close the file

### makesparse.c
```c
#include <stdio.h>
#include <string.h>

#define BIG_SIZE 0x1000000

int main(int argc, char * argv[])
{
  FILE * f;
  f = fopen(argv[1], "w");
  if (f == NULL) 
  {
     printf("ERROR creating file: %s", argv[1]);
     return 1;
  }
  fwrite(argv[1], 1, strlen(argv[1]), f);
  fseek(f, BIG_SIZE, SEEK_CUR);
  fwrite(argv[1], 1, strlen(argv[1]), f);
  fclose(f);
}
```