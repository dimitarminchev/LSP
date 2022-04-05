## Използване на Unix сокети

```c
#include<sys/types.h>
#include<sys/socket.h>

int socket(int domain, int type, int protocol);
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
```

- **socket()** създава крайна точка за комуникация и връща дескриптор на файла, който се отнася до тази крайна точка.
  - домейнът (_Термин на Английски език: domain_) определя семейството протоколи, което ще се използва: **AF_UNIX**, **AF_LOCAL**, **AF_INET**.
  - Тип (_Термин на Английски език: type_) определя комуникационната семантика: **SOCK_STREAM** или **SOCK_DGRAM**.
- Когато се създава сокет със **socket()**, то той съществува в именованото пространство (адресното пространство), но няма зададен адрес.
- **bind()** присвоява адреса, посочен в **addr**, на сокета, посочен от файловият дескриптор **sockfd** върнат от метода socket().


- **sockaddr** има следната структура:
```c
struct sockaddr {
   sa_family_t sa_family;
   char sa_data[14];
}
```