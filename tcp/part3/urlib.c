#include "urlib.h"

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

/* parsing URL, extracting hostname and URI and coping them into givaen strings */

int URLparser(char* URL, char* hostname, char* URI){

  int i = 0, j;

  while (URL[i] != '/' && URL[i]){ ++i; }
  i += 2;
  if (i >= strlen(URL)){ return -1;}

  j = i;
  while (URL[j] != '/' && URL[j]){ ++j; }
  strncpy(hostname, URL + i, j - i);
  if (j == strlen(URL)){ return 1;} // no URI spesefied thats fine

  i = j;
  ++j;
  if (j > strlen(URL)){ return -1;}
  while (URL[j]){ ++j; }
  strncpy(URI, URL + i +1, j - i);

  return 1;    
}