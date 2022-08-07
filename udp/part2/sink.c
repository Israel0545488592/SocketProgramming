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
#include "print_socket.h"


int main(int argc, char *argv[]){

  if (argc < 2){ printf("sould supply source port"); }


  // socket variables
  int reciver, bytes_recived;
  socklen_t src_addr_len;
  struct sockaddr_in  src_addr;
  struct { char head; u_long  body; char tail;} msg;        // variable to hold coming UDP segment info


  // connectionless IPv4 socket for UDP comunication
  if ((reciver = socket(AF_INET, SOCK_DGRAM, 0)) < 0){

    perror("NIC problome\n");
    return -1;
  }


  // preproccessing

  bzero((char *) &src_addr, sizeof(src_addr));              // zero out address-struct to prevent mishaps
  src_addr.sin_family = (short) AF_INET;                    // agin: IPv4
  src_addr.sin_addr.s_addr = htonl(INADDR_ANY);             // spesific source IP doesnt matter for conectionless comunication
  src_addr.sin_port = htons(atoi(argv[1]));                 // set up port

  printsin( &src_addr, "RECV_UDP", "Local socket is:"); 
  fflush(stdout);


  bind(reciver, (struct sockaddr *) &src_addr, sizeof(src_addr));          // listen to incoming messages

  while (1) {

    // reciving info

    src_addr_len = sizeof(src_addr);
    bytes_recived = recvfrom(reciver, &msg, sizeof(msg), 0, (struct sockaddr *) &src_addr, &src_addr_len);
    if (bytes_recived < 0){

      perror("could not recive any info \n");
      return -1;
    }

    // printing info about sender and packet

    printsin( &src_addr, "recv_udp: ", "Packet from:");
    printf("Got data ::%c%ld%c\n", msg.head, (long) ntohl(msg.body), msg.tail);
    fflush(stdout);
  }

  close(reciver);
  return 0;
}

