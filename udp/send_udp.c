#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>

int main(int argc, char *argv[]){


  // socket variables
  int sender;
  struct sockaddr_in  dest;
  struct hostent *hostptr;
  struct { char head; u_long body; char tail; } msgbuf;


  // preproccessing

  sender = socket (AF_INET, SOCK_DGRAM, 0);                                 // connectionless IPv4 socket for UDP comunication
  bzero((char *) &dest, sizeof(dest));                                      // zero out address-struct to prevent mishaps
  hostptr = gethostbyname(argv[1]);                                         // get IP address
  dest.sin_family = (short) AF_INET;                                        // again: IPv4
  bcopy(hostptr -> h_addr, (char *) &dest.sin_addr, hostptr -> h_length);
  dest.sin_port = htons((u_short)0x3333);

  msgbuf.head = '<';
  msgbuf.body = htonl(getpid());                                    /* IMPORTANT! */
  msgbuf.tail = '>';

  sendto(sender, &msgbuf, sizeof(msgbuf), 0, (struct sockaddr *) &dest, sizeof(dest));

  close(sender);
  return 0;
}