#include "nslookup.h"

char* lookup(char* hostname) {

  // variables to store the result
  struct addrinfo* res;
  char* hostaddr;
  struct sockaddr_in* saddr;

  /* 
    the main method which I assume ask the OS to
    run the nslookup < hostname > command. that in return result
    in a DNS request to figure out the IP of the hostname.
  */
  if (0 != getaddrinfo(hostname, NULL, NULL, &res)) {

    fprintf(stderr, "Error in resolving hostname %s\n", hostname);
    exit(1);
  }
  
  // some casting and we are done
  saddr = (struct sockaddr_in*)res -> ai_addr;
  hostaddr = inet_ntoa(saddr -> sin_addr);

  return hostaddr;
}
