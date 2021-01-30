#include <stdio.h>
#include <string.h>
#define BIG_SIZE 0x1000000 // 16777216 bytes = 16 MB
int main(int argc, char * argv[])
{
   // arguments check
   if(argc != 2)
   {
     printf("Syntax: makesparse [filename]\n");
     return -1;
   }

   // open file
   FILE * f = fopen(argv[1], "w");

   // error open file
   if (f == NULL)
   {
      printf("Error creating file: %s", argv[1]);
      return -2;
   }

   // write
   fwrite(argv[1], 1, strlen(argv[1]), f);
   fseek(f, BIG_SIZE, SEEK_CUR);
   fwrite(argv[1], 1, strlen(argv[1]), f);

   // close file
   fclose(f);

   return 0;
}
