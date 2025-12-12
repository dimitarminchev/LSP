## Finishing Threads

There are several ways in which a thread may be terminated:

- The thread returns normally and its work is done.
- The thread calls **pthread_exit** regardless of whether its work is done or not.
- The thread is cancelled by another thread via **pthread_cancel**.
- The entire process is terminated due to calling **exec()** or **exit()**
- If main() finishes first, without explicitly calling **pthread_exit**