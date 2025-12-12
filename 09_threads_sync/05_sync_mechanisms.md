## Synchronization mechanisms

The threads library provides three primary synchronization mechanisms:

- **Mutexes**. Mutual exclusion primitives that block access to variables from other threads. They enforce exclusive access by a single thread to a variable or a set of variables.
- **Joins**. A thread waits for other threads to finish.
- **Condition variables**. While mutexes provide synchronization by controlling thread access to data, condition variables allow threads to synchronize based on the actual value/state of the data.
