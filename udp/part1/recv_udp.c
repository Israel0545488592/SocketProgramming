#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>

/* method to print recived UDP segment's info */

void printsin(struct sockaddr_in *sock, char *str1, char *str2) {

  printf("%s\n", str1);
  char IP[16] = {0};
  inet_ntop(AF_INET, &(sock -> sin_addr), IP, INET_ADDRSTRLEN);
  printf("%s: ip = %s, port = %d \n", str2, IP, ntohs(sock -> sin_port));
  printf("\n");
}

int main(int argc, char *argv[]){

  int reciver, sender;                                      // socket variables
  socklen_t snd_addr_size;
  struct sockaddr_in  reciver_addr, sender_addr;
  struct { char head; u_long  body; char tail;} msg;        // variable to hold coming UDP segment info


  reciver = socket (AF_INET, SOCK_DGRAM, 0);                // connectionless IPv4 socket for UDP comunication

  // preproccessing

  bzero((char *) &reciver_addr, sizeof(reciver_addr));              // zero out address-struct to prevent mishaps
  reciver_addr.sin_family = (short) AF_INET;                        // agin: IPv4
  reciver_addr.sin_addr.s_addr = htonl(INADDR_ANY);                 // connect via ALL port
  reciver_addr.sin_port = htons((u_short)0x3333);

  printsin( &reciver_addr, "RECV_UDP", "Local socket is:"); 
  fflush(stdout);                                                   // feed stdout filestream the content intended to it so far

  bind(reciver, (struct sockaddr *) &reciver_addr, sizeof(reciver_addr));          // listen to incoming messages

  while (1) {

    snd_addr_size = sizeof(sender_addr);
    sender = recvfrom(reciver, &msg, sizeof(msg), 0, (struct sockaddr *) &sender_addr, &snd_addr_size);

    printsin( &sender_addr, "recv_udp: ", "Packet from:");
    printf("Got data ::%c%ld%c\n", msg.head, (long) ntohl(msg.body), msg.tail);
    fflush(stdout);

    close(sender);
  }

  close(reciver);
  return 0;
}

