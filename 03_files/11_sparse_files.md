## Seeking in Files and Sparse Files

```c
#include<stdio.h>
FILE *fopen(const char *pathname, const char *mode);
size_t fread(void *ptr, size_t size, size_t nmemb, FOLE *stream);
int fseek(FILE *stream. long offset, int whence);
int fclose(FILE *stream);
```

- The behavior of **fseek()** depends on the argument: **SEEK_CUR**, **SEEK_END**, or **SEEK_SET**.
- The method returns the new file position on success.
- On error, it returns -1, and error information is written to **errno**.
- Seeking past the end of a file and then writing to it causes **holes** filled with zeros.
- Files with holes are called **sparse files**.
- Holes do not occupy physical disk space.
- **du** = estimate of the disk space used by the file.

| Argument | Description                                                                                                                                                                                                                                            |
| -------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| SEEK_CUR | Takes the value of the current file position (**fd**) plus the value **POS**, which can be negative, zero, or positive. **POS** of zero returns the value of the current file position.                                                               |
| SEEK_END | The value of the current file position (**fd**) becomes equal to the file length plus the value **POS**, which can be negative, zero, or positive. **POS** of zero sets the offset to the end of the file.                                             |
| SEEK_SET | The value of the current file position (**fd**) becomes equal to the value **POS**. **POS** of zero sets the offset to the beginning of the file.                                                                                                     |

More information: [Sparse Files](https://en.wikipedia.org/wiki/Sparse_file)
