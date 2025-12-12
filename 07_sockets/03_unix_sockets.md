## Using Unix Sockets

```c
#include<sys/types.h>
#include<sys/socket.h>

int socket(int domain, int type, int protocol);
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
```

- **socket()** creates an endpoint for communication and returns a file descriptor that refers to that endpoint.
  - domain determines the protocol family which will be used: **AF_UNIX**, **AF_LOCAL**, **AF_INET**.
  - type determines the communication semantics: **SOCK_STREAM** or **SOCK_DGRAM**.
- When a socket is created with **socket()**, it exists in a name space (address space) but has no address assigned to it.
- **bind()** assigns the address specified in **addr** to the socket referred to by the file descriptor **sockfd** returned by the socket() method.


- **sockaddr** has the following structure:
```c
struct sockaddr {
   sa_family_t sa_family;
   char sa_data[14];
}
```