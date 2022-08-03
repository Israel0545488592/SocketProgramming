#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

  // set up

  srandom(10);                                                          // seed for the random generator

  int reciver, sender;                                                  // socket variables
  socklen_t snd_addr_size;
  struct sockaddr_in  reciver_addr, sender_addr, dest;
  struct hostent *hostptr;
  struct { char head; u_long  body; char tail;} msg_rcv, msg_snd;       // variable to hold coming UDP segment info


  reciver = socket (AF_INET, SOCK_DGRAM, 0);                            // connectionless IPv4 socket for UDP comunication

  // preproccessing

  bzero((char *) &reciver_addr, sizeof(reciver_addr));                  // zero out address-struct to prevent mishaps
  reciver_addr.sin_family = (short) AF_INET;                            // agin: IPv4
  reciver_addr.sin_addr.s_addr = htonl(INADDR_ANY);                     // connect via ALL port
  reciver_addr.sin_port = htons((u_short)0x3333);

  // more for the sending proccess

  bzero((char *) &dest, sizeof(dest));
  hostptr = gethostbyname(argv[1]);                                       
  dest.sin_family = (short) AF_INET;
  bcopy(hostptr -> h_addr, (char *) &dest.sin_addr, hostptr -> h_length);
  dest.sin_port = htons((u_short)0x3334);

  bind(reciver, (struct sockaddr *) &reciver_addr, sizeof(reciver_addr)); // listen to incoming messages

  msg_snd.head = '<';
  msg_snd.tail = '>';

  while (1) {

    snd_addr_size = sizeof(sender_addr);
    sender = recvfrom(reciver, &msg_rcv, sizeof(msg_rcv), 0, (struct sockaddr *) &sender_addr, &snd_addr_size);

    printf("Got data ::%c%ld%c\n", msg_rcv.head, (long) ntohl(msg_rcv.body), msg_rcv.tail);
    fflush(stdout);

    if ( ((float) random()) / ((float) RAND_MAX) ){

      msg_snd.body = msg_rcv.body; msg_snd.body += 1;
      sendto(sender, &msg_snd, sizeof(msg_snd), 0, (struct sockaddr *) &dest, sizeof(dest));
    }

    close(sender);
  }

  close(reciver);
  return 0;
}