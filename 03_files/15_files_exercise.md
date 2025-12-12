## File Handling Exercise
Practice the materials from this topic by implementing the projects presented below.

### File Manipulator
Write a program **file-manipulator.c** that requires 3 arguments: **words_count**, **min_length**, **max_length**. The program should generate a file called **file-manipulator.log** that contains **words_count** number of words (_separated by spaces_). To generate the words, create a function **random_word_generator** (_the function will not generate real words, but rather random sequences of characters_):

```c
char* random_word_generator(int min_length, int max_length);
```

Then the program should print the generated file to the screen.

After the program creates the file **file-manipulator.log** and before writing to it, it should lock the first 100 bytes of the file. When the program prints the generated words, it should wait for the **Enter** key to be pressed, then unlock the file. Accordingly, if the file is already locked by another process, the program should notify about this and wait for the **Enter** key to be pressed before trying again (_to lock, generate, and write_).

Compile and run several times for testing.
