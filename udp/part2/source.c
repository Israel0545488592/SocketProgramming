#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "print_socket.h"

int main(int argc, char *argv[]){


  // socket variables
  int sender, bytes_sent, itr;
  struct sockaddr_in  dest_addr, src_addr;
  struct hostent *hostptr;
  struct { char head; u_long body; char tail; } msg;


  // connectionless IPv4 socket for UDP comunication
  if ((sender = socket (AF_INET, SOCK_DGRAM, 0)) < 0){

    perror("NIC problome\n");
    return -1;
  }


  // preproccessing
  
  // get IP address
  hostptr = gethostbyname(argv[1]);

  bzero((char *) &dest_addr, sizeof(dest_addr));                                 // zero out address-struct to prevent mishaps
  dest_addr.sin_family = (short) AF_INET;                                        // again: IPv4
  bcopy(hostptr -> h_addr, (char *) &dest_addr.sin_addr, hostptr -> h_length);   // the IP of the destination
  dest_addr.sin_port = htons((u_short)0x3333);                                   // port

  bzero((char *) &src_addr, sizeof(src_addr));
  src_addr.sin_family = (short) AF_INET;
  src_addr.sin_addr.s_addr = htonl(INADDR_ANY);                                  // source IP doesnt matter for conectionless comunication
  src_addr.sin_port = htons((u_short)0x3332);

  printsin( &src_addr, "RECV_UDP", "Local socket is:"); 
  fflush(stdout);


  if (bind(sender, (struct sockaddr *) &src_addr, sizeof(src_addr)) < 0) {

    perror("connection to network error\n");
    exit(1);
  }


  itr = 0;
  while (1){

    msg.head = '<';
    msg.body = htonl(itr);
    msg.tail = '>';

    bytes_sent = sendto(sender, &msg, sizeof(msg), 0, (struct sockaddr *) &dest_addr, sizeof(dest_addr));
    if (bytes_sent < 0){

      perror("could not recive any info \n");
      return -1;
    }

    itr++;
    usleep(1000000);
    printf("datagram sent\n");
  }

  close(sender);
  return 0;
}