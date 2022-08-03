#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]){


  // socket variables
  int sender, itr;
  struct sockaddr_in  dest;
  struct hostent *hostptr;
  struct { char head; u_long body; char tail; } msgbuf;


  // preproccessing

  sender = socket (AF_INET, SOCK_DGRAM, 0);                                 // connectionless IPv4 socket for UDP comunication
  bzero((char *) &dest, sizeof(dest));                                      // zero out address-struct to prevent mishaps
  hostptr = gethostbyname(argv[1]);                                         // get IP address of hostname
  dest.sin_family = (short) AF_INET;                                        // again: IPv4
  bcopy(hostptr -> h_addr, (char *) &dest.sin_addr, hostptr -> h_length);
  dest.sin_port = htons((u_short)0x3333);


  itr = 0;
  while (1){

    msgbuf.head = '<';
    msgbuf.body = htonl(itr);
    msgbuf.tail = '>';

    sendto(sender, &msgbuf, sizeof(msgbuf), 0, (struct sockaddr *) &dest, sizeof(dest));

    itr++;
    usleep(1000000);
    printf("datagram sent\n");
  }
  
  close(sender);
  return 0;
}