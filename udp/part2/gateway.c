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
#include "print_socket.h"

int main(int argc, char *argv[]){

  if (argc < 3){ printf("sould supply hostname and source port"); }


  srandom(10);                                                          // seed for the random generator

  // socket variables
  int gateway, bytes_recv, bytes_sent;
  socklen_t src_addr_len;
  struct sockaddr_in  src_addr, dest_addr;
  struct hostent *hostptr;
  struct { char head; u_long  body; char tail;} msg_rcv, msg_snd;       // variable to hold UDP segment info


  // connectionless IPv4 socket for UDP comunication
  if ((gateway = socket (AF_INET, SOCK_DGRAM, 0)) < 0){

    perror("NIC problome\n");
    return -1;
  }

  // preproccessing

  hostptr = gethostbyname(argv[1]);                                 // hostname -> IP

  bzero((char *) &src_addr, sizeof(src_addr));                      // zero out address-struct to prevent mishaps
  src_addr.sin_family = (short) AF_INET;                            // agin: IPv4
  src_addr.sin_addr.s_addr = htonl(INADDR_ANY);                     // spesfic id doesnt matter for the reciver in conectionless comunication
  src_addr.sin_port = htons(atoi(argv[2]));                         // set the port

  bzero((char *) &dest_addr, sizeof(dest_addr));
  dest_addr.sin_family = (short) AF_INET;
  dest_addr.sin_port =  htons(atoi(argv[2]) +1);
  bcopy(hostptr -> h_addr, (char *) &dest_addr.sin_addr, hostptr -> h_length);  // set IP

  msg_snd.head = '<';
  msg_snd.tail = '>';

  printsin( &src_addr, "RECV_UDP", "Local socket is:"); 
  fflush(stdout);


  if (bind(gateway, (struct sockaddr *) &src_addr, sizeof(src_addr)) < 0) {

    perror("connection to network error\n");
    exit(1);
  }


  while (1) {

    // reciving data

    src_addr_len = sizeof(src_addr);
    bytes_recv = recvfrom(gateway, &msg_rcv, sizeof(msg_rcv), 0, (struct sockaddr *) &src_addr, &src_addr_len);
    if (bytes_recv < 0){

      perror("could not recive any info \n");
      return -1;
    }

    // printing info about the source

    printf("Got data ::%c%ld%c\n", msg_rcv.head, (long) ntohl(msg_rcv.body), msg_rcv.tail);
    printsin( &src_addr, "recv_udp: ", "Packet from:");
    fflush(stdout);

    if (( (float)random() / (float)RAND_MAX ) > 0.5){   // packet loss simulation
      
      // sending info forward

      msg_snd.body = msg_rcv.body;
      bytes_sent = sendto(gateway, &msg_snd, sizeof(msg_snd), 0, (struct sockaddr *) &dest_addr, sizeof(dest_addr));
      if (bytes_sent < 0){

        perror("could not recive any info \n");
        return -1;
      }

    }
  }

  close(gateway);
  return 0;
}