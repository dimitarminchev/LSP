## Race condition problems

**Race conditions** occur because, although the code may appear in the source in the order you expect it to run, threads are scheduled by the operating system and execute in an unpredictable order. It cannot be assumed that threads will run in the order they were created.

Threads may also run at different speeds. When threads execute concurrently (racing to finish), they can produce unexpected results.

Use **mutexes** and **joins** to achieve a predictable execution order and results.
