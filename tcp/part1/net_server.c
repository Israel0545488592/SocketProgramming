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

#define PORT 80
#define SIM_LENGTH 10

int main(void){


  // set up
  int count;
  int sock; 
  int connect_sock; 
  struct sockaddr_in serv_name; 
  socklen_t len = sizeof(serv_name);

  sock = socket(AF_INET, SOCK_STREAM, 0); // conection-oriented, IPv4 socket for TCP communication

    
  // preproccessing of socket's address-struct
  bzero(&serv_name, sizeof(serv_name));   // zero out to prevent mishaps
  serv_name.sin_family = AF_INET;         // IPv4
  serv_name.sin_port = htons(PORT);       // byte network order (port)


  //listen to whoever is trying to connect to this IP, up to 2 clients though
  bind(sock, (struct sockaddr *)&serv_name, sizeof(serv_name));
  listen(sock, 2); 

  len = sizeof(serv_name);
  
  // open up another socket for new client
  connect_sock = accept(sock, (struct sockaddr *)&serv_name, &len);

  //send it a lovely message
  for (count = 1; count <= SIM_LENGTH; count++){
    
    write(connect_sock, &count, 4);
    printf("Server has written %d to socket.\n", count);
  }

  close(connect_sock); 
  close(sock);
}
