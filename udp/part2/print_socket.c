#include "print_socket.h"

/* method to print recived UDP segment's info */

void printsin(struct sockaddr_in *sock, char *str1, char *str2) {

  printf("%s\n", str1);
  char IP[16] = {0};
  inet_ntop(AF_INET, &(sock -> sin_addr), IP, INET_ADDRSTRLEN);
  printf("%s: ip = %s, port = %d \n", str2, IP, ntohs(sock -> sin_port));
  printf("\n");
}