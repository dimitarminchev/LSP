#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// fifo named pipe
#define FIFO_NAME "./chat-fifo"

// Main program
int main()
{
   char ch;
   mkfifo(FIFO_NAME, 0600); // write + read
   FILE * f = fopen(FIFO_NAME, "w"); // w = write

   // Error check
   if (f == NULL)
   {
      printf("Failed to open FIFO!\n");
      return -1; // EXIT_FAILURE
   }

   // Write characters to the named pipe / fifo file
   do
   {
      ch = getchar();
      fputc(ch, f);
      if (ch == 10) fflush(f);
   }
   while (ch != 'q'); // q = quit

   fclose(f); // close file = save
   unlink(FIFO_NAME); // delete file

   return 0; // EXIT_SUCCESS
}
