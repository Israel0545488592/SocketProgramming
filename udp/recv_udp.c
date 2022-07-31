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

/*
void printsin(struct sockaddr_in *s, char *str1, char *str2) {
  printf("%s\n", str1);
  printf("%s: ", str2);
  -- port: sin->sin_port (host integer type) 
  -- IP: sin->sin_addr (IP in dotted-decimal notation) 
  printf("\n");
}
*/

int main(int argc, char *argv[]){

  int reciver, sender;                                  // socket variables
  socklen_t fsize;
  struct sockaddr_in  s_in, from;
  struct { char head; u_long  body; char tail;} msg;

  reciver = socket (AF_INET, SOCK_DGRAM, 0);            // connectionless IPv4 socket for UDP comunication


  // preproccessing

  bzero((char *) &s_in, sizeof(s_in));              // zero out address-struct to prevent mishaps
  s_in.sin_family = (short) AF_INET;                // agin: IPv4
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);         // connect via ALL port
  s_in.sin_port = htons((u_short)0x3333);

  //printsin( &s_in, "RECV_UDP", "Local socket is:"); 
  fflush(stdout);                                           // feed stdout filestream the content intended to him so far

  bind(reciver, (struct sockaddr *)&s_in, sizeof(s_in));    // listen to incoming messages

  while (1) {

    fsize = sizeof(from);
    sender = recvfrom(reciver, &msg, sizeof(msg), 0, (struct sockaddr *) &from, &fsize);
    //printsin( &from, "recv_udp: ", "Packet from:");
    printf("Got data ::%c%ld%c\n", msg.head, (long) ntohl(msg.body), msg.tail); 
    fflush(stdout);
    close(sender);
  }
  
  return 0;
}

