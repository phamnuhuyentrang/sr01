#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <ifaddrs.h>

//recupere l'adresse ip de chaque carte réseau chaque 5 secondes
int main() {

  struct ifaddrs *addrs, *tmp;
  while (1) {
     getifaddrs(&addrs);
     tmp = addrs;

     while (tmp) {
        if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET) {
          struct sockaddr_in *pAddr = (struct sockaddr_in *)tmp->ifa_addr;
          printf("[network manager] %s: %s\n", tmp->ifa_name, inet_ntoa(pAddr->sin_addr));
        }
        tmp = tmp->ifa_next;
     }

     freeifaddrs(addrs);

     sleep(5);
  }

  return 0;
}
