## Process Exercise
Practice the materials from this topic by implementing the project presented below.

### Temp File Generator

Write a program **temp-file-generator.c** that requires 1 argument: **files_count**. The program should generate **files_count** number of files named "**temp-file-NN.tmp**" (_where the number NN is a number from 1 to files_count_). Each file is created by a separate process and contains the identifier of the corresponding process as text 1000 times (_pid = 1001 should take 4 bytes per ID_). The parent process should be notified after each file is created.

### Temp File Generator Plus

Write a new program **temp-file-generator-plus.c** by improving the previous program so that the processes write only to one file, where the sequences of process identifiers do not overlap (_we have 1000 times pid_file_1, then 1000 times pid_file_2 ... then 1000 times pid_files_count_).
