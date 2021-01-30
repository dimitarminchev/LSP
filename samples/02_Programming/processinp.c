#include<stdio.h>
#include<stdlib.h>
int main(int argc, char ** argv)
{
	int numbers_count = 0;
	int sum = 0;
	char temp_str[50];

	// Argument count check
        if(argc <= 1)
        {
		printf("Arguments count must be one or more.\n");
		return -1;
        }

	// Print Argument Information
	printf("The value of argc=%d\n", argc);
	printf("The value(s) in argv:\n");
	for(int i=0; i < argc; i++)
	{
		printf(" > argv[%d] = %s\n", i, argv[i]);
	}

	// Enter some numbers and sum it
	numbers_count = atoi(argv[1]);
	printf("Enter %d some numbers:\n", numbers_count);
	for(int i = 0; i < numbers_count; i++)
	{
		scanf("%s", temp_str);
		sum += atoi(temp_str);
	}
	printf("Total sum is %d\n", sum);

	return 0;
}
