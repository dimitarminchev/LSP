## Working with Sockets in C

| method                           | description                                                      |
|----------------------------------|------------------------------------------------------------------|
| socket ()                        | creates an endpoint for communication                            |
| bind ()                          | binds a name to a socket                                         |
| recv (), recvfrom (), recvmsg () | receives a message from a socket                                 |
| send (), sendto (), sendmsg ()   | sends a message to a socket                                      |
| socketpair ()                    | creates a pair of connected sockets                              |
| listen ()                        | listens for connections on a socket                              |
| accept ()                        | accepts a connection on a socket                                 |
| connect ()                       | initiates a connection on a socket                               |
| htons ()                         | converts unsigned short integer to network byte order            |
| gethostbyname ()                 | returns a structure of type hostent for the given host name      |
