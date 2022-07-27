#include "nslookup.h"

char* lookup(char* hostname) {

  struct addrinfo* res;
  char* hostaddr;
  struct sockaddr_in* saddr;
  
  if (0 != getaddrinfo(hostname, NULL, NULL, &res)) {
    fprintf(stderr, "Error in resolving hostname %s\n", hostname);
    exit(1);
  }
  
  saddr = (struct sockaddr_in*)res->ai_addr;
  hostaddr = inet_ntoa(saddr->sin_addr);

  return hostaddr;
}
