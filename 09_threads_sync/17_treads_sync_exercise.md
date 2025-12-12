## Thread synchronization exercise
Practice the chapter material by implementing the project described below.

### AdvancedChat

Modify the pair of network server/client programs from the previous chapter with the following changes:

- The server should accept an optional `-p` argument which, if present, enables a "polite mode". In polite mode the server should process client messages in rounds: when one client sends a message, that client's next message is not processed until all other connected clients have sent their messages. You may change the communication protocol between clients and server if needed to implement this behavior.

- The server should persist chat history to a file named `chat.log`.
