## Library Example

In the `libexample/` folder, create a file `test.c` with the following content:
```c
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
```

Compile and run the test program using the commands:
```
gcc test.c -ldl -o test
./test
```

As a result, if executed successfully, you should see the following three lines:
```
Library is initialized
Result: 49
Library is exited
```
