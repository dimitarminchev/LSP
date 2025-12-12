## Thread Cancellation Types

The **pthread_cancel()** function sends a cancellation request to a thread.

Whether and when the target thread reacts to the cancellation request depends on two attributes that are under the control of that thread: its cancelability state (enabled/disabled) and type:

- **Deferred** (default behavior) means that cancellation will be delayed until the thread calls a function **pthread_testcancel()**.

- **Asynchronous** means that the thread can be cancelled at any time (usually immediately, but the system does not guarantee this).