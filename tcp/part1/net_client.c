#include <sys/types.h>
#include <unistd.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>    
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <sys/types.h> 
#include <arpa/inet.h>

#define SIM_LENGTH 10
#define IP_ADDRESS "192.168.56.1"
#define PORT 80 

int main(void){
  
  // set up

  // socket variables
  int sock; 
  struct sockaddr_in cli_name;

  int count;
  int value;

  
  sock = socket(AF_INET, SOCK_STREAM, 0);   // conection-oriented, IPv4 socket for TCP communication
  if (sock < 0){

    perror ("Error opening channel");
    close(sock);
    exit(1);
  }

  printf("Client is alive and establishing socket connection.\n");
      
  // preproccessing of socket's address-struct
  bzero(&cli_name, sizeof(cli_name));                 // zero out to prevent mishaps
  cli_name.sin_family = AF_INET;                      // IPv4
  cli_name.sin_addr.s_addr = inet_addr(IP_ADDRESS);   // byte network order (IP)
  cli_name.sin_port = htons(PORT);                    // byte network order (port)


  // connect to IP:PORT
  if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) == -1){
    
    perror ("Error establishing communications");
    close(sock);
    exit(1);
  }


  // read whatever it sends you
  for (count = 1; count <= SIM_LENGTH; count++){
    
    read(sock, &value, 4);
    printf("Client has received %d from socket.\n", value);
  }

  printf("Exiting now.\n");
  close(sock); 
  exit(0); 
} 
