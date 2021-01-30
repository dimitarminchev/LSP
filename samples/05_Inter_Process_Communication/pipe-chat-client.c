#include <stdio.h>
#include <unistd.h>

// fifo named pipe
#define FIFO_NAME "./chat-fifo"

// Main program
int main()
{
   char ch;
   FILE * f = fopen(FIFO_NAME, "r"); // r = read

   // Read characters from the named pipe / fifo file
   do
   {
      ch = fgetc(f);
      putchar(ch);
   }
   while (ch != 'q'); // q = quit

   fclose(f); // close file
   unlink(FIFO_NAME); // delete file
   
   return 0; // EXIT_SUCCESS
}
