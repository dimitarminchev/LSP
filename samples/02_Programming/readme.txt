1. Компилиране
===
nano first.c
---
#include<stdio.h>
int main()
{
	int a=0;
	int b=a+5;
	printf("%i\n",b);
	return 0;
}

Компилирайте в асемблер 
---
gcc -S first.c -o first.s
nano first.s

Компилирайте до обектен файл 
---
gcc -c first.c -o first.o
nano first.o

Компилирайте до изпълнима програма
---
gcc first.c -o first
nano first
./first



2. Библиотеки (стр.37)
===
mkdir libexample
mkdir libexample/src
-> main.c
mkdir libexample/src/addlib
-> add.c, add.h, answer.c, answer.h
mkdir libexample/bin
mkdir libexample/bin/static
mkdir libexample/bin/shared

cd libexample/src/addlib/
nano add.c
---
#include <stdio.h>
int gSummand;
void setSummand(int summand) {
	gSummand = summand;
}
int add(int summand) {
	return gSummand + summand;
}
void __attribute__ ((constructor)) initLibrary(void) {
	printf("Library is initialized\n"); 
	gSummand = 0;
}
void __attribute__ ((destructor)) cleanUpLibrary(void) {
	printf("Library is exited\n"); 
}

nano add.h
---
void setSummand(int summand);
int add(int summand);

nano answer.c
---
#include "add.h"
int answer() {
	setSummand(20);
	return add(22); // 42 = 20 + 22
}

nano answer.h
---
int answer();

cd ..
nano main.c
---
#include <stdio.h>
#include "addlib/add.h"
#include "addlib/answer.h"
int main(int argc, char* argv[])
{
	setSummand(5);
	printf("5 + 7 = %d\n", add(7));
	printf("And the answer is: %d\n", answer());
	return 0;
}

cd ..

Създаване на обектни файлове 
---
gcc -c src/main.c -o bin/main.o
gcc -c src/addlib/add.c -o bin/static/add.o
gcc -c src/addlib/answer.c -o bin/static/answer.o
gcc -c -fPIC src/addlib/add.c -o bin/shared/add.o
gcc -c -fPIC src/addlib/answer.c -o bin/shared/answer.o

Създаване на статична и динамична библиотеки 
---
ar rcs bin/static/libadd.a bin/static/add.o bin/static/answer.o
gcc bin/main.o -Lbin/static -ladd -o bin/statically-linked
./bin/statically-linked

gcc -shared bin/shared/add.o bin/shared/answer.o -o bin/shared/libadd.so
gcc bin/main.o -Lbin/shared -ladd -o bin/use-shared-library
LD_LIBRARY_PATH=$(pwd)/bin/shared bin/use-shared-library

Използване на динамична библиотека
---
nano test.c
---
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
int main()
{
		// Load the dinamic library:
        void* lib_add = dlopen("bin/shared/libadd.so",  RTLD_LAZY | RTLD_GLOBAL);

        // Declare the function pointers:
        void (*fptr_setSummand)(int);
        int  (*fptr_add)(int);

        // Get the pointers to the functions within the library:
        fptr_setSummand = dlsym(lib_add, "setSummand");
        fptr_add = dlsym(lib_add, "add");

        // Call the function via the function pointer:
        fptr_setSummand(42);
        int result = fptr_add(7);
        printf("Result: %d\n", result);

        return 0;
}


gcc test.c -ldl -o test
./test



3. Дебъгване 
===
sum.c
---
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[])
{
	int numbers_count = atoi(argv[1]);
	int numbers_sum = 0;
	char next_number[50];
	for(int i = 0; i < numbers_count; i++)
	{
		printf("Enter %d number: ", i+1);
		scanf("%s", next_number);
		numbers_sum += atoi(next_number);
	}
	printf("Total numbers sum is %d\n", numbers_sum);
	return 0;
}

gcc -g sum.c -o sum
gdb sum
b main
r 3
n
q
